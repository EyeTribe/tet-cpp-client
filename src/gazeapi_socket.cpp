/*
 * Copyright (c) 2013-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX
#endif

#include "gazeapi_socket.hpp"


namespace gtl
{
    JSONPackageMatcher::JSONPackageMatcher()
        : m_stack( 0 )
        , m_in_message( false )
    {}

    Socket::Socket( int verbose_level )
        : m_io_service()
        , m_socket( m_io_service )
        , m_handler( *this )
        , m_verbose( verbose_level )
        , m_sync_id( -1 )
    {}

    Socket::~Socket()
    {
        if( m_thread.joinable() )
        {
            m_thread.join();
        }
    }

    bool Socket::connect( std::string const & address, std::string const & port )
    {
        // If a thread is already running - wait for it to finish
        if( m_thread.joinable() )
        {
            m_thread.join();
        }

        using namespace boost::asio::ip;

        tcp::resolver resolver( m_io_service );
        tcp::resolver::query query( address, port );
        tcp::resolver::iterator endpoint_iterator = resolver.resolve( query );
        tcp::resolver::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;

        while( error && endpoint_iterator != end )
        {
            m_socket.close();
            m_socket.connect( *endpoint_iterator++, error );
        }

        if( error )
        {
            m_socket.close();
            return false;
        }

        boost::asio::async_read_until( m_socket, m_buffer, m_matcher,
            boost::bind( &Socket::on_read,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred ) );

        // Keep io_service processing requests in a separate thread
        m_io_service.reset();
        m_thread = boost::thread( boost::bind( ( size_t( boost::asio::io_service::* )( ) ) &boost::asio::io_service::run, &m_io_service ) );

        return true;
    }

    void Socket::disconnect()
    {
        if( m_socket.is_open() )
        {
            m_socket.close();
        }
        m_io_service.stop(); // stops io_service and exits thread
    }

    bool Socket::handle_connection_state()
    {
        return true;
    }

    int Socket::get_id( std::string const & message ) const
    {
        size_t const pos = message.find( "\"id\":" );
        int const id = pos != std::string::npos ? std::atoi( &message[pos + 5] ) : -1;    // sizeof( "id": ) == 5
        return id;
    }

    bool Socket::send( std::string const & message )
    {
        size_t const size = message.size();
        char * data = new char[ size ];
        memcpy( data, message.c_str(), size );

        boost::asio::async_write( m_socket,
            boost::asio::buffer( data, size ),
            boost::bind( &Socket::on_write, this, boost::asio::placeholders::error, data ) );

        if( m_verbose > 0 )
        {
            std::cout << "Send: " << message << std::endl << std::flush;
        }

        return true;
    }

    bool Socket::send_sync( std::string const & message )
    {
        int const id = get_id( message );
        if( id == -1 )
        {
            return false;
        }
        assert( m_sync_id == -1 );
        m_sync_id = id;
        if( m_verbose > 0 )
        {
            std::cout << "Sync [id: " << id << "] begun"<< std::endl << std::flush;
        }
        send( message );
        while( m_sync_id == id )
        {
            boost::this_thread::sleep_for( boost::chrono::milliseconds( 1 ) );
        }
        if( m_verbose > 0 )
        {
            std::cout << "Sync [id: " << id << "] done" << std::endl << std::flush;
        }
        return true;
    }

    void Socket::on_read( boost::system::error_code const & error, size_t bytes_transferred )
    {
        if( error )
        {
            Observable<ISocketListener>::ObserverVector const & observers = get_observers();
            for( size_t i = 0; i < observers.size(); ++i )
            {
                observers[i]->on_disconnected();
            }
        }
        else
        {
            typedef boost::asio::streambuf::const_buffers_type buffer_type;
            typedef boost::asio::buffers_iterator<buffer_type> iterator;

            buffer_type input = m_buffer.data();

            std::string reply; reply.reserve( bytes_transferred );
            std::copy( iterator::begin( input ), iterator::begin( input ) + bytes_transferred, std::back_inserter( reply ) );
            m_buffer.consume( bytes_transferred );

            if( m_verbose > 1 )
            {
                std::cout << "Recv: " << reply << std::endl << std::flush;
            }

            m_handler.process_message( reply );

            boost::asio::async_read_until( m_socket, m_buffer, m_matcher,
                boost::bind( &Socket::on_read,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred ) );
        }
    }

    void Socket::on_write( const boost::system::error_code& error, char* data )
    {
        if( error )
        {
            Observable<ISocketListener>::ObserverVector const & observers = get_observers();

            for( size_t i = 0; i < observers.size(); ++i )
            {
                observers[ i ]->on_disconnected();
            }
        }

        delete[] data;
    }

    HandleMessages::HandleMessages( Socket & owner )
        : m_owner( owner )
        , m_terminate( false )
    {
        m_thread = boost::thread( boost::bind( &HandleMessages::run, this ) );
    }

    HandleMessages::~HandleMessages()
    {
        terminate();
        if( m_thread.joinable() )
        {
            m_thread.join();
        }
    }

    void HandleMessages::on_message( std::string const & message )
    {
        Observable<ISocketListener>::ObserverVector const & observers = m_owner.get_observers();
        for( size_t i = 0; i < observers.size(); ++i )
        {
            observers[i]->on_message( message );
        }
    }

    void HandleMessages::process_message( std::string const & message )
    {
        // Validate if message contain an id, and if we currently have a blocking request with that id
        {
            int const id = m_owner.get_id( message );
            if( id != -1 && m_owner.m_sync_id == id )
            {
                on_message( message );
                m_owner.m_sync_id = -1;
                return;
            }
        }
        m_lock.lock();
        m_queue.push_back( message );
        m_lock.unlock();
    }

    void HandleMessages::terminate()
    {
        m_terminate = true;
    }

    void HandleMessages::run()
    {
        while( !m_terminate )
        {
            if( m_queue.empty() )
            {
                boost::this_thread::sleep_for( boost::chrono::milliseconds( 1 ) );
            }
            else
            {
                m_lock.lock();
                std::string const message = m_queue.front();
                m_queue.pop_front();
                m_lock.unlock();
                on_message( message );
            }
        }
    }

}
