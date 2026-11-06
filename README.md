# GPUOpen-AGS_SDK - AMD GPU Services (AGS) C++ library and API headers

This is a `build2` package repository for
[`AGS_SDK`](https://github.com/GPUOpen-LibrariesAndSDKs/AGS_SDK),
the SDK of the AMD GPU Services (AGS) library for querying AMD GPU software
and hardware state and accessing AMD driver extensions for Direct3D 11 and 12.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libgpuopen-ags` or `libgpuopen-ags-headers` in your `build2`-based project,
then instead see the accompanying
[`libgpuopen-ags/PACKAGE-README.md`](libgpuopen-ags/PACKAGE-README.md) or
[`libgpuopen-ags-headers/PACKAGE-README.md`](libgpuopen-ags-headers/PACKAGE-README.md)
file.

The development setup for `GPUOpen-AGS_SDK` uses the standard `bdep`-based workflow.
For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/GPUOpen-AGS_SDK.git
cd GPUOpen-AGS_SDK

bdep init -C @msvc cc config.cxx=cl
bdep update
bdep test
```
