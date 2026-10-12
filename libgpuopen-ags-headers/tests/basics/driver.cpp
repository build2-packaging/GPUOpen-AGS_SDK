#include <cstdlib>
#include <type_traits>

// amd_ags.h needs the Direct3D headers included first.
//
#include <d3d11.h>
#include <d3d12.h>

#include <amd_ags.h>

#undef NDEBUG
#include <cassert>

static void* __stdcall
allocate (size_t n)
{
  return std::malloc (n);
}

static void __stdcall
deallocate (void* p)
{
  std::free (p);
}

int main ()
{
  using namespace std;

  // Version macros.
  //
  static_assert (AGS_CURRENT_VERSION ==
                 AGS_MAKE_VERSION (AMD_AGS_VERSION_MAJOR,
                                   AMD_AGS_VERSION_MINOR,
                                   AMD_AGS_VERSION_PATCH));

  static_assert (AGS_MAKE_VERSION (6, 3, 1) == ((6 << 22) | (3 << 12) | 1));

  // The function pointer types that the entry points of the AGS DLL are
  // resolved with at runtime.
  //
  static_assert (is_same_v<decltype (&agsGetVersionNumber),
                           AGS_GETVERSIONNUMBER>);
  static_assert (is_same_v<decltype (&agsInitialize), AGS_INITIALIZE>);
  static_assert (is_same_v<decltype (&agsDeInitialize), AGS_DEINITIALIZE>);
  static_assert (is_same_v<decltype (&agsGetGPUInfo), AGS_GETGPUINFO>);
  static_assert (is_same_v<decltype (&agsDriverExtensionsDX12_CreateDevice),
                           AGS_DRIVEREXTENSIONSDX12_CREATEDEVICE>);
  static_assert (is_same_v<decltype (&agsDriverExtensionsDX11_CreateDevice),
                           AGS_DRIVEREXTENSIONSDX11_CREATEDEVICE>);

  // Configuration with user allocation callbacks.
  //
  {
    AGSConfiguration c {};
    assert (c.allocCallback == nullptr && c.freeCallback == nullptr);

    c.allocCallback = &allocate;
    c.freeCallback = &deallocate;

    void* p (c.allocCallback (16));
    assert (p != nullptr);
    c.freeCallback (p);
  }

  // GPU information.
  //
  {
    AGSDeviceInfo d {};
    d.asicFamily = AGSAsicFamily_RDNA4;
    d.numCUs = 64;

    AGSGPUInfo i {};
    i.numDevices = 1;
    i.devices = &d;

    assert (i.devices[0].asicFamily == AGSAsicFamily_RDNA4);
    assert (AGSAsicFamily_RDNA4 < AGSAsicFamily_Count);
    assert (AGS_SUCCESS == 0);
  }

  // Direct3D 12 device creation parameters.
  //
  {
    AGSDX12DeviceCreationParams c {};
    c.FeatureLevel = D3D_FEATURE_LEVEL_12_0;

    AGSDX12ExtensionParams e {};
    e.pAppName = L"driver";
    e.appVersion = AGS_MAKE_VERSION (1, 0, 0);

    AGSDX12ReturnedParams r {};
    ID3D12Device* d (r.pDevice);

    assert (c.FeatureLevel == D3D_FEATURE_LEVEL_12_0);
    assert (e.uavSlot == 0 && e.appVersion == (1 << 22));
    assert (d == nullptr && r.extensionsSupported.shaderClock == 0);
    assert (AGS_DX12_SHADER_INTRINSICS_SPACE_ID == 0x7FFF0ADE);
  }

  // Direct3D 11 device creation parameters.
  //
  {
    const D3D_FEATURE_LEVEL l[] = {D3D_FEATURE_LEVEL_11_0};

    AGSDX11DeviceCreationParams c {};
    c.DriverType = D3D_DRIVER_TYPE_HARDWARE;
    c.pFeatureLevels = l;
    c.FeatureLevels = 1;
    c.SDKVersion = D3D11_SDK_VERSION;

    AGSDX11ExtensionParams e {};
    e.crossfireMode = AGS_CROSSFIRE_MODE_DISABLE;

    AGSDX11ReturnedParams r {};
    ID3D11Device* d (r.pDevice);

    assert (c.pFeatureLevels[0] == D3D_FEATURE_LEVEL_11_0);
    assert (e.crossfireMode == AGS_CROSSFIRE_MODE_DISABLE);
    assert (d == nullptr && r.extensionsSupported.quadList == 0);

    static_assert (
      is_same_v<decltype (&agsDriverExtensionsDX11_IASetPrimitiveTopology),
                AGSReturnCode (*) (AGSContext*, D3D_PRIMITIVE_TOPOLOGY)>);

    assert (static_cast<D3D_PRIMITIVE_TOPOLOGY> (
              AGS_PRIMITIVE_TOPOLOGY_QUADLIST) !=
            D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);
  }
}
