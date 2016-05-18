# Change Log #
---

0.9.77 (2016-05-18)
---
- Removed heartbeats as the server no longer requires them
- Removed connection pull mode as the server natively only support push mode
- Changed connection methods (no more pulls)
- Changed verbose mechanism in GazeAPI constructor from bool (turn on/off) to integer (verbose level)
- Added missing remove_observer method
- Fixed issue with changed tracker state
- Fixed deadlock issues from blocking server calls
- Fixed Boost json concurrency crash bug
- Various code cleanup

0.9.53 (2015-01-26)
---
- Implements Version 2 of the API (requires a server that supports API Version 2)
- Pseudo-blocking methods improved to block/sync robustly utilizing the new Version 2 IDs

0.9.49 (2014-12-10)
---
- Fixed a crash (exception) that sometimes would occur when disconnecting from the GazeAPI
- Fixed GazeAPI hanging when calling connect for the second time
- Added IConnectionStateListener to the GazerApi to be notified about connection state changes
- Added a missing calibration changed notification from the ICalibrationResultListener

0.9.36 (2014-07-17)
---
- Updated license

0.9.33 (2014-04-24)
---
- Fixed missing calibration report targets
- Added missing get_screen API method

0.9.31 (2014-04-01)
---
- Fixed wrong Json-formatted set screen request string
- Fixed bug related to uninitialized "avg" member of GazeData
- Vital server calls made blocking, including get_frame() when running in pull-mode

0.9.27 (2014-02-11)
---
- Bug fix of status code
- Removed forward declarations and included interface and types headers instead in gazeapi.h
- Fixed hanging observers
- Cleans up when shutting down!
- Added push_mode to connect (similar to C# SDK)
- Fixed bug where no GazeData was ever sent to the client
- Added is_connected() connectivity info to the GazeApi

0.9.26 (2014-01-30)
---
- Initial release
