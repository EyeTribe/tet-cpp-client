C++ SDK for The Eye Tribe Tracker
====

Introduction
----

This is the C++ reference implementation for The Eye Tribe Tracker and provides a C++ interface for communicating with the server, without resorting to socket programming and JSON-parsing. 

This version is to be considered _alpha_. Feedback and bug fix submissions are welcome.

Please visit our [developer website](http://dev.theeyetribe.com) for more information.


Compilation
----

The C++SDK comes with CMake-support making it easy to build the SDK as a library for inclusion in your own project. Alternatively you may copy the files directly into your own project. 

The CMake GUI can be obtained at the [CMake website](http://www.cmake.org).


Dependencies
----

In order to provide non-C++11 portability and network support, the C++ SDK utilizes a variety of [Boost libraries](http://www.boost.org). The lowest boost version version tested is 1.53, but older versions may work. For information on obtaining and installing a recent version of Boost, please the [Boost website](http://www.boost.org).

Boost is meant to be built from source and does include instructions on how to accomplish this. However, prebuilt binaries can be downloaded as well. CMake may encounter issues with prebuilt versions of Boost, and thus we advise users to build Boost manually.


Build
----

1. Install [Boost libraries](http://www.boost.org) 
2. Use CMake GUI to generate project files 
3. Build the C++ SDK library with your preferred compiler

Note: In step 2) CMake will try to find Boost during configure. If that fails do the following:
a. Turn on the Advanced flag
b. Set BOOST_INCLUDE_DIR to the path of the _root_ of Boost
c. Configure
d. If CMake fails to find the Boost libraries, then set BOOST_LIBRARYDIR to the path of where the prebuilt libraries  of Boost are located
e. Configure and this should succeed
f. Generate project files 


Samples
----

There are currently no samples available for the C++ SDK, but they will be added as they become available.


API Reference
----

The complete API specification used by the C++ SDK to communicate with the server is available on our [developer website](http://dev.theeyetribe.com/api/).


Changelog
----

0.9.49 (2014-12-10)

- Fixed occational exception when disconnecting from the GazeAPI
- Fixed GazeAPI hanging when connecting for the second time
- Added support for listening to EyeTribe Server conneciton state (IConnectionStateListener)
- Added missing calibration result notification to ICalibrationResultListener(s)

0.9.36 (2014-07-17)

- Updated license

0.9.33 (2014-04-24)

- Fixed missing calibration report targets
- Added missing get_screen API method

0.9.31 (2014-04-01)

- Fixed wrong Json-formatted set screen request string
- Fixed bug related to uninitialized "avg" member of GazeData
- Vital server calls made blocking, including get_frame() when running in pull-mode

0.9.27 (2014-02-11)

- Bug fix of status code
- Removed forward declarations and included interface and types headers instead in gazeapi.h
- Fixed hanging observers
- Cleans up when shutting down!
- Added push_mode to connect (similar to C# SDK)
- Fixed bug where no GazeData was ever sent to the client
- Added is_connected() connectivity info to the GazeApi

0.9.26 (2014-01-30)

- Initial release
