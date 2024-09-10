IDXGIAdapter1*
DeviceManagerDx::GetDXGIAdapter()
{
  if (mAdapter) {
    return mAdapter;
  }

  nsModuleHandle dxgiModule(LoadLibrarySystem32(L"dxgi.dll"));
  decltype(CreateDXGIFactory1)* createDXGIFactory1 = (decltype(CreateDXGIFactory1)*)
    GetProcAddress(dxgiModule, "CreateDXGIFactory1");

  if (!createDXGIFactory1) {
    return nullptr;
  }

  // Try to use a DXGI 1.1 adapter in order to share resources
  // across processes.
  RefPtr<IDXGIFactory1> factory1;
  HRESULT hr = createDXGIFactory1(__uuidof(IDXGIFactory1),
                                  getter_AddRefs(factory1));
  if (FAILED(hr) || !factory1) {
    // This seems to happen with some people running the iZ3D driver.
    // They won't get acceleration.
    return nullptr;
  }

  if (!mDeviceStatus) {
    // If we haven't created a device yet, and have no existing device status,
    // then this must be the compositor device. Pick the first adapter we can.
    MOZ_ASSERT(ProcessOwnsCompositor());

    if (FAILED(factory1->EnumAdapters1(0, getter_AddRefs(mAdapter)))) {
      return nullptr;
    }
  } else {
    // In the UI and GPU process, we clear mDeviceStatus on device reset, so we
    // should never reach here. Furthermore, the UI process does not create
    // devices when using a GPU process.
    //
    // So, this should only ever get called on the content process.
    MOZ_ASSERT(XRE_IsContentProcess());

    // In the child process, we search for the adapter that matches the parent
    // process. The first adapter can be mismatched on dual-GPU systems.
    for (UINT index = 0; ; index++) {
      RefPtr<IDXGIAdapter1> adapter;
      if (FAILED(factory1->EnumAdapters1(index, getter_AddRefs(adapter)))) {
        break;
      }

      const DxgiAdapterDesc& preferred = mDeviceStatus->adapter();

      DXGI_ADAPTER_DESC desc;
      if (SUCCEEDED(adapter->GetDesc(&desc)) &&
          desc.AdapterLuid.HighPart == preferred.AdapterLuid.HighPart &&
          desc.AdapterLuid.LowPart == preferred.AdapterLuid.LowPart &&
          desc.VendorId == preferred.VendorId &&
          desc.DeviceId == preferred.DeviceId)
      {
        mAdapter = adapter.forget();
        break;
      }
    }
  }

  if (!mAdapter) {
    return nullptr;
  }

  // We leak this module everywhere, we might as well do so here as well.
  dxgiModule.disown();
  return mAdapter;
}