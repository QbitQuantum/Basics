bool OnCreate(HWND hWnd)
{
    HRESULT hr = S_OK;

    // D3D機能レベルの一覧を用意
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_9_1;
    UINT deviceCreationFlag = 0;

    // D3D11デバイスおよびイメディエイトコンテキストの生成
    ComPtr<ID3D11Device> pDevice;
    ComPtr<ID3D11DeviceContext> pImmediateContext;
    hr = D3D11CreateDevice(
             nullptr,
             D3D_DRIVER_TYPE_HARDWARE,
             nullptr,
             deviceCreationFlag,
             featureLevels,
             _countof(featureLevels),
             D3D11_SDK_VERSION,
             pDevice.GetAddressOf(),
             &featureLevel,
             pImmediateContext.GetAddressOf()
         );
    if(FAILED(hr))
    {
        PrintSystemError(hr);
        return false;
    }

    // ID3D11Device2への変換
    hr = pDevice.As(&gpDevice);
    if(FAILED(hr))
    {
        PrintSystemError(hr);
        return false;
    }

    // ID3D11DeviceContext2への変換
    hr = pImmediateContext.As(&gpImmediateContext);
    if(FAILED(hr))
    {
        PrintSystemError(hr);
        return false;
    }

    // DXGIFactory4オブジェクトの取得
    ComPtr<IDXGIFactory4> pFactory;
    {
        ComPtr<IDXGIDevice> pDXGIDevice;
        hr = pDevice.As(&pDXGIDevice);
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        ComPtr<IDXGIAdapter> pDXGIAdapter;
        hr = pDXGIDevice->GetAdapter(pDXGIAdapter.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        hr = pDXGIAdapter->GetParent(IID_PPV_ARGS(pFactory.GetAddressOf()));
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // Alt + Enterによる全画面化の禁止
    pFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

    // SwapChainの生成
    {
        hr = pDevice.As(&gpDevice);
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        DXGI_SWAP_CHAIN_DESC1 SwapChainDesc {};
        SwapChainDesc.Width = Width;
        SwapChainDesc.Height = Height;
        SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        SwapChainDesc.SampleDesc.Count = 1;
        SwapChainDesc.SampleDesc.Quality = 0;
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        SwapChainDesc.BufferCount = 1;

        ComPtr<IDXGISwapChain1> pSwapChain;
        hr = pFactory->CreateSwapChainForHwnd(
                 gpDevice.Get(),
                 hWnd,
                 &SwapChainDesc,
                 nullptr,
                 nullptr,
                 pSwapChain.GetAddressOf()
             );
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        hr = pSwapChain.As(&gpSwapChain);
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // レンダーターゲットビュー (Render Target View : RTV)の生成と設定
    {
        ComPtr<ID3D11Texture2D> pBackBuffer;
        hr = gpSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        hr = gpDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, gpRTV.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // レンダーターゲットの設定
    gpImmediateContext->OMSetRenderTargets(1, gpRTV.GetAddressOf(), nullptr);

    // ビューポートの設定
    D3D11_VIEWPORT viewport {};
    viewport.Width = Width;
    viewport.Height = Height;
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    gpImmediateContext->RSSetViewports(1, &viewport);

    // 頂点シェーダの生成
    {
        ComPtr<ID3DBlob> pVertexShaderBlob;
        ComPtr<ID3DBlob> pErrorBlob;

        hr = D3DCompileFromFile(
                 L"012.hlsl",
                 nullptr,
                 nullptr,
                 "VS",
                 "vs_5_0",
                 0,
                 0,
                 pVertexShaderBlob.GetAddressOf(),
                 pErrorBlob.GetAddressOf()
             );
        if(FAILED(hr))
        {
            if(pErrorBlob)
            {
                cout << reinterpret_cast<char *>(pErrorBlob->GetBufferPointer()) << endl;
            }
            else
            {
                PrintSystemError(hr);
            }

            return false;
        }

        hr = gpDevice->CreateVertexShader(
                 pVertexShaderBlob->GetBufferPointer(),
                 pVertexShaderBlob->GetBufferSize(),
                 nullptr,
                 gpVertexShader.GetAddressOf()
             );
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        hr = gpDevice->CreateInputLayout(
                 layout,
                 _countof(layout),
                 pVertexShaderBlob->GetBufferPointer(),
                 pVertexShaderBlob->GetBufferSize(),
                 gpInputLayout.GetAddressOf()
             );
        if(FAILED(hr))
        {
            cout << static_cast<char *>(pErrorBlob->GetBufferPointer()) << endl;
            return false;
        }

        gpImmediateContext->IASetInputLayout(gpInputLayout.Get());
    }

    // ピクセルシェーダの生成
    {
        ComPtr<ID3DBlob> pPixelShaderBlob;
        ComPtr<ID3DBlob> pErrorBlob;

        hr = D3DCompileFromFile(
                 TEXT("012.hlsl"),
                 nullptr,
                 nullptr,
                 "PS",
                 "ps_5_0",
                 0,
                 0,
                 pPixelShaderBlob.GetAddressOf(),
                 pErrorBlob.GetAddressOf()
             );
        if(FAILED(hr))
        {
            if(pErrorBlob)
            {
                cout << reinterpret_cast<char *>(pErrorBlob->GetBufferPointer()) << endl;
            }
            else
            {
                PrintSystemError(hr);
            }
            return false;
        }

        hr = gpDevice->CreatePixelShader(
                 pPixelShaderBlob->GetBufferPointer(),
                 pPixelShaderBlob->GetBufferSize(),
                 nullptr,
                 gpPixelShader.GetAddressOf()
             );
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // 頂点バッファの生成
    {
        Vertex vertices[] =
        {
            { XMFLOAT3(-0.5f,  0.5f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
            { XMFLOAT3( 0.5f,  0.5f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
            { XMFLOAT3( 0.5f, -0.5f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
            { XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0.0f, 1.0f) }
        };

        D3D11_BUFFER_DESC BufferDesc {};
        BufferDesc.ByteWidth = sizeof vertices;
        BufferDesc.Usage = D3D11_USAGE_DEFAULT;
        BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        // BufferDesc.CPUAccessFlags = 0;
        // BufferDesc.MiscFlags = 0;
        // BufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA SubResourceData {};
        SubResourceData.pSysMem = vertices;
        // SubResourceData.SysMemPitch = 0;
        // SubResourceData.SysMemSlicePitch = 0;

        hr = gpDevice->CreateBuffer(&BufferDesc, &SubResourceData, gpVertexBuffer.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        UINT stride = sizeof vertices[0];
        UINT offset = 0;
        gpImmediateContext->IASetVertexBuffers(0, 1, gpVertexBuffer.GetAddressOf(), &stride, &offset);
        gpImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    // インデックスバッファの生成
    {
        WORD indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };

        D3D11_BUFFER_DESC BufferDesc {};
        BufferDesc.ByteWidth = sizeof indices;
        BufferDesc.Usage = D3D11_USAGE_DEFAULT;
        BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        // BufferDesc.CPUAccessFlags = 0;
        // BufferDesc.MiscFlags = 0;
        // BufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA SubResourceData {};
        SubResourceData.pSysMem = indices;
        // SubResourceData.SysMemPitch = 0;
        // SubResourceData.SysMemSlicePitch = 0;

        hr = gpDevice->CreateBuffer(&BufferDesc, &SubResourceData, gpIndexBuffer.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        gpImmediateContext->IASetIndexBuffer(gpIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    }

    // 定数バッファの生成
    {
        D3D11_BUFFER_DESC BufferDesc {};
        BufferDesc.ByteWidth = sizeof(ConstantBuffer);
        BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        hr = gpDevice->CreateBuffer(&BufferDesc, nullptr, gpConstantBuffer.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // テクスチャ生成
    {
        D3D11_TEXTURE2D_DESC Texture2DDesc {};
        Texture2DDesc.Width = 128;
        Texture2DDesc.Height = 128;
        Texture2DDesc.MipLevels = 1;
        Texture2DDesc.ArraySize = 1;
        Texture2DDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        Texture2DDesc.SampleDesc.Count = 1;
        Texture2DDesc.SampleDesc.Quality = 0;
        Texture2DDesc.Usage = D3D11_USAGE_IMMUTABLE;
        Texture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        // Texture2DDesc.CPUAccessFlags = 0;
        // Texture2DDesc.MiscFlags = 0;

        uint32_t texture[128][128];
        for(auto h = 0; h < 128; ++h)
        {
            for(auto w = 0; w < 128; ++w)
            {
                if((w & 1 + h & 1) & 1)
                {
                    texture[h][w] = ~0u;
                }
                else
                {
                    texture[h][w] = 0;
                }
            }
        }

        D3D11_SUBRESOURCE_DATA TextureData {};
        TextureData.pSysMem = texture;
        TextureData.SysMemPitch = 128 * 4;

        hr = gpDevice->CreateTexture2D(&Texture2DDesc, &TextureData, gpTexture.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        hr = gpDevice->CreateShaderResourceView(gpTexture.Get(), nullptr, gpTextureRV.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }

        D3D11_SAMPLER_DESC SamplerDesc {};
        SamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.MipLODBias = 0.0f;
        SamplerDesc.MaxAnisotropy = 2;
        SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        SamplerDesc.BorderColor[0] = 0.0f;
        SamplerDesc.BorderColor[1] = 0.0f;
        SamplerDesc.BorderColor[2] = 0.0f;
        SamplerDesc.BorderColor[3] = 0.0f;
        SamplerDesc.MinLOD = -FLT_MAX;
        SamplerDesc.MaxLOD = FLT_MAX;

        hr = gpDevice->CreateSamplerState(&SamplerDesc, gpSampler.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    // RasterizerStateの生成
    {
        D3D11_RASTERIZER_DESC2 RasterizerDesc {};
        // デフォルト設定
        // RasterizerDesc.FillMode = D3D11_FILL_SOLID;
        // RasterizerDesc.CullMode = D3D11_CULL_BACK;
        // RasterizerDesc.FrontCounterClockwise = FALSE;
        // RasterizerDesc.DepthBias = 0;
        // RasterizerDesc.DepthBiasClamp = 0.0f;
        // RasterizerDesc.SlopeScaledDepthBias = 0.0f;
        // RasterizerDesc.DepthClipEnable = TRUE;
        // RasterizerDesc.ScissorEnable = FALSE;
        // RasterizerDesc.MultisampleEnable = FALSE;
        // RasterizerDesc.AntialiasedLineEnable = FALSE;
        // RasterizerDesc.ForcedSampleCount = 0;
        // RasterizerDesc.ConservativeRaster = D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        RasterizerDesc.FillMode = D3D11_FILL_SOLID;
        RasterizerDesc.CullMode = D3D11_CULL_NONE;
        RasterizerDesc.FrontCounterClockwise = FALSE;
        RasterizerDesc.DepthBias = 0;
        RasterizerDesc.DepthBiasClamp = 0.0f;
        RasterizerDesc.SlopeScaledDepthBias = 0.0f;
        RasterizerDesc.DepthClipEnable = TRUE;
        RasterizerDesc.ScissorEnable = FALSE;
        RasterizerDesc.MultisampleEnable = FALSE;
        RasterizerDesc.AntialiasedLineEnable = FALSE;
        RasterizerDesc.ForcedSampleCount = 0;
        RasterizerDesc.ConservativeRaster = D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;

        hr = gpDevice->CreateRasterizerState2(&RasterizerDesc, gpRasterizerState.GetAddressOf());
        if(FAILED(hr))
        {
            PrintSystemError(hr);
            return false;
        }
    }

    return true;
}