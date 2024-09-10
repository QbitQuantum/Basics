bool PngViewer::init_d2d()
{
	DXGI_SWAP_CHAIN_DESC1 swap_descriptor;
	RECT client_rect;
	ID3D11Device * device;
	IDXGISwapChain1 * swap_chain_1;
	HRESULT r;

	if(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, &device, nullptr, nullptr) != S_OK)
	{
		return false;
	}
	r = device->QueryInterface(__uuidof(IDXGIDevice3), (void **)&this->device_gi);
	device->Release();
	if(r != S_OK)
	{
		return false;
	}

	if(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, __uuidof(IDXGIFactory3), (void **)&this->gi_factory) != S_OK)
	{
		return false;
	}

	::GetClientRect(this->window, &client_rect);
	this->swap_chain_region.cx = client_rect.right - client_rect.left;
	this->swap_chain_region.cy = client_rect.bottom - client_rect.top;

	::memset(&swap_descriptor, 0, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swap_descriptor.Width = this->swap_chain_region.cx;
	swap_descriptor.Height = this->swap_chain_region.cy;
	swap_descriptor.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_descriptor.SampleDesc.Count = 1;
	swap_descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_descriptor.BufferCount = 2;
	swap_descriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swap_descriptor.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

	if(this->gi_factory->CreateSwapChainForComposition(this->device_gi, &swap_descriptor, nullptr, &swap_chain_1) != S_OK)
	{
		return false;
	}

	r = swap_chain_1->QueryInterface(__uuidof(IDXGISwapChain2), (void **)&this->swap_chain);
	swap_chain_1->Release();
	if(r != S_OK)
	{
		return false;
	}

	if(DCompositionCreateDevice(this->device_gi, __uuidof(IDCompositionDevice), (void **)&this->comp_device) != S_OK)
	{
		return false;
	}

	if(this->comp_device->CreateTargetForHwnd(this->window, true, &this->comp_target) != S_OK)
	{
		return false;
	}

	if(this->comp_device->CreateVisual(&this->comp_visual) != S_OK)
	{
		return false;
	}

	this->comp_visual->SetContent(this->swap_chain);
	this->comp_target->SetRoot(this->comp_visual);
	this->comp_device->Commit();

	return true;
}