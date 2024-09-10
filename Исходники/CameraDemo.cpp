bool CameraDemo::LoadContent()
{
	ID3DBlob * vsBuffer = 0;
	
	bool compileResult = CompileD3DShader( "TextureMap.fx" , "VS_Main" , "vs_4_0" , &vsBuffer );

	if( compileResult == false )
	{
		DXTRACE_MSG( "¼ÓÔØ¶¥µã×ÅÉ«Æ÷Ê§°Ü£¡" );
		return false;
	}

	HRESULT d3dResult;

	d3dResult = d3dDevice_ ->CreateVertexShader( vsBuffer ->GetBufferPointer() , vsBuffer ->GetBufferSize() , 0 , &solidColorVS_ );

	if( FAILED( d3dResult ))
	{
		if( vsBuffer )
			vsBuffer ->Release();

		return false ;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[ ] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };


	unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

	d3dResult =d3dDevice_ ->CreateInputLayout( solidColorLayout , totalLayoutElements , vsBuffer ->GetBufferPointer() , vsBuffer ->GetBufferSize() , &inputLayout_ );
	vsBuffer ->Release();

	if( FAILED( d3dResult ))
	{
		return false;
	}

	ID3DBlob * psBuffer = 0;

	compileResult = CompileD3DShader( "TextureMap.fx" , "PS_Main" , "ps_4_0" , &psBuffer );

	if( compileResult == false )
	{
		DXTRACE_MSG( "¼ÓÔØÏñËØ×ÅÉ«Æ÷Ê§°Ü£¡" );
		return false;
	}

	d3dResult = d3dDevice_ ->CreatePixelShader( psBuffer ->GetBufferPointer() , psBuffer ->GetBufferSize() , 0 , &solidColorPS_ );
	psBuffer ->Release();

	if( FAILED( d3dResult ))
	{
		return false;
	}

	VertexPos vertices[ ] = 
	{
		{ XMFLOAT3( -1.0f , 1.0f , -1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , -1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , 1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( -1.0f , 1.0f , 1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } ,

		{ XMFLOAT3( -1.0f , -1.0f , -1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , -1.0f , -1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , -1.0f , 1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( -1.0f , -1.0f , 1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } ,
		
		{ XMFLOAT3( -1.0f , -1.0f , 1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( -1.0f , -1.0f , -1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( -1.0f , 1.0f , -1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( -1.0f , 1.0f , 1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } ,

		{ XMFLOAT3( 1.0f , -1.0f , 1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , -1.0f , -1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , -1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , 1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } ,

		{ XMFLOAT3( -1.0f , -1.0f , -1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , -1.0f , -1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , -1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( -1.0f , 1.0f , -1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } ,

		{ XMFLOAT3( -1.0f , -1.0f , 1.0f ) , XMFLOAT2( 0.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , -1.0f , 1.0f ) , XMFLOAT2( 1.0f , 0.0f ) } ,
		{ XMFLOAT3( 1.0f , 1.0f , 1.0f ) , XMFLOAT2( 1.0f , 1.0f ) } ,
		{ XMFLOAT3( -1.0f , 1.0f , 1.0f ) , XMFLOAT2( 0.0f , 1.0f ) } 
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory( &vertexDesc , sizeof( vertexDesc ));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof( VertexPos ) * 24;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData , sizeof( resourceData ));
	resourceData.pSysMem = vertices;

	d3dResult = d3dDevice_ ->CreateBuffer( &vertexDesc , &resourceData , &vertexBuffer_ );

	if( FAILED( d3dResult ))
	{
		DXTRACE_MSG( "´´½¨¶¥µã»º³åÇøÊ§°Ü£¡" );
		return false;
	}

	WORD indices[ ] =
	{
		3 , 1 , 0 , 2 , 1 , 3 ,
		6 , 4 , 5 , 7 , 4 , 6 ,
		11 , 9 , 8 , 10 , 9 , 11 ,
		14 , 12 , 13 , 15 , 12 , 14 ,
		19 , 17 , 16 , 18 , 17 , 19 ,
		22 , 20 , 21 ,23 , 20 , 22 
	};

	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory( &indexDesc , sizeof( indexDesc ));
	indexDesc.Usage = D3D11_USAGE_DEFAULT ; 
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = sizeof( WORD ) * 36 ;
	indexDesc.CPUAccessFlags = 0;
	resourceData.pSysMem = indices;

	d3dResult =d3dDevice_ ->CreateBuffer( &indexDesc , &resourceData , &indexBuffer_ );

	if( FAILED( d3dResult ))
	{
		DXTRACE_MSG( "´´½¨Ë÷Òý»º³åÇøÊ§°Ü£¡" );
		return false;
	}

	d3dResult = D3DX11CreateShaderResourceViewFromFile( d3dDevice_ , "decal.dds" , 0 , 0 , &colorMap_ , 0 );

	if( FAILED( d3dResult ))
	{
		DXTRACE_MSG( "¼ÓÔØÎÆÀíÍ¼ÏñÊ§°Ü£¡" );
		return false;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc , sizeof( colorMapDesc ));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = d3dDevice_ ->CreateSamplerState( &colorMapDesc ,&colorMapSampler_ );

	if( FAILED( d3dResult ))
	{
		DXTRACE_MSG( "´´½¨²ÉÑùÆ÷Ê§°Ü£¡" );
		return false;
	}

	D3D11_BUFFER_DESC constDesc;
	ZeroMemory( &constDesc , sizeof( constDesc ));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof( XMMATRIX );
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	d3dResult = d3dDevice_ ->CreateBuffer( &constDesc , 0 , &viewCB_ );

	if( FAILED( d3dResult ))
	{
		return false;
	}

	d3dResult = d3dDevice_ ->CreateBuffer( &constDesc , 0 , &projCB_ );

	if( FAILED( d3dResult ))
	{
		return false;
	}

	d3dResult = d3dDevice_ ->CreateBuffer( &constDesc , 0 , &worldCB_ );

	if( FAILED( d3dResult ))
	{
		return false;
	}

	XMMATRIX projection_ = XMMatrixPerspectiveLH( XM_PIDIV4 , 800.0f / 600.0f , 0.01f , 100.0f );

	projection_ = XMMatrixTranspose( projection_ );
	

	camera_.SetPositions( XMFLOAT3( 3.0f , 3.0f , -12.0f ) , XMFLOAT3( 0.0f , 0.0f , 0.0f ));

	return true;
}