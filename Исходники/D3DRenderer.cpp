void D3DRenderer::OnResize(UINT newHeight, UINT newWidth)
{
	mWindowHeight = newHeight;
	mWindowWidth = newWidth;

	//Release old COM interfaces.
	ReleaseCOM(mDepthStencilBuffer);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mRenderTargetView);

	//Resize the buffers to the new sizes and rebind them to the pipeline through
	//the RenderTargetView.
	HR(mSwapChain->ResizeBuffers(1, mWindowWidth, mWindowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	ReleaseCOM(backBuffer);

	//Description for the Depth Stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	//Defining the buffer
	depthStencilDesc.Height = mWindowHeight;
	depthStencilDesc.Width = mWindowWidth;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//The MSAA settings for the depthStencilDesc MUST match the SwapChain.
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	//Other options
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	
	//Actually create the DepthStencilView
	md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView);

	//Bind the Render target and DepthStencilView to the pipline
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	mScreenViewport.TopLeftX = 0.0f;
	mScreenViewport.TopLeftY = 0.0f;
	mScreenViewport.Width = static_cast<float>(newWidth);
	mScreenViewport.Height = static_cast<float>(newHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;
	
	mDeviceContext->RSSetViewports(1, &mScreenViewport);
	
	mProjMatrix = XMMatrixPerspectiveFovLH(0.25f*3.14f, newWidth/newHeight, 1.0f, 1000.0f);
}