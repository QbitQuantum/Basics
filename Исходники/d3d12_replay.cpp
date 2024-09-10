ReplayCreateStatus D3D12_CreateReplayDevice(const char *logfile, IReplayDriver **driver)
{
  RDCDEBUG("Creating a D3D12 replay device");

  WrappedIDXGISwapChain3::RegisterD3DDeviceCallback(GetD3D12DeviceIfAlloc);

  HMODULE lib = NULL;
  lib = LoadLibraryA("d3d12.dll");
  if(lib == NULL)
  {
    RDCERR("Failed to load d3d12.dll");
    return eReplayCreate_APIInitFailed;
  }

  lib = LoadLibraryA("dxgi.dll");
  if(lib == NULL)
  {
    RDCERR("Failed to load dxgi.dll");
    return eReplayCreate_APIInitFailed;
  }

  if(GetD3DCompiler() == NULL)
  {
    RDCERR("Failed to load d3dcompiler_??.dll");
    return eReplayCreate_APIInitFailed;
  }

  D3D12InitParams initParams;
  RDCDriver driverFileType = RDC_D3D12;
  string driverName = "D3D12";
  if(logfile)
  {
    auto status = RenderDoc::Inst().FillInitParams(logfile, driverFileType, driverName,
                                                   (RDCInitParams *)&initParams);
    if(status != eReplayCreate_Success)
      return status;
  }

  // initParams.SerialiseVersion is guaranteed to be valid/supported since otherwise the
  // FillInitParams (which calls D3D12InitParams::Serialise) would have failed above, so no need to
  // check it here.

  if(initParams.MinimumFeatureLevel < D3D_FEATURE_LEVEL_11_0)
    initParams.MinimumFeatureLevel = D3D_FEATURE_LEVEL_11_0;

  ID3D12Device *dev = NULL;
  HRESULT hr = RENDERDOC_CreateWrappedD3D12Device(NULL, initParams.MinimumFeatureLevel,
                                                  __uuidof(ID3D12Device), (void **)&dev);

  if(FAILED(hr))
  {
    RDCERR("Couldn't create a d3d12 device :(.");

    return eReplayCreate_APIHardwareUnsupported;
  }

  WrappedID3D12Device *wrappedDev = (WrappedID3D12Device *)dev;
  if(logfile)
    wrappedDev->SetLogFile(logfile);
  wrappedDev->SetLogVersion(initParams.SerialiseVersion);

  RDCLOG("Created device.");
  D3D12Replay *replay = wrappedDev->GetReplay();

  replay->SetProxy(logfile == NULL);

  *driver = (IReplayDriver *)replay;
  return eReplayCreate_Success;
}