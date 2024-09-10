HRESULT DXSourceWindow::CreateShaderResources()
{
	HRESULT hr = S_OK;
		
	// Set up constant buffer
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;    
	Desc.ByteWidth = sizeof( CUBE_CB );
	hr = m_pd3dDevice->CreateBuffer( &Desc, NULL, &m_Cube_pcb );
	PASS_TEST( hr );

	// create vertex buffer
	const float pVertices[] = { -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
                                 0.5f, -0.5f,  0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
                                -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
                                -0.5f, -0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f,  0.5f,  0.5f,
                                -0.5f,  0.5f,  0.5f,   0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
                                -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f };

	const float pNormal[] = {   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                                1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
                                -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f };

	const float pTexture[] =  { 1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f,
                                1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f,
                                1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f,
                                1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f,
                                1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f,
                                1.0f,0.0f,   1.0f,1.0f,    0.0f,1.0f,    0.0f,0.0f};

    const float pColors[]   = { 1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                                1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                                0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
                                1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f };



	CUBE_Vertex1 verts[24];
	for (int i=0; i<24; i++)
	{
		verts[i].pos = D3DXVECTOR3(pVertices[3*i], pVertices[3*i+1], pVertices[3*i+2]);
		verts[i].texture = D3DXVECTOR2(pTexture[2*i], pTexture[2*i+1] );
		verts[i].normal = D3DXVECTOR3(pNormal[3*i], pNormal[3*i+1], pNormal[3*i+2] );
		verts[i].color = D3DXVECTOR3(pColors[3*i], pColors[3*i+1], pColors[3*i+2]);
	}

	D3D11_BUFFER_DESC vbDesc    = {0};
	vbDesc.BindFlags            = D3D11_BIND_VERTEX_BUFFER; // Type of resource
	vbDesc.ByteWidth            = 24*sizeof(CUBE_Vertex1);       // size in bytes
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vbData = {0};
	vbData.pSysMem = verts;

	hr = m_pd3dDevice->CreateBuffer( &vbDesc, &vbData, &m_Cube_pVertexBuffer);
    PASS_TEST(hr);

	// create index buffer
	int indices[36] = {-1};
	for (int i=0; i<6; i++)
	{
		indices[6*i]=4*i; indices[6*i+1]=4*i+1; indices[6*i+2]=4*i+3;
		indices[6*i+3]=4*i+1; indices[6*i+4]=4*i+2; indices[6*i+5]=4*i+3;
	}
	vbDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    vbDesc.ByteWidth            = 36*sizeof(unsigned int);
	vbData.pSysMem = indices;
	hr = m_pd3dDevice->CreateBuffer( &vbDesc, &vbData, &m_Cube_pIndexBuffer );
	PASS_TEST(hr);


	// Compile the shaders using the lowest possible profile for broadest feature level support
	ID3DBlob* pVertexShaderBuffer = NULL;
	hr = CompileShaderFromFile(L"DrawCube.hlsl", "VSMain", "vs_4_0_level_9_1", &pVertexShaderBuffer );
	if ( hr == D3D11_ERROR_FILE_NOT_FOUND ) 
	{ 
		MessageBoxA(NULL,"ERROR, file DrawCube.hlsl not found.","DirectGMA",NULL);
		return D3D11_ERROR_FILE_NOT_FOUND;
	}
	PASS_TEST(hr);
	hr = m_pd3dDevice->CreateVertexShader( pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), NULL, &m_Cube_pVertexShader );
	PASS_TEST(hr);

	ID3DBlob* pPixelShaderBuffer = NULL;
	hr = CompileShaderFromFile( L"DrawCube.hlsl", "PSMain", "ps_4_0_level_9_1", &pPixelShaderBuffer );
	PASS_TEST(hr);
	hr = m_pd3dDevice->CreatePixelShader( pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), NULL, &m_Cube_pPixelShader );
	PASS_TEST(hr);

	// Create our vertex input layout
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,   0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE",  0,  DXGI_FORMAT_R32G32_FLOAT,      0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",  0,   DXGI_FORMAT_R32G32B32_FLOAT,   0, 20,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",  0,    DXGI_FORMAT_R32G32B32_FLOAT,   0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = m_pd3dDevice->CreateInputLayout( layout, ARRAYSIZE( layout ), pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), &m_Cube_pVertexLayout11 );
	PASS_TEST(hr);
    SAFE_RELEASE( pVertexShaderBuffer );
    SAFE_RELEASE( pPixelShaderBuffer );

	
    // Create a sampler state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = m_pd3dDevice->CreateSamplerState( &sampDesc, &m_Cube_pSamplerLinear );
	PASS_TEST(hr);


	// Set the raster state
	D3D11_RASTERIZER_DESC RasterizerDesc;
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_NONE;
	RasterizerDesc.FrontCounterClockwise = TRUE;
	RasterizerDesc.DepthBias = 0;
	RasterizerDesc.DepthBiasClamp = 0.0f;
	RasterizerDesc.SlopeScaledDepthBias = 0.0f;
	RasterizerDesc.DepthClipEnable = TRUE;
	RasterizerDesc.ScissorEnable = FALSE;
	RasterizerDesc.MultisampleEnable = FALSE;
	RasterizerDesc.AntialiasedLineEnable = FALSE;

	hr = m_pd3dDevice->CreateRasterizerState( &RasterizerDesc, &m_Cube_pRasterizerStateSolid );
	PASS_TEST(hr);

	// Set state Objects
	m_pImmediateContext->RSSetState( m_Cube_pRasterizerStateSolid );


	hr = D3DX11CreateShaderResourceViewFromFile( m_pd3dDevice, L"amdlogo.dds", NULL, NULL, &m_Cube_pTextureRV, NULL );
	if ( hr == D3D11_ERROR_FILE_NOT_FOUND ) 
	{ 
		MessageBoxA(NULL,"ERROR, file amdlogo.dds not found.","DirectGMA",NULL);
		return D3D11_ERROR_FILE_NOT_FOUND;
	}
	PASS_TEST(hr);


	return S_OK;
}