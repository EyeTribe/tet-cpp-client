/*
 * Copyright (c) 2013-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef _THEEYETRIBE_GAZEAPI_H_
#define _THEEYETRIBE_GAZEAPI_H_

#include <gazeapi_types.h>
#include <gazeapi_interfaces.h>

#include <memory>
#include <string>


namespace gtl
{

    /** \class GazeApi
    *   This is the main entry point into the GaziApi library for communicating and controlling The Eyetribe Tracker server
    */
    class GazeApi
    {
    public:
        /** GazeApi constructor.
         * Creates an instance of the GazeApi that can be used to connect to a server.
         *
         * \param[in] verbose_level Control output of JSON-messages recieved and sent on the socket.
         * When enabling verbose output, messages are output using std::cout.
         * levels:
         * 0 = disabled,
         * 1 = send (sync/async),
         * 2 = all send/recv
         */
        explicit GazeApi( int verbose_level = 0 );
        ~GazeApi();

        /** Add an IGazeListener to the GazeApi.
         *
         * \param[in] listener The IGazeListener listener to be added.
         * \sa remove_listener(IGazeListener & listener).
         */
        void add_listener( IGazeListener & listener );

        /** Remove an IGazeListener from the GazeApi.
         *
         * \param[in] listener The IGazeListener listener to be removed.
         * \sa add_listener(IGazeListener & listener).
         */
        void remove_listener( IGazeListener & listener );

        /** Add an ICalibrationResultListener to the GazeApi.
         *
         * \param[in] listener The ICalibrationResultListener listener to be added.
         * \sa remove_listener(ICalibrationResultListener & listener).
         */
        void add_listener( ICalibrationResultListener & listener );

        /** Remove an ICalibrationResultListener from the GazeApi.
         *
         * \param[in] listener The ICalibrationResultListener listener to be removed.
         * \sa add_listener(ICalibrationResultListener & listener).
         */
        void remove_listener( ICalibrationResultListener & listener );

        /** Add an IConnectionStateListener to the GazeApi.
        *
        * \param[in] listener The IConnectionStateListener listener to be added.
        * \sa remove_listener(IConnectionStateListener & listener).
        */
        void add_listener( IConnectionStateListener & listener );

        /** Remove an IConnectionStateListener from the GazeApi.
        *
        * \param[in] listener The IConnectionStateListener listener to be removed.
        * \sa add_listener(IConnectionStateListener & listener).
        */
        void remove_listener( IConnectionStateListener & listener );

        /** Add an ITrackerStateListener to the GazeApi.
         *
         * \param[in] listener The ITrackerStateListener listener to be added.
         * \sa remove_listener(ITrackerStateListener & listener).
         */
        void add_listener( ITrackerStateListener & listener );

        /** Remove an ITrackerStateListener from the GazeApi.
         *
         * \param[in] listener The ITrackerStateListener listener to be removed.
         * \sa add_listener(ITrackerStateListener & listener).
         */
        void remove_listener( ITrackerStateListener & listener );

        /** Add an ICalibrationProcessHandler to the GazeApi.
         *
         * \param[in] listener The ICalibrationProcessHandler listener to be added.
         * \sa remove_listener(ICalibrationProcessHandler & listener).
         */
        void add_listener( ICalibrationProcessHandler & listener );

        /** Remove an ICalibrationProcessHandler from the GazeApi.
         *
         * \param[in] listener The ICalibrationProcessHandler listener to be removed.
         * \sa add_listener(ICalibrationProcessHandler & listener).
         */
        void remove_listener( ICalibrationProcessHandler & listener );

        /** Query whether the client is connected the the server.
         *
         * \return bool True if connected, false if not.
         */
        bool is_connected() const;

        /** Connect to the server via default port.
         *
         * \return bool True if connected, false if connection failed.
         */
        bool connect();

        /** Connect to the server via specified port.
         *
         * \param[in] port port number to connect to server on.
         * \return bool True if connected, false if connection failed.
         */
        bool connect( unsigned short port );

        /** Disconnect from server. */
        void disconnect();

        /** Set screen parameters.
         *
         * \param[in] screen the Screen parameters to be set.
         */
        bool set_screen( Screen const & screen );

        /** Get current used screen parameters.
         *
         * \param[out] screen the Screen parameters to be retrieved.
         */
        void get_screen( Screen & screen ) const;

        /** Get current GazeData
         *
         * Retrieves the current valid GazeData.
         *
         * \param[out] gaze_data current valid GazeData.
         */
        void get_frame( GazeData & gaze_data ) const;

        /** Get current valid calibration
         *
         * \param[out] calib_result latest valid calibration result.
         */
        void get_calib_result( CalibResult & calib_result ) const;

        /** Read the current cached server state.
         *  NOTE: The cached version is not guaranteed to be up to date.
         *
         * \returns ServerState the current server state.
         */
        ServerState const & get_server_state() const;

        /** Update and return the current server state.
        *
        * \returns ServerState the current server state.
        */
        ServerState const & update_server_state();

        /** Begin new calibration sesssion.
         *
         * \param[in] point_count The number of points to use for calibration.
         * \returns indication of the request processed okay.
         */
        bool calibration_start( int const point_count );

        /** Clear the current server calibration .
         *
         * Clears the current server calibration but does not affect an ongoing calibration session.
         */
        void calibration_clear();

        /** Abort the current calibration session.
         *
         * Aborts the current calibration session, but does not clear any valid calibration in the server
         */
        void calibration_abort();

        /** Begin calibration a new calibration point.
         *
         * \param[in] x x-coordinate of calibration point.
         * \param[in] y y-coordinate of calibration point.
         * \returns indication of the request processed okay.
         * \sa calibration_point_end.
         */
        bool calibration_point_start( int const x, int const y );

        /** End current calibration point.
         * \sa calibration_point_start(int const x, int const y).
         */
        void calibration_point_end();

    private:
        GazeApi( GazeApi const & other );
        GazeApi & operator = ( GazeApi const & other );

        class Engine;

#if __cplusplus <= 199711L
        std::auto_ptr<Engine> m_engine;
#else
        std::unique_ptr<Engine> m_engine;
#endif
    };

}

#endif
