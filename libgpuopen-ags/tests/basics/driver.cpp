#include <cstdio>
#include <cstdlib>

// amd_ags.h needs the Direct3D headers included first.
//
#include <d3d11.h>
#include <d3d12.h>

#include <amd_ags.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  assert (agsGetVersionNumber () == AGS_CURRENT_VERSION);

  AGSContext* context (nullptr);
  AGSGPUInfo info {};
  const AGSReturnCode r (
    agsInitialize (AGS_CURRENT_VERSION, nullptr, &context, &info));

  if (r != AGS_SUCCESS || info.numDevices == 0)
  {
    std::printf ("agsInitialize: %d, %d device(s), skipping GPU info\n",
                 r, r == AGS_SUCCESS ? info.numDevices : 0);

    if (r == AGS_SUCCESS)
      assert (agsDeInitialize (context) == AGS_SUCCESS);

    return 0;
  }

  assert (context != nullptr);
  assert (info.devices != nullptr);

  AGSGPUInfo info2 {};
  assert (agsGetGPUInfo (context, &info2) == AGS_SUCCESS);
  assert (info2.numDevices == info.numDevices);
  assert (info2.devices != nullptr);

  for (int i (0); i < info.numDevices; ++i)
  {
    const AGSDeviceInfo& d (info.devices[i]);

    assert (d.adapterString != nullptr);
    assert (d.asicFamily >= AGSAsicFamily_Unknown);
    assert (d.asicFamily < AGSAsicFamily_Count);

    if (d.vendorId == 0x1002)
      assert (d.deviceId != 0);

    std::printf ("%s (vendor 0x%04X device 0x%04X)\n",
                 d.adapterString, d.vendorId, d.deviceId);
  }

  assert (agsDeInitialize (context) == AGS_SUCCESS);
  return 0;
}
