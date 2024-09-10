void GltfPbr::CreatePipeline(ID3D12Device* pDevice, UINT node, std::vector<std::string> semanticNames, std::vector<D3D12_INPUT_ELEMENT_DESC> layout, PBRPrimitives *pPrimitive)
{
    //=================================================================================================
    // let vertex shader know what buffers are present
    // The Shader Code glTF20_EX.hlsl has if defs that are enable using these attributes when compiled
    // and ref by the D3D12_GRAPHICS_PIPELINE_STATE_DESC 
    //=================================================================================================
    bool Has_Normals = false;

    std::map<std::string, std::string> attributeDefines;
    for (unsigned int i = 0; i < layout.size(); i++)
    {
        layout[i].SemanticName = semanticNames[i].c_str();
        attributeDefines[std::string("HAS_") + layout[i].SemanticName] = "1";

        if (semanticNames[i].compare("NORMAL") == 0) Has_Normals = true;

    }

    // Compile shaders
    //
    ID3DBlob *pBlobShaderVert, *pBlobShaderPixel;
    {
        // build macro structure
        //
        std::vector<D3D_SHADER_MACRO> macros;
        CompileMacros(&attributeDefines, &macros);
        CompileMacros(&pPrimitive->m_pMaterial->m_defines, &macros);
        macros.push_back(D3D_SHADER_MACRO{ NULL, NULL });

        ID3DBlob *pError;
        D3DCompileFromFile(L"./plugins/shaders/glTF20_EX.hlsl", macros.data(), nullptr, "mainVS", "vs_5_0", 0, 0, &pBlobShaderVert, &pError);
        D3DCompileFromFile(L"./plugins/shaders/glTF20_EX.hlsl", macros.data(), nullptr, "mainPS", "ps_5_0", 0, 0, &pBlobShaderPixel, &pError);
        if (pError != NULL)
        {
            char *msg = (char *)pError->GetBufferPointer();
            MessageBoxA(0, msg, "", 0);
        }
    }

    // Create root signature
    //
    {
        CD3DX12_DESCRIPTOR_RANGE DescRange[4];
        DescRange[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);		// b0 <- per frame
        DescRange[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, pPrimitive->m_pMaterial->m_textureCount, 0);		// t0 <- per material
        DescRange[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);		// b1 <- per material parameters
        DescRange[3].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 5, 0);	// s0 <- samplers

        CD3DX12_ROOT_PARAMETER RTSlot[4];
        RTSlot[0].InitAsDescriptorTable(1, &DescRange[0], D3D12_SHADER_VISIBILITY_ALL);
        RTSlot[1].InitAsDescriptorTable(1, &DescRange[1], D3D12_SHADER_VISIBILITY_PIXEL);
        RTSlot[2].InitAsDescriptorTable(1, &DescRange[2], D3D12_SHADER_VISIBILITY_ALL);
        RTSlot[3].InitAsDescriptorTable(1, &DescRange[3], D3D12_SHADER_VISIBILITY_PIXEL);

        // the root signature contains 3 slots to be used
        CD3DX12_ROOT_SIGNATURE_DESC descRootSignature = CD3DX12_ROOT_SIGNATURE_DESC();
        descRootSignature.NumParameters = 4;
        descRootSignature.pParameters = RTSlot;
        descRootSignature.NumStaticSamplers = 0;
        descRootSignature.pStaticSamplers = NULL;

        // deny uneccessary access to certain pipeline stages   
        descRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE
            | D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
            //| D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS
            | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS
            | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
            | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
            //| D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

        ID3DBlob *pOutBlob, *pErrorBlob = NULL;
        ThrowIfFailed(D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &pOutBlob, &pErrorBlob));
        ThrowIfFailed(
            pDevice->CreateRootSignature(
                node,
                pOutBlob->GetBufferPointer(),
                pOutBlob->GetBufferSize(),
                IID_PPV_ARGS(&pPrimitive->m_RootSignature))
        );
        pPrimitive->m_RootSignature->SetName(L"OnCreatePrimitiveColorPass");

        pOutBlob->Release();
        if (pErrorBlob)
            pErrorBlob->Release();
    }

    D3D12_RENDER_TARGET_BLEND_DESC blendingOpaque = D3D12_RENDER_TARGET_BLEND_DESC
    {
        FALSE,FALSE,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };

    D3D12_RENDER_TARGET_BLEND_DESC blendingBlend = D3D12_RENDER_TARGET_BLEND_DESC
    {
        TRUE,FALSE,
        D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };

    // Create a PSO description
    //
    if (!pBlobShaderVert || !pBlobShaderPixel)
    {
        throw 1;
    }

    D3D12_GRAPHICS_PIPELINE_STATE_DESC descPso = {};
    
    descPso.InputLayout = { layout.data(), (UINT)layout.size() };
    descPso.pRootSignature = pPrimitive->m_RootSignature.Get();
    descPso.VS = { reinterpret_cast<BYTE*>(pBlobShaderVert->GetBufferPointer()), pBlobShaderVert->GetBufferSize() };
    descPso.PS = { reinterpret_cast<BYTE*>(pBlobShaderPixel->GetBufferPointer()), pBlobShaderPixel->GetBufferSize() };
    descPso.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    descPso.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;

    // Decide on default view based on attributes available
    if (m_pGLTFData)
    {
        if(m_pGLTFData->isBinFile)
            descPso.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
        else {
            if (Has_Normals)
            {
                descPso.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
            }
            else
                descPso.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
        }
    }
    else 
    {
        if (Has_Normals)
        {
            descPso.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
        }
        else
            descPso.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
    }

    descPso.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    descPso.BlendState.IndependentBlendEnable = TRUE;
    descPso.BlendState.RenderTarget[0] = blendingBlend;
    descPso.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    descPso.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    descPso.SampleMask = UINT_MAX;
    descPso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    descPso.NumRenderTargets = 1;
    descPso.RTVFormats[0] = DXGI_FORMAT_R16G16B16A16_UNORM;
    descPso.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    descPso.SampleDesc.Count = 4;
    descPso.NodeMask = node;
    descPso.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
    ThrowIfFailed(
        pDevice->CreateGraphicsPipelineState(&descPso, IID_PPV_ARGS(&pPrimitive->m_PipelineRender))
    );

    // create samplers if not initialized (this should happen once)
    if (m_sampler.GetSize()==0)
    {
        m_pResourceViewHeaps->AllocSamplerDescriptor(5, &m_sampler);

        //for pbr materials
        D3D12_SAMPLER_DESC SamplerDesc;
        ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
        SamplerDesc.Filter = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        SamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.BorderColor[0] = 0.0f;
        SamplerDesc.BorderColor[1] = 0.0f;
        SamplerDesc.BorderColor[2] = 0.0f;
        SamplerDesc.BorderColor[3] = 0.0f;
        SamplerDesc.MinLOD = 0.0f;
        SamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        SamplerDesc.MipLODBias = 0;
        SamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        SamplerDesc.MaxAnisotropy = 1;
        pDevice->CreateSampler(&SamplerDesc, m_sampler.GetCPU(0));


        // diffuse env map sampler
        ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
        SamplerDesc.Filter = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        SamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.BorderColor[0] = 0.0f;
        SamplerDesc.BorderColor[1] = 0.0f;
        SamplerDesc.BorderColor[2] = 0.0f;
        SamplerDesc.BorderColor[3] = 0.0f;
        SamplerDesc.MinLOD = 0.0f;
        SamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        SamplerDesc.MipLODBias = 0;
        SamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        SamplerDesc.MaxAnisotropy = 1;
        pDevice->CreateSampler(&SamplerDesc, m_sampler.GetCPU(1));

        // specular env map sampler
        ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
        SamplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        SamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.BorderColor[0] = 0.0f;
        SamplerDesc.BorderColor[1] = 0.0f;
        SamplerDesc.BorderColor[2] = 0.0f;
        SamplerDesc.BorderColor[3] = 0.0f;
        SamplerDesc.MinLOD = 0.0f;
        SamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        SamplerDesc.MipLODBias = 0;
        SamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        SamplerDesc.MaxAnisotropy = 1;
        pDevice->CreateSampler(&SamplerDesc, m_sampler.GetCPU(2));

        // specular BRDF lut sampler
        ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
        SamplerDesc.Filter = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        SamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        SamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        SamplerDesc.BorderColor[0] = 0.0f;
        SamplerDesc.BorderColor[1] = 0.0f;
        SamplerDesc.BorderColor[2] = 0.0f;
        SamplerDesc.BorderColor[3] = 0.0f;
        SamplerDesc.MinLOD = 0.0f;
        SamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        SamplerDesc.MipLODBias = 0;
        SamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        SamplerDesc.MaxAnisotropy = 1;
        pDevice->CreateSampler(&SamplerDesc, m_sampler.GetCPU(3));

        // specular BRDF lut sampler
        D3D12_SAMPLER_DESC samplerShadow = {
            D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
            D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
            D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
            D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
            0.0f,
            1u,
            D3D12_COMPARISON_FUNC_LESS_EQUAL,
            { 0.0f, 0.0f, 0.0f, 0.0f },
            0.0f,
            D3D12_FLOAT32_MAX
        };

        pDevice->CreateSampler(&samplerShadow, m_sampler.GetCPU(4));
    }

    pPrimitive->m_sampler = &m_sampler;
}