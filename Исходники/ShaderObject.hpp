		//must called after shader compiled
		HRESULT initializeShaderReflector()
		{
			HRESULT hr = E_FAIL;
			hr = D3DReflect(pShaderContextBuffer->GetBufferPointer(),
				pShaderContextBuffer->GetBufferSize(),
				IID_ID3D11ShaderReflection, 
				reinterpret_cast<void**>(&pShaderReflector));
			if (FAILED(hr))
			{
				return hr;
			}
			return S_OK;
		}