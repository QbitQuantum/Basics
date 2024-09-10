bool Init_Device()
{
	//Set up DX swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory( &swapChainDesc, sizeof(swapChainDesc) );

	//set buffer dimensions and format
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = GAME_RESOLUTION_X;
	swapChainDesc.BufferDesc.Height = GAME_RESOLUTION_Y;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;

	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = Window_GetHWND();
	swapChainDesc.Windowed = !FULL_SCREEN;

	//Create the D3D device
	if ( FAILED( D3D10CreateDeviceAndSwapChain(	NULL,D3D10_DRIVER_TYPE_HARDWARE,NULL,0,D3D10_SDK_VERSION,&swapChainDesc,&dx_swap_chain,&dx_device) ) )
			return false;

	//try to get the back buffer
	ID3D10Texture2D* pBackBuffer;

	if ( FAILED( dx_swap_chain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer) ) ) return false;

	//try to create render target view
	if ( FAILED( dx_device->CreateRenderTargetView(pBackBuffer, NULL, &dx_render_target) ) ) return false;

	//release the back buffer
	pBackBuffer->Release();

	//set the render target
	dx_device->OMSetRenderTargets(1, &dx_render_target, NULL);

	//create viewport structure
	dx_viewport.Width = GAME_RESOLUTION_X;
	dx_viewport.Height = GAME_RESOLUTION_Y;
	dx_viewport.MinDepth = 0.0f;
	dx_viewport.MaxDepth = 1.0f;
	dx_viewport.TopLeftX = 0;
	dx_viewport.TopLeftY = 0;

	//set the viewport
	dx_device->RSSetViewports(1, &dx_viewport);

	//setup blend state
	D3D10_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D10_BLEND_DESC));

	BlendState.BlendEnable[0] = TRUE;

	BlendState.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	BlendState.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	BlendState.BlendOp = D3D10_BLEND_OP_ADD;

	BlendState.SrcBlendAlpha = D3D10_BLEND_ONE;
	BlendState.DestBlendAlpha = D3D10_BLEND_ONE;
	BlendState.BlendOpAlpha = D3D10_BLEND_OP_ADD;

	BlendState.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	dx_device->CreateBlendState(&BlendState, &dx_AlphaBlendState);

	//set blend state
	dx_device->OMSetBlendState(dx_AlphaBlendState, 0, 0xfffffff);

	return true;
}