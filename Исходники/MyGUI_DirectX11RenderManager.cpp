	void DirectX11RenderManager::initialise(ID3D11Device* _device)
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		mpD3DDevice = _device;
		_device->GetImmediateContext(&mpD3DContext);

		mVertexFormat = VertexColourType::ColourABGR;

		std::string vertexProfile, pixelProfile;
		if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_0 )
		{
			vertexProfile = "vs_5_0";
			pixelProfile = "ps_5_0";
		}
		else if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_10_1 )
		{
			vertexProfile = "vs_4_1";
			pixelProfile = "ps_4_1";
		}
		else if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_10_0 )
		{
			vertexProfile = "vs_4_0";
			pixelProfile = "ps_4_0";
		}
		else if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_3 )
		{
			vertexProfile = "vs_4_0_level_9_3";
			pixelProfile = "ps_4_0_level_9_3";
		}
		else if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_2 )
		{
			vertexProfile = "vs_4_0_level_9_1";
			pixelProfile = "ps_4_0_level_9_1";
		}
		else if ( mpD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_1 )
		{
			vertexProfile = "vs_4_0_level_9_1";
			pixelProfile = "ps_4_0_level_9_1";
		}

		// Get Current viewports
		memset(&mInfo, 0, sizeof(mInfo));
		UINT numViewports = 0;
		D3D11_VIEWPORT viewports[8];

		mpD3DContext->RSGetViewports(&numViewports, viewports);
		MYGUI_PLATFORM_ASSERT(numViewports == 0, getClassTypeName() << " 0 viewport sets");

		setViewSize((int)viewports[0].Width, (int)viewports[0].Height);

		UINT flags = (1 << 11) | (1 << 15);

		// Build Flat Vertex Shader
		ID3DBlob* bytecode = 0, *errors = 0, *signature0 = 0, *signature1 = 0;
		HRESULT hr = D3DCompile(vsSource, strlen(vsSource), "VertexShader0", 0, 0, "main", vertexProfile.c_str(), flags, 0, &bytecode, &errors);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, unknown errors!"));

		hr = D3DGetInputSignatureBlob(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), &signature0);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, failed to get input signature!"));

		hr = mpD3DDevice->CreateVertexShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), 0, &mVertexShader0);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Create failed!"));

		if ( bytecode ) bytecode->Release();
		if ( errors ) errors->Release();


		// Build Textured Vertex Shader
		bytecode = 0;
		errors = 0;
		hr = D3DCompile(vsTexturedSource, strlen(vsTexturedSource), "VertexShader1", 0, 0, "main", vertexProfile.c_str(), flags, 0, &bytecode, &errors);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, unknown errors!"));

		hr = D3DGetInputSignatureBlob(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), &signature1);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, failed to get input signature!"));

		hr = mpD3DDevice->CreateVertexShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), 0, &mVertexShader1);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Create failed!"));

		if ( bytecode ) bytecode->Release();
		if ( errors ) errors->Release();

		// Build Flat Pixel Shader
		bytecode = 0;
		errors = 0;
		hr = D3DCompile(psSource, strlen(psSource), "PixelShader0", 0, 0, "main", pixelProfile.c_str(), flags, 0, &bytecode, &errors);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, unknown errors!"));

		hr = mpD3DDevice->CreatePixelShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), 0, &mPixelShader0);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Create failed!"));

		if ( bytecode ) bytecode->Release();
		if ( errors ) errors->Release();


		// Build Textured Pixel Shader
		bytecode = 0;
		errors = 0;
		hr = D3DCompile(psTexturedSource, strlen(psTexturedSource), "PixelShader1", 0, 0, "main", pixelProfile.c_str(), flags, 0, &bytecode, &errors);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Compilation failed, unknown errors!"));

		hr = mpD3DDevice->CreatePixelShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), 0, &mPixelShader1);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, (errors ? (char*)errors->GetBufferPointer() : "Vertex Shader Create failed!"));

		if ( bytecode ) bytecode->Release();
		if ( errors ) errors->Release();

		// Create Sampler State
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.BorderColor[0] = samplerDesc.BorderColor[1] = samplerDesc.BorderColor[2] = samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)0;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.MaxLOD = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MipLODBias = 0.0f;
		hr = mpD3DDevice->CreateSamplerState(&samplerDesc, &mSamplerState);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Sampler State Create failed!");

		// Create Blend State
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		hr = mpD3DDevice->CreateBlendState(&blendDesc, &mBlendState);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Blend State Create failed!");

		// Create Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthDesc;
		depthDesc.DepthEnable = false;
		depthDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthDesc.StencilEnable = false;
		depthDesc.StencilReadMask = depthDesc.StencilWriteMask = 0;
		depthDesc.BackFace.StencilDepthFailOp = depthDesc.BackFace.StencilFailOp = depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthDesc.FrontFace = depthDesc.BackFace;
		hr = mpD3DDevice->CreateDepthStencilState(&depthDesc, &mDepthStencilState);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Depth Stencil State Create failed!");

		// Create Rasterizer State
		D3D11_RASTERIZER_DESC rastDesc;
		rastDesc.FillMode              = D3D11_FILL_SOLID;
		rastDesc.CullMode              = D3D11_CULL_NONE;
		rastDesc.FrontCounterClockwise = FALSE;
		rastDesc.DepthBias             = 0;
		rastDesc.DepthBiasClamp        = 0;
		rastDesc.SlopeScaledDepthBias  = 0;
		rastDesc.ScissorEnable         = FALSE;
		rastDesc.MultisampleEnable     = FALSE;
		rastDesc.AntialiasedLineEnable = FALSE;
		hr = mpD3DDevice->CreateRasterizerState(&rastDesc, &mRasterizerState);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Rasterizer State Create failed!");

		// Create Input Layout
		hr = mpD3DDevice->CreateInputLayout(vertexLayout, 3, signature0->GetBufferPointer(), signature0->GetBufferSize(), &mInputLayout0);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Input Layout Create failed!");

		signature0->Release();

		// Create Input Layout
		hr = mpD3DDevice->CreateInputLayout(vertexLayout, 3, signature1->GetBufferPointer(), signature1->GetBufferSize(), &mInputLayout1);
		MYGUI_PLATFORM_ASSERT(hr == S_OK, "Input Layout Create failed!");

		signature1->Release();

		mUpdate = false;

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}