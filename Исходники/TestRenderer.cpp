bool TestRenderer::Initialize()
{
    UINT d3dFlag = 0;
#if defined(_DEBUG)
    d3dFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        d3dFlag, &featureLevel, 1, D3D11_SDK_VERSION, &Device, nullptr, &Context);
    if (FAILED(hr))
    {
        // Did it fail because we're requesting the debug layer and it's not present on this machine?
        if (d3dFlag == D3D11_CREATE_DEVICE_DEBUG && hr == DXGI_ERROR_SDK_COMPONENT_MISSING)
        {
            // Try again without debug layer
            d3dFlag &= ~D3D11_CREATE_DEVICE_DEBUG;
            hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                d3dFlag, &featureLevel, 1, D3D11_SDK_VERSION, &Device, nullptr, &Context);
        }

        if (FAILED(hr))
        {
            LogError(L"Failed to create D3D11 device.");
            return false;
        }
    }

    UINT dxgiFlag = 0;
#if defined(_DEBUG)
    dxgiFlag |= DXGI_CREATE_FACTORY_DEBUG;
#endif

    ComPtr<IDXGIFactory> factory;
    hr = CreateDXGIFactory2(dxgiFlag, IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        LogError(L"Failed to create DXGI factory.");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd{};
    scd.BufferCount = 2;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
#if USE_SRGB
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
#else
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
#endif
    scd.SampleDesc.Count = 4;
    scd.OutputWindow = Window;
    scd.Windowed = TRUE;

    hr = factory->CreateSwapChain(Device.Get(), &scd, &SwapChain);
    if (FAILED(hr))
    {
        LogError(L"Failed to create swapchain.");
        return false;
    }

    ComPtr<ID3D11Texture2D> texture;
    hr = SwapChain->GetBuffer(0, IID_PPV_ARGS(&texture));
    if (FAILED(hr))
    {
        LogError(L"Failed to get backbuffer.");
        return false;
    }

    hr = Device->CreateRenderTargetView(texture.Get(), nullptr, &RenderTarget);
    if (FAILED(hr))
    {
        LogError(L"Failed to get backbuffer.");
        return false;
    }

    D3D11_TEXTURE2D_DESC td{};
    texture->GetDesc(&td);
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    td.Format = DXGI_FORMAT_D32_FLOAT;
    hr = Device->CreateTexture2D(&td, nullptr, texture.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        LogError(L"Failed to create depth texture.");
        return false;
    }

    hr = Device->CreateDepthStencilView(texture.Get(), nullptr, &DepthBuffer);
    if (FAILED(hr))
    {
        LogError(L"Failed to create depth stencil view.");
        return false;
    }

    hr = Device->CreateVertexShader(SimpleTransformVS, sizeof(SimpleTransformVS), nullptr, &VertexShader);
    if (FAILED(hr))
    {
        LogError(L"Failed to create vertex shader.");
        return false;
    }

    hr = Device->CreatePixelShader(SimpleTexturePS, sizeof(SimpleTexturePS), nullptr, &PixelShader);
    if (FAILED(hr))
    {
        LogError(L"Failed to create pixel shader.");
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC elems[5] {};
    elems[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    elems[0].SemanticName = "POSITION";
    elems[1].AlignedByteOffset = sizeof(XMFLOAT3);
    elems[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    elems[1].SemanticName = "NORMAL";
    elems[2].AlignedByteOffset = sizeof(XMFLOAT3) * 2;
    elems[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    elems[2].SemanticName = "TANGENT";
    elems[3].AlignedByteOffset = sizeof(XMFLOAT3) * 2;
    elems[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    elems[3].SemanticName = "BITANGENT";
    elems[4].AlignedByteOffset = sizeof(XMFLOAT3) * 4;
    elems[4].Format = DXGI_FORMAT_R32G32_FLOAT;
    elems[4].SemanticName = "TEXCOORD";

    hr = Device->CreateInputLayout(elems, _countof(elems), SimpleTransformVS, sizeof(SimpleTransformVS), &InputLayout);
    if (FAILED(hr))
    {
        LogError(L"Failed to create input layout.");
        return false;
    }

    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.ByteWidth = sizeof(Constants);
    bd.StructureByteStride = bd.ByteWidth;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = Device->CreateBuffer(&bd, nullptr, &ConstantBuffer);
    if (FAILED(hr))
    {
        LogError(L"Failed to create constant buffer.");
        return false;
    }

    bd.ByteWidth = sizeof(LightConstants);
    bd.StructureByteStride = bd.ByteWidth;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0;

    hr = Device->CreateBuffer(&bd, nullptr, &LightsConstantBuffer);
    if (FAILED(hr))
    {
        LogError(L"Failed to create constant buffer.");
        return false;
    }

    D3D11_SAMPLER_DESC sd = {};
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.MaxLOD = 12;

    hr = Device->CreateSamplerState(&sd, &Sampler);
    if (FAILED(hr))
    {
        LogError(L"Failed to create sampler.");
        return false;
    }

    D3D11_RASTERIZER_DESC rd = {};
    rd.FrontCounterClockwise = TRUE;
    rd.AntialiasedLineEnable = TRUE;
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_BACK;
    rd.DepthClipEnable = TRUE;

    hr = Device->CreateRasterizerState(&rd, &RasterizerState);
    if (FAILED(hr))
    {
        LogError(L"Failed to create rasterizer state.");
        return false;
    }

    RECT rc{};
    GetClientRect(Window, &rc);

    D3D11_VIEWPORT vp = {};
    vp.Width = (float)(rc.right - rc.left);
    vp.Height = (float)(rc.bottom - rc.top);
    vp.MaxDepth = 1.f;

    Context->OMSetRenderTargets(1, RenderTarget.GetAddressOf(), DepthBuffer.Get());

    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    Context->IASetInputLayout(InputLayout.Get());
    Context->VSSetShader(VertexShader.Get(), nullptr, 0);
    Context->PSSetShader(PixelShader.Get(), nullptr, 0);
    Context->VSSetConstantBuffers(0, 1, ConstantBuffer.GetAddressOf());
    Context->PSSetSamplers(0, 1, Sampler.GetAddressOf());
    Context->PSSetConstantBuffers(0, 1, LightsConstantBuffer.GetAddressOf());
    Context->RSSetState(RasterizerState.Get());
    Context->RSSetViewports(1, &vp);

    return true;
}