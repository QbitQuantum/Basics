	DFORCEINLINE static void getContants(ID3D10Device *d3dDevice,
		const String& prefix,
		DUNORDERED_MAP <String, size_t>& mapVars,
		ID3D10Blob* pCode,
		ID3D10Buffer** pBuffer,
		size_t& size){
		HRESULT hr;
		ID3D10ShaderReflection* pReflection = NULL;
		hr = D3D10ReflectShader((void*)pCode->GetBufferPointer(),
			pCode->GetBufferSize(),
			&pReflection);

		if (FAILED(hr))
		{
			DEBUG_ASSERT_MSG(0, "Shader reflection could not be obtained. Reason: " << DXGetErrorDescription(hr));
			return;
		}

		D3D10_SHADER_DESC desc;
		DX_ASSERT_MSG(pReflection->GetDesc(&desc));
		//init
		ID3D10ShaderReflectionConstantBuffer* pConstantBuffer = NULL;
		size_t valueOffset = 0;
		size = 0;
		//calc size
		for (uint i = 0; i < desc.ConstantBuffers; ++i)
		{
			pConstantBuffer = pReflection->GetConstantBufferByIndex(i);

			uint count = 0;
			D3D10_SHADER_BUFFER_DESC bufferDesc;
			DX_ASSERT_MSG(pConstantBuffer->GetDesc(&bufferDesc));
			if (bufferDesc.Type == D3D10_CT_TBUFFER)
				continue;

			count = bufferDesc.Variables;

			ID3D10ShaderReflectionVariable* pConstant = NULL;
			D3D10_SHADER_VARIABLE_DESC constantDesc;
			for (uint j = 0; j < count; ++j)
			{
				pConstant = pConstantBuffer->GetVariableByIndex(j);
				pConstant->GetDesc(&constantDesc);
				mapVars[prefix + '.' + constantDesc.Name] = valueOffset;
				valueOffset += constantDesc.Size;
			}
		}
		//save size buffer
		size = Math::multipleOfX(valueOffset, 16);
		//
		if (valueOffset)
		{
			(*pBuffer) = genBufferObject(d3dDevice, size);
		}

	}