void ShaderManager::CreateInputLayout(ID3DBlob* VS, ID3D11InputLayout* &inputLayout)
{
	HRESULT hr;
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescArray;

	ID3D11ShaderReflection* pReflection;
	hr = D3DReflect(VS->GetBufferPointer(), VS->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pReflection);
	assert(hr == S_OK);

	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	unsigned int i = 0;
	for (; i < shaderDesc.InputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pReflection->GetInputParameterDesc(i, &paramDesc);
		D3D11_INPUT_ELEMENT_DESC inputElementDesc;

		inputElementDesc.SemanticName = paramDesc.SemanticName;
		inputElementDesc.SemanticIndex = paramDesc.SemanticIndex;
		
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inputElementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inputElementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inputElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inputElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		inputElementDesc.InputSlot = 0;
		inputElementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDesc.InstanceDataStepRate = 0;

		inputElementDescArray.push_back(inputElementDesc);
	}

	// Initialize input layout
	hr = D3D11Renderer::GetInstance()->m_pD3D11Device->CreateInputLayout(&inputElementDescArray[0], i, VS->GetBufferPointer(), VS->GetBufferSize(), &inputLayout);
	assert(hr == S_OK);

	pReflection->Release();
}