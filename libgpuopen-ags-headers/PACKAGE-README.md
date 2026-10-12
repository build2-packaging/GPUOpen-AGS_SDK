# libgpuopen-ags-headers - AMD GPU Services (AGS) C++ API headers

This is a `build2` package for the
[`AGS_SDK`](https://github.com/GPUOpen-LibrariesAndSDKs/AGS_SDK) C++ library.
It provides the header of the AMD GPU Services (AGS) library, which gives
applications access to AMD GPU software and hardware state information that
is not normally available through standard operating systems or graphics
APIs, such as the driver version and GPU architecture, as well as to the AMD
driver extensions for Direct3D 11 and 12.


## Usage

To start using `libgpuopen-ags-headers` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libgpuopen-ags-headers ^6.3.1
```

Then import the library in your `buildfile`:

```
import libs = libgpuopen-ags-headers%lib{gpuopen-ags-headers}
```


## Importable targets

This package provides the following importable targets:

```
lib{gpuopen-ags-headers}
```

The AGS header, included without a subdirectory prefix
(`#include <amd_ags.h>`). The HLSL shader intrinsics for the AGS shader
extensions (`ags_shader_intrinsics_dx11.hlsl` and
`ags_shader_intrinsics_dx12.hlsl`) are installed next to it.

This package is headers only. Upstream ships the AGS library itself only as
prebuilt binaries (`amd_ags_x64.dll` with its import and static libraries),
which this package does not provide, so the `ags*()` functions declared in
`amd_ags.h` cannot be linked against. They can instead be resolved at
runtime from an `amd_ags_x64.dll` with `GetProcAddress()`, using the function
pointer types declared in the header (`AGS_INITIALIZE` and so on). Note that
`agsInitialize()` fails unless the DLL is of the same version as the header.

As in upstream, the header targets Windows and relies on `<windows.h>` being
included first. Its forward declarations of the Direct3D enums are a
Microsoft extension, so with MinGW GCC the Direct3D headers (`<d3d11.h>`,
`<d3d12.h>`, or at least `<d3dcommon.h>`) must be included before
`<amd_ags.h>`.


## Configuration variables

This package provides no configuration variables.
