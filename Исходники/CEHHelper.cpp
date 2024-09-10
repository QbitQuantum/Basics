bool
IsDX10Available()
{
  DWORD isDX10Available;
  if (GetDWORDRegKey(metroDX10Available, isDX10Available)) {
    return isDX10Available;
  }

  HMODULE dxgiModule = LoadLibraryA("dxgi.dll");
  if (!dxgiModule) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }
  CreateDXGIFactory1Func createDXGIFactory1 =
    (CreateDXGIFactory1Func) GetProcAddress(dxgiModule, "CreateDXGIFactory1");
  if (!createDXGIFactory1) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }

  HMODULE d3d10module = LoadLibraryA("d3d10_1.dll");
  if (!d3d10module) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }
  D3D10CreateDevice1Func createD3DDevice =
    (D3D10CreateDevice1Func) GetProcAddress(d3d10module,
                                            "D3D10CreateDevice1");
  if (!createD3DDevice) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }

  CComPtr<IDXGIFactory1> factory1;
  if (FAILED(createDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory1))) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }

  CComPtr<IDXGIAdapter1> adapter1;
  if (FAILED(factory1->EnumAdapters1(0, &adapter1))) {
    SetDWORDRegKey(metroDX10Available, 0);
    return false;
  }

  CComPtr<ID3D10Device1> device;
  // Try for DX10.1
  if (FAILED(createD3DDevice(adapter1, D3D10_DRIVER_TYPE_HARDWARE, nullptr,
                             D3D10_CREATE_DEVICE_BGRA_SUPPORT |
                             D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
                             D3D10_FEATURE_LEVEL_10_1,
                             D3D10_1_SDK_VERSION, &device))) {
    // Try for DX10
    if (FAILED(createD3DDevice(adapter1, D3D10_DRIVER_TYPE_HARDWARE, nullptr,
                               D3D10_CREATE_DEVICE_BGRA_SUPPORT |
                               D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
                               D3D10_FEATURE_LEVEL_10_0,
                               D3D10_1_SDK_VERSION, &device))) {
      // Try for DX9.3 (we fall back to cairo and cairo has support for D3D 9.3)
      if (FAILED(createD3DDevice(adapter1, D3D10_DRIVER_TYPE_HARDWARE, nullptr,
                                 D3D10_CREATE_DEVICE_BGRA_SUPPORT |
                                 D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
                                 D3D10_FEATURE_LEVEL_9_3,
                                 D3D10_1_SDK_VERSION, &device))) {

        SetDWORDRegKey(metroDX10Available, 0);
        return false;
      }
    }
  }
  

  SetDWORDRegKey(metroDX10Available, 1);
  return true;
}