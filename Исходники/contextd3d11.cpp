int ContextD3D11::CreateDeviceResources() {
  UINT creationFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;//D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
  creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driverTypes[] =
  {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE( driverTypes );

  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_12_1,
    D3D_FEATURE_LEVEL_12_0,
    D3D_FEATURE_LEVEL_11_1,
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };
  UINT numFeatureLevels = ARRAYSIZE( featureLevels );
  D3D_FEATURE_LEVEL feature_level;
  ID3D11Device* device;
  ID3D11DeviceContext* devicecontext;

  auto hr = D3D11CreateDevice(adaptor_, D3D_DRIVER_TYPE_UNKNOWN, nullptr,	creationFlags, featureLevels, ARRAYSIZE(featureLevels),	D3D11_SDK_VERSION, &device, &feature_level, &devicecontext);
  if (FAILED(hr)) {
    OutputDebugString("ContextD3D11::CreateDeviceResources : D3D11CreateDevice Failed");
    return hr;
  }
  device_ = (ID3D11Device1*)device;
  device_context_ = (ID3D11DeviceContext1*)devicecontext;

  SafeRelease(&default_blend_state);
  D3D11_BLEND_DESC BlendStateDescription;
  ZeroMemory(&BlendStateDescription,sizeof(BlendStateDescription));
  BlendStateDescription.RenderTarget[0].BlendEnable           = true;
  BlendStateDescription.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;        //D3D11_BLEND_SRC_COLOR;
  BlendStateDescription.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;//D3D11_BLEND_DEST_COLOR;
  BlendStateDescription.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_SRC_ALPHA;//D3D11_BLEND_SRC_ALPHA;
  BlendStateDescription.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;//D3D11_BLEND_DEST_ALPHA;
  BlendStateDescription.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
  BlendStateDescription.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
  BlendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
  device_->CreateBlendState(&BlendStateDescription,&default_blend_state);
  float blendFactor[] = {1,1, 1, 1};
  UINT sampleMask   = 0xffffffff;
  device_context_->OMSetBlendState(default_blend_state,blendFactor,sampleMask);


  

  return S_OK;
}