void CShaderCreator::FinalizeRes( TResource * pRes )
{
	// Компилируем шейдер --------------------------------------------------

	ID3D10Blob *	pByteCode = NULL;
	CShader *		pShader = (CShader *)pRes->pResource;
	uint			nConstBufferSize;

	const char * szEntry = NULL;
	const char * szProfile = NULL;
	bool bIsVertexShader = true;

	if ( CStr::FinishWith( pRes->sFileName.GetString(), ".vsh" ) )
	{
		szEntry = "Ripple";
		szProfile = "vs_4_0";
	}
	else if ( CStr::FinishWith( pRes->sFileName.GetString(), ".psh" ) )
	{
		szEntry = "main";
		szProfile = "ps_4_0";
		bIsVertexShader = false;
	}

	EResult rStatus = CompileShader(
		pRes->sFileName.GetString(),
		(const char *)pRes->pBuffer,
		szEntry,
		szProfile,
		&pByteCode );

	// После компиляции исходный код уже не нужен
	DEL_ARRAY( pRes->pBuffer );

	if ( R_OK != rStatus )
	{
		// Компиляция провалилась
		pRes->eState = TResource::FAILED;
		return;
	}

	ID3D10ShaderReflection * pRef = NULL;
	HRESULT hRes;

	if ( bIsVertexShader )
	{
		pShader->m_pByteCodeVS = pByteCode;
		// Обрабатываем переменные ---------------------------------------------

		hRes = D3D10ReflectShader(
			pByteCode->GetBufferPointer(),
			pByteCode->GetBufferSize(),
			&pRef );

		if ( ( S_OK == hRes ) && ( NULL != pRef ) )
		{
			D3D10_SHADER_DESC desc;
			pRef->GetDesc( &desc );

			DEBUG_ASSERT( 1 == desc.ConstantBuffers )

				// Перебираем каждый буффер констант
				for ( uint i = 0; i < desc.ConstantBuffers; ++i )
				{
					ID3D10ShaderReflectionConstantBuffer * pCBuf =
						pRef->GetConstantBufferByIndex( i );

					D3D10_SHADER_BUFFER_DESC bufDesc;
					pCBuf->GetDesc( &bufDesc );

					const char * szCBName	= bufDesc.Name;
					nConstBufferSize		= bufDesc.Size;

					pShader->m_nUniformCount = bufDesc.Variables;
					pShader->m_pUniforms = NEW CShader::TUniform [ pShader->m_nUniformCount ];

					// Перебираем каждую переменную в буффере
					for ( uint nVar = 0; nVar < bufDesc.Variables; ++nVar )
					{
						ID3D10ShaderReflectionVariable * pVar =
							pCBuf->GetVariableByIndex( nVar );

						D3D10_SHADER_VARIABLE_DESC varDesc;
						pVar->GetDesc( &varDesc );

						CShader::TUniform & tUniform = pShader->m_pUniforms[ nVar ];

						tUniform.sName	= varDesc.Name;
						tUniform.nCount = varDesc.Size / sizeof( vec4 );
						tUniform.nLoc	= varDesc.StartOffset / sizeof( vec4 );
					}
				}
		}

		hRes = g_pDevice->CreateVertexShader(
			pByteCode->GetBufferPointer(),
			pByteCode->GetBufferSize(),
			&pShader->m_pVS );
	}