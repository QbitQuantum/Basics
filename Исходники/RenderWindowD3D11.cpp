RenderWindow::RenderWindow(Renderer* aRenderer, HWND hWnd, int aWidth, int aHeight, int flags)
	: RenderTarget(aRenderer->device(), aWidth, aHeight)
	, mHwnd(hWnd)
	, mInitFlags(flags)
{
	assert(mHwnd);

	mHwnd = hWnd;

	RECT rect;
	GetClientRect(hWnd, &rect);

	// these typically will be the same as aWidth and aHeight, which are by now stored in mWidth and mHeight
	// but it's possible that the user for some reason wants different dimensions, so let them
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	DXGI_SWAP_EFFECT effect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // Win8 and greater
	if (!IsWindows8OrGreater())
		effect = DXGI_SWAP_EFFECT_DISCARD; // Win7 and Vista, and possibly XP

	DXGI_SWAP_CHAIN_DESC desc = { 0 };
	desc.BufferCount = 2;
	desc.SwapEffect = effect;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	ComPtr<IDXGIFactory> factory = aRenderer->factory();
	assert(factory);
	if (!factory)
		throw InvalidParameterException("Invalid 'factory' renderer property in Direct3D11::RenderWindow");

	HRESULT hr = E_FAIL;

	if (factory) {
		hr = factory->CreateSwapChain(
			mDevice.Get(),
			&desc,
			&mSwapChain
			);
	}

	if (FAILED(hr) || !mSwapChain)
		throw Exception("Could not create swap chain in Direct3D11::RenderWindow");

	hr = mSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		&mBackBuffer
		);

	if (FAILED(hr))
		throw Exception("Could not obtain back buffer from swap chain in Direct3D11::RenderWindow");

	hr = mDevice->CreateRenderTargetView(
		mBackBuffer.Get(),
		nullptr,
		&mRenderTargetView
		);

	if (FAILED(hr))
		throw Exception("Could not create render target view in Direct3D11::RenderWindow");

	mBackBuffer->GetDesc(&mDesc);
}