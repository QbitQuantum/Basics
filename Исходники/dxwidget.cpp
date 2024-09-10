// Create Direct3D device and swap chain
HRESULT DxWidget::InitDevice()
{
	HRESULT hrResult = E_FAIL;
	HRESULT hrRetCode = E_FAIL;

	m_driverType = D3D10_DRIVER_TYPE_NULL;

    UINT createDeviceFlags = 0;

    D3D10_DRIVER_TYPE driverTypes[] =
    {
        D3D10_DRIVER_TYPE_HARDWARE,
        D3D10_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

    ZeroMemory(&m_swapChainDesc, sizeof(m_swapChainDesc));
    m_swapChainDesc.BufferCount = 1;
	m_swapChainDesc.BufferDesc.Width = width();
    m_swapChainDesc.BufferDesc.Height = height();
    m_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_swapChainDesc.OutputWindow = (HWND)winId();
    m_swapChainDesc.SampleDesc.Count = 1;
    m_swapChainDesc.SampleDesc.Quality = 0;
    m_swapChainDesc.Windowed = TRUE;
	
    for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex];
        hrRetCode = D3D10CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags,
			D3D10_SDK_VERSION, &m_swapChainDesc, &m_pSwapChain, &m_pd3dDevice);

        if(SUCCEEDED(hrRetCode))
            break;
    }
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pSwapChain);
	KE_PROCESS_ERROR(m_pd3dDevice);

    // Create a render target view
    ID3D10Texture2D* pBackBuffer;
    hrRetCode = m_pSwapChain->GetBuffer(0, __uuidof( ID3D10Texture2D ), ( LPVOID* )&pBackBuffer);
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(pBackBuffer);

    hrRetCode = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pRenderTargetView);
	
    m_pd3dDevice->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

    // Setup the viewport
    m_viewPort.Width = width();
    m_viewPort.Height = height();
    m_viewPort.MinDepth = 0.0f;
    m_viewPort.MaxDepth = 1.0f;
    m_viewPort.TopLeftX = 0;
    m_viewPort.TopLeftY = 0;
    m_pd3dDevice->RSSetViewports(1, &m_viewPort);

	 // Create the effect
    DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

    hrRetCode = D3DX10CreateEffectFromFile(L"testqt.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0,
		m_pd3dDevice, NULL, NULL, &m_pEffect, NULL, NULL );
	KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pEffect);

    // Obtain the technique
    m_pTechnique = m_pEffect->GetTechniqueByName("Render");

    // Define the input layout
    D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT numElements = sizeof(layout) / sizeof(layout[0]);

    // Create the input layout
    D3D10_PASS_DESC PassDesc;
    m_pTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
    hrRetCode = m_pd3dDevice->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &m_pVertexLayout);
    KE_COM_PROCESS_ERROR(hrRetCode);
	KE_PROCESS_ERROR(m_pVertexLayout);

    // Set the input layout
    m_pd3dDevice->IASetInputLayout(m_pVertexLayout);
	// Set primitive topology
    m_pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	hrResult = S_OK;
Exit0:
	return hrResult;
}