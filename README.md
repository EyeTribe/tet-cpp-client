C++ SDK for The Eye Tribe Tracker
====

Introduction
----

This is the C++ reference implementation for The Eye Tribe Tracker and provides a C++ interface for communicating with the server, without resorting to socket programming and JSON-parsing. 

This version is to be considered _alpha_. Feedback and bug fix submissions are welcome.

Please visit http://dev.theeyetribe.com for more information.


Compilation
----

The C++SDK comes with CMake-support making it easy to build the SDK as a library for inclusion in your own project. Alternatively you may copy the files directly into your own project. 

The CMake GUI can be obtained at http://www.cmake.org.


Dependencies
----

In order to provide non-C++11 portability and network support, the C++ SDK utilities a variety of Boost libraries. The lowest boost version version tested is 1.53, but older versions may work. For information on obtaining and installing a recent version of Boost, please visit http://www.boost.org.


Build
----

1. Install boost 
2. Use CMake to generate project files 
3. Build library with your preferred build tool


Samples
----

There are currently no samples available for the C++ SDK, but they will be added as they become available.


API Reference
----

The complete API specification used by the C++ SDK to communicate with the server is available on http://dev.theeyetribe.com/api/


Changelog
----

0.9.26 (2014-01-30)
- Initial release