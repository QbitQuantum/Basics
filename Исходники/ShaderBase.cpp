	HRESULT ShaderBase::processLoadedShaderBlob( ID3DBlob *shaderSource )
	{
		HRESULT res = build( shaderSource );
		if ( FAILED(res) )
		{
			std::cout << "Error (ShaderBase::processLoadedShaderBlob): Error creating shader" << std::endl;
			return res;
		}


		// setup buffers using the shader reflection
		ID3D11ShaderReflection *reflector;
		res = D3DReflect( shaderSource->GetBufferPointer(), shaderSource->GetBufferSize(),
							IID_ID3D11ShaderReflection, (void**)&reflector );
		if ( FAILED( res ) )
		{
			std::cout << "Error (ShaderBase::processLoadedShaderBlob): Error creating shader reflection" << std::endl;
			return res;
		}


		D3D11_SHADER_DESC shaderDesc;
		ZeroMemory( &shaderDesc, sizeof( D3D11_SHADER_DESC ) );
		res = reflector->GetDesc( &shaderDesc );
		if ( FAILED( res ) )
		{
			std::cout << "Error (ShaderBase::processLoadedShaderBlob): Error creating shader reflection description" << std::endl;
			reflector->Release();
			return res;
		}


		for ( UINT i = 0U; i < shaderDesc.ConstantBuffers; ++i )
		{
			ID3D11ShaderReflectionConstantBuffer *constBuffReflection = reflector->GetConstantBufferByIndex( i );
			D3D11_SHADER_BUFFER_DESC shaderBuffDesc;
			constBuffReflection->GetDesc( &shaderBuffDesc );

			//TODO: these can be put on the stack
			ConstantBuffer *cBuff = new ConstantBuffer( m_dxDev, i, shaderBuffDesc.Name );
			cBuff->create( shaderBuffDesc.Size );
			for ( UINT j = 0U; j < shaderBuffDesc.Variables; ++j )
			{
				ID3D11ShaderReflectionVariable *variableRefl = constBuffReflection->GetVariableByIndex( j );
				D3D11_SHADER_VARIABLE_DESC shaderVarDesc;
				variableRefl->GetDesc( &shaderVarDesc );

				cBuff->addVariableDefinition( shaderVarDesc.Name, shaderVarDesc.StartOffset, shaderVarDesc.Size );
			}

			m_constBuffers.push_back( cBuff );
			m_dxConstBuffers.push_back( cBuff->getDxBufferPtr() );
		}

		reflector->Release();

		return S_OK;
	}