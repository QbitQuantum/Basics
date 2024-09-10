bool RendererDX11::LoadContent(HWND windowHandle)
{
    assert(m_d3dDevice);
    
    InitFractalCube(startSize, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), 0);

    for (auto i = 0; i < m_meshes.size(); ++i)
    {
        m_meshes[i]->InitializeBuffers(m_d3dDevice);
    }
    
    m_camera = Camera();

    HRESULT hr;
    // Load the compiled vertex shader.
    ID3DBlob* vertexShaderBlob;
    LPCWSTR compiledVertexShaderObject = L"SimpleVertexShader.cso";
    // Load the compiled pixel shader.
    ID3DBlob* pixelShaderBlob;
    LPCWSTR compiledPixelShaderObject = L"SimplePixelShader.cso";

    hr = D3DReadFileToBlob(compiledVertexShaderObject, &vertexShaderBlob);
    if (FAILED(hr))
    {
        return false;
    }

    hr = D3DReadFileToBlob(compiledPixelShaderObject, &pixelShaderBlob);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_d3dDevice->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &m_d3dVertexShader);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_d3dDevice->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &m_d3dPixelShader);
    if (FAILED(hr))
    {
        return false;
    }

    // Create the input layout for the vertex shader.
    D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosColor,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosColor,Color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    hr = m_d3dDevice->CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_d3dInputLayout);
    if (FAILED(hr))
    {
        return false;
    }

    SafeRelease(vertexShaderBlob);
    SafeRelease(pixelShaderBlob);

    // Create the constant buffers for the variables defined in the vertex shader.
    D3D11_BUFFER_DESC constantBufferDesc;
    ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
    constantBufferDesc.CPUAccessFlags = 0;
    constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    hr = m_d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_d3dConstantBuffers[CB_Appliation]);
    if (FAILED(hr))
    {
        return false;
    }
    hr = m_d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_d3dConstantBuffers[CB_Frame]);
    if (FAILED(hr))
    {
        return false;
    }
    hr = m_d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_d3dConstantBuffers[CB_Object]);
    if (FAILED(hr))
    {
        return false;
    }

    // Setup the projection matrix.
    RECT clientRect;
    GetClientRect(windowHandle, &clientRect);

    // Compute the exact client dimensions.
    // This is required for a correct projection matrix.
    float clientWidth = static_cast<float>(clientRect.right - clientRect.left);
    float clientHeight = static_cast<float>(clientRect.bottom - clientRect.top);

    m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), clientWidth / clientHeight, 0.1f, 100.0f);

    m_d3dDeviceContext->UpdateSubresource(m_d3dConstantBuffers[CB_Appliation], 0, nullptr, &m_projectionMatrix, 0, 0);

    return true;
}