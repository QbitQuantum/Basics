void DirectXMesh::CreateDevice() {
  mMesh = NULL;
  pd3d9 = NULL;
  pd3d9Device = NULL;

  HRESULT hr;

  pd3d9 = Direct3DCreate9(D3D_SDK_VERSION);

  D3DPRESENT_PARAMETERS fakeParams;
  fakeParams.BackBufferWidth = 320;
  fakeParams.BackBufferHeight = 240;
  fakeParams.BackBufferFormat = D3DFMT_X8R8G8B8;
  fakeParams.BackBufferCount = 1;
  fakeParams.MultiSampleType = D3DMULTISAMPLE_NONE;
  fakeParams.MultiSampleQuality = 0;
  fakeParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
  fakeParams.hDeviceWindow = GetShellWindow();
  fakeParams.Windowed = true;
  fakeParams.Flags = 0;
  fakeParams.FullScreen_RefreshRateInHz = 0;
  fakeParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
  fakeParams.EnableAutoDepthStencil = false;

  hr = pd3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL,
                           D3DCREATE_SOFTWARE_VERTEXPROCESSING, &fakeParams,
                           &pd3d9Device);
  if(FAILED(hr))
  {
    hr = pd3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, NULL,
                             D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                             &fakeParams, &pd3d9Device);
    if(FAILED(hr))
    {
      SAFE_RELEASE( pd3d9 )
    }
  }
}