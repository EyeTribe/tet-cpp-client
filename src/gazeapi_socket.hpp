/*
 * Copyright (c) 2013-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef _THEEYETRIBE_GAZEAPI_SOCKET_H_
#define _THEEYETRIBE_GAZEAPI_SOCKET_H_

#include "gazeapi_observable.hpp"

#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>

#include <string>
#include <vector>
#include <deque>


namespace gtl
{
    class JSONPackageMatcher; // Forward declaration for boost::asio::is_matching_condition
};

namespace boost
{
    namespace asio
    {
        template <> struct is_match_condition < gtl::JSONPackageMatcher >
            : public true_type
            {};
    }
};

namespace gtl
{
    class JSONPackageMatcher
    {
    public:
        JSONPackageMatcher();

        template <typename Iterator>
        std::pair<Iterator, bool> operator()( Iterator begin, Iterator end )
        {
            Iterator i = begin;

            while( i != end )
            {
                bool const left = *i == '{';
                bool const right = *i == '}';
                m_stack += left ? 1 : right ? -1 : 0;
                m_in_message |= left;

                ++i; // We need to make sure that '}' is consumed before returning

                if( m_stack == 0 && m_in_message )
                {
                    while( i != end && *i != '{' )
                    {
                        ++i; // read all post-amble until next message starts (\r, \n, etc.)
                    }

                    m_in_message = false;
                    return std::make_pair( i, true );
                }
            }
            return std::make_pair( i, false );
        }

    private:
        bool    m_in_message;
        size_t  m_stack;
    };

    // Call backs from socket
    class ISocketListener
    {
    public:
        virtual ~ISocketListener() {}
        virtual void on_message( std::string const & message ) = 0;
        virtual void on_disconnected() = 0;
    };

    class HandleMessages
    {
    public:
        HandleMessages( class Socket & owner );
        ~HandleMessages();
    
        void process_message( std::string const & message );
        void terminate();

    private:
        void run();
        void on_message( std::string const & message );

    private:
        Socket &                    m_owner;
        bool                        m_terminate;
        std::deque<std::string>     m_queue;
        boost::mutex                m_lock;
        boost::thread               m_thread;
    };

    class Socket : public Observable < ISocketListener >
    {
    public:
        Socket( int verbose_level = 0 );
        ~Socket();

        bool connect( std::string const & address, std::string const & port );
        void disconnect();
        bool handle_connection_state();
        int get_id( std::string const & message ) const;
        bool send( std::string const & message );
        bool send_sync( std::string const & message );

    private:
        void on_read( boost::system::error_code const & error, size_t bytes_transferred );
        void on_write( boost::system::error_code const & error, char* data );

    private:
        friend HandleMessages;
        boost::asio::io_service         m_io_service;
        boost::asio::ip::tcp::socket    m_socket;
        HandleMessages                  m_handler;
        int                             m_verbose;
        int                             m_sync_id;
        boost::asio::streambuf          m_buffer;
        boost::thread                   m_thread;
        JSONPackageMatcher              m_matcher;
    };
}

#endif // _THEEYETRIBE_GAZEAPI_SOCKET_H_
