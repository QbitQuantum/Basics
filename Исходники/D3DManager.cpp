bool D3DManager::Resize(int screenWidth, int screenHeight, float screenDepth, float screenNear)
{
	if(m_swapChain) {
		m_deviceContext->OMSetRenderTargets(0, 0, 0);

        // Release all outstanding references to the swap chain's buffers.
        m_renderTargetView->Release();

        HRESULT result;
        // Preserve the existing buffer count and format.
        // Automatically choose the width and height to match the client rect for HWNDs.
        result = m_swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);                                        
        if(FAILED(result))
		{
			log_sxerror("D3DManager", "Failed to resize our buffers.");
			return false;
		}

        // Get buffer and create a render-target-view.
        ID3D11Texture2D* pBuffer;
        result = m_swapChain->GetBuffer(0, __uuidof( ID3D11Texture2D),
                                        (void**) &pBuffer );
        if(FAILED(result))
		{
			log_sxerror("D3DManager", "Failed to get a pointer to the back buffer.");
			return false;
		}

        result = m_device->CreateRenderTargetView(pBuffer, NULL,
                                                    &m_renderTargetView);
        if(FAILED(result))
		{
			log_sxerror("D3DManager", "Failed to recreate the render target view.");
			return false;
		}

        pBuffer->Release();

        m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL );

		// Setup the viewport for rendering.
		D3D11_VIEWPORT viewport;
        viewport.Width = (float)screenWidth;
        viewport.Height = (float)screenHeight;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;

        // Create the viewport.
        m_deviceContext->RSSetViewports(1, &viewport);

		 // Setup the projection matrix.
		float fieldOfView = (float)XM_PI / 4.0f;
		assert(screenWidth != 0);
		assert(screenHeight != 0);
        float screenAspect = (float)screenWidth / (float)screenHeight;

        // Create the projection matrix for 3D rendering.
        XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth));

        // Initialize the world and view matrix to the identity matrix.
        XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
		XMStoreFloat4x4(&m_viewMatrix, XMMatrixIdentity());

        // Create an orthographic projection matrix for 2D rendering.
        XMStoreFloat4x4(&m_orthoMatrix, XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth));

		// Store our screen dimensions
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;
	}

	return true;
}