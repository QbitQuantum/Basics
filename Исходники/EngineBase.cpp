bool EngineBase::LoadContent()
{
	//load models
	vector<VertexPos> vertexbuffer;
	vector<int> indexbuffer;
	vector<SubSet> subsets;

	if (!SpriteModel::instance()->load_model("rescs/Smodel.in", vertexbuffer, indexbuffer, subsets))
	{
		MessageBox(0, "error loading models!", 0, 0);
		return false;
	}
	

	//int direct3d device
	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader(L"rescs/TextureMap.fx", "VS_Main", "vs_4_0", &vsBuffer);

	if (compileResult == false)
	{
		MessageBox(0, "Error compiling the vertex shader!", 0, 0);
		return false;
	}

	HRESULT d3dResult;

	d3dResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), 0, &solidColorVS_);

	if (FAILED(d3dResult))
	{
		MessageBox(0, "Error creating the vertex shader!", 0, 0);

		if (vsBuffer)
			vsBuffer->Release();

		return false;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	int totalLayoutElements = ARRAYSIZE(solidColorLayout);

	d3dResult = d3dDevice_->CreateInputLayout(solidColorLayout, totalLayoutElements,
		vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &inputLayout_);

	vsBuffer->Release();

	if (FAILED(d3dResult))
	{
		MessageBox(0, "Error creating the input layout!", 0, 0);
		return false;
	}

	ID3DBlob* psBuffer = 0;

	compileResult = CompileD3DShader(L"rescs/TextureMap.fx", "PS_Main", "ps_4_0", &psBuffer);

	if (compileResult == false)
	{
		MessageBox(0, "Error compiling pixel shader!", 0, 0);
		return false;
	}

	d3dResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(),
		psBuffer->GetBufferSize(), 0, &solidColorPS_);

	psBuffer->Release();

	if (FAILED(d3dResult))
	{
		MessageBox(0, "Error creating pixel shader!", 0, 0);
		return false;
	}


	d3dResult = CreateDDSTextureFromFile(d3dDevice_, L"rescs/resc.dds", nullptr, &colorMap_);

	if (FAILED(d3dResult))
	{
		MessageBox(0, "Failed to load the texture image!", 0, 0);
		return false;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = d3dDevice_->CreateSamplerState(&colorMapDesc, &colorMapSampler_);

	if (FAILED(d3dResult))
	{
		MessageBox(0, "Failed to create color map sampler state!", 0, 0);
		return false;
	}


	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * (int)vertexbuffer.size();

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = &vertexbuffer[0];
	d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &vertexBuffer_);
	if (FAILED(d3dResult))
	{
		MessageBox(0, "Failed to create vertex buffer!", 0, 0);
		return false;
	}

	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(int) * (int)indexbuffer.size();
	vertexDesc.CPUAccessFlags = 0;
	resourceData.pSysMem = &indexbuffer[0];
	d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &indexBuffer_);
	if (FAILED(d3dResult))
	{
		MessageBox(0, "Failed to create index buffer!", 0, 0);
		return false;
	}


	//create constant buffer
	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc, sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(XMMATRIX);
	constDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &mvpCB_);
	if (FAILED(d3dResult))
	{
		return false;
	}

	constDesc.ByteWidth = sizeof(tex_co_trans);
	d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &texTrans_);

	sets = subsets;


	XMMATRIX view = XMMatrixIdentity();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	vpMatrix_ = XMMatrixMultiply(view, projection);


	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	d3dDevice_->CreateBlendState(&blendDesc, &alphaBlendState_);
	d3dContext_->OMSetBlendState(alphaBlendState_, blendFactor, 0xFFFFFFFF);

	//set states
	UINT stride = sizeof(VertexPos);
	UINT offset = 0;

	d3dContext_->IASetInputLayout(inputLayout_);
	d3dContext_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext_->VSSetShader(solidColorVS_, 0, 0);
	d3dContext_->PSSetShader(solidColorPS_, 0, 0);
	d3dContext_->PSSetShaderResources(0, 1, &colorMap_);
	d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

	return true;
}