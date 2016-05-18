![The Eye Tribe](tet_logo.png)

C++ SDK for the EyeTribe Dev Kit
====

Introduction
----

This is the C++ library implementation for the EyeTribe Dev Kit. This reference implementation provides a C++ interface for communicating with the EyeTribe Server through the open EyeTribe API. The library allow developers to get started quickly and focus their efforts on creating truly immersive and innovative apps using our eye tracking technology.

Documentation
----
Find examples of how to use thislibrary at our [EyeTribe C++ Tutorial](http://dev.theeyetribe.com/cpp/). The EyeTribe API reference is found at [Eye Tribe Developer Website](http://dev.theeyetribe.com/api/).

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
  a. Download and extract the Boost source code  
  b. Run bootstrap from a terminal and follow the on-screen instructions
2. Use CMake GUI to generate project files  
  (CMake will try to find Boost during configure. If that fails do the following)  
  a. Turn on the Advanced flag  
  b. Set BOOST_INCLUDE_DIR to the path of the _root_ of Boost  
  c. Configure  
  d. If CMake fails to find the Boost libraries, then set BOOST_LIBRARYDIR to the path of where the prebuilt libraries  of Boost are located  
  e. Configure  
  f. Generate project files
3. Build the C++ SDK library with your preferred compiler


Getting Help
----

- **Have questions or need support?** Visit our [developer forum](http://theeyetribe.com/forum/), to find answers to your questions and share your experiences with others developers.
- **Have a bug to report?** Open a [new issue](https://github.com/EyeTribe/tet-charp-client/issues) and tell us what you are experiencing. Please add library version and full log if possible.
- **Have a feature request?** Either open a [new issue](https://github.com/EyeTribe/tet-csharp-client/issues) or post in our [developer forum](http://theeyetribe.com/forum/). Tell us what feature you are missing and what it should do. 

Feedback
----

If you like using this library, please consider sending out a tweet mentioning [@TheEyeTribe](twitter.com/theeyetribe), announce your app in our [developer forum](http://theeyetribe.com/forum/), or email [support@theeyetribe.com](mailto:support@theeyetribe.com) to let us know.