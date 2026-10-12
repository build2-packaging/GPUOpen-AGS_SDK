# GPUOpen-AGS_SDK - <SUMMARY>

This is a `build2` package repository for [`GPUOpen-AGS_SDK`](https://<UPSTREAM-URL>),
a <SUMMARY-OF-FUNCTIONALITY>.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`GPUOpen-AGS_SDK` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](<PACKAGE>/PACKAGE-README.md) file.

The development setup for `GPUOpen-AGS_SDK` uses the standard `bdep`-based workflow.
For example:

```
git clone .../GPUOpen-AGS_SDK.git
cd GPUOpen-AGS_SDK

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
