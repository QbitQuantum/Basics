BOOL TRenderDevice::CreateRenderDevice(){
	HRESULT  hr;
	RenderSize = new TD3DRenderSize();
	
	if(RenderWindow!=0){
		RenderWindow->CreateNativeWindow();
		SetWindowLong(RenderWindow->GetHWnd(), GWL_USERDATA, (LONG)this);
		RenderWindow->SetWindowSize(RenderSize->GetRenderWidth(),RenderSize->GetRenderHeight());
	}
	
#if defined(DEBUG) || defined(_DEBUG)
	m_CreateFlags|=D3D10_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL pFeatureLevels[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};
	
	hr = D3D11CreateDevice(0,D3D_DRIVER_TYPE_HARDWARE,0,m_CreateFlags,
						pFeatureLevels,
						6,
						D3D11_SDK_VERSION,
						&Device,
						&m_OutFeatureLevel,
						&DeviceContext);
	if(FAILED(hr)){
		MessageBox(0,L"创建设备失败",0,0);
		return S_FALSE;
	}
	if(m_OutFeatureLevel!=D3D_FEATURE_LEVEL_11_0){
		MessageBox(0,L"m_OutFeatureLevel!=D3D_FEATURE_LEVEL_11_0",0,0);
	}
	
	Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MsaaQuality);
	assert(MsaaQuality>0);
	
	CreateSwapChain();
	
	RenderTarget = new TRenderTarget(this);
	ViewPort = new TViewPort(this);
	ViewPort->ApplyViewPort();
	
	return S_OK;
}