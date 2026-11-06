# libgpuopen-ags - AMD GPU Services (AGS) C++ library (prebuilt)

> **NOTE:**  
> This package does not contain any source code. Instead, in order to "build"
> the exported target(s) it downloads (tens of megabytes of) pre-built binaries
> provided by AMD for the target platform.
>
> Supported platforms/compilers are 64-bit Windows (MSVC and MinGW).

This is a `build2` package for the
[`AGS_SDK`](https://github.com/GPUOpen-LibrariesAndSDKs/AGS_SDK) C++ library.
It imports AMD's prebuilt AGS binaries for 64-bit Windows and re-exports the
headers from
[`libgpuopen-ags-headers`](https://github.com/build2-packaging/GPUOpen-AGS_SDK).

On `x86_64-windows` it provides the shared `amd_ags_x64.dll` plus import
library, and a static `amd_ags_x64_<year>_<MT|MD>[d].lib` matching the
MSVC toolset year and `cxx.mode`. Shared file names come from
`ags-binaries.build`. Binaries are downloaded at build time into
`config.libgpuopen_ags.cache` (not shipped). The static libraries are
MSVC object archives, which MinGW cannot link. Use `config.bin.lib=shared`
with MinGW.


## Usage

To start using `libgpuopen-ags` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libgpuopen-ags ^6.3.1
```

Then import the library in your `buildfile`:

```
import libs = libgpuopen-ags%lib{gpuopen-ags}
```


## Importable targets

This package provides the following importable targets:

```
lib{gpuopen-ags}
```


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.libgpuopen_ags.cache ?= $out_root
```

Download cache. Only a symlink is a target, so `b clean` keeps the files.
