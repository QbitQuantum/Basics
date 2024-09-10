AGN::ShaderDX11::ShaderDX11(DeviceDX11& a_deviceReference, const uint16_t a_aId, EShaderType a_type, ID3D11DeviceChild* a_shaderHandle, ID3DBlob* a_shaderBlob)
	: m_deviceReference(a_deviceReference)
	, m_aId(a_aId)
	, m_type(a_type)
	, m_shaderHandle(a_shaderHandle)
	, m_shaderBlob(a_shaderBlob)
	, m_shaderReflection(nullptr)
	, m_shaderReflectionDesc(nullptr)
{
	HRESULT hr = D3DReflect(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&m_shaderReflection);

	if (FAILED(hr)) g_log.error("Failed performing reflection on shader");

	m_shaderReflectionDesc = new D3D11_SHADER_DESC();		// TODO: refactor, we dont want pointers just to be able to fwd declare :/
	memset(m_shaderReflectionDesc, 0, sizeof(D3D11_SHADER_DESC));

	hr = m_shaderReflection->GetDesc(m_shaderReflectionDesc);

	if (FAILED(hr)) g_log.error("Failed getting reflection desc on shader");


	int numConstantBuffers;
	D3D11_SHADER_BUFFER_DESC* constantBufferDescriptions;

	// reflect on constant buffers
	getConstantBufferDesc(constantBufferDescriptions, numConstantBuffers);

	if (numConstantBuffers > 0)
	{
		m_constantBuffers.reserve(numConstantBuffers);

		m_bufferHandles.reserve(numConstantBuffers);

		// create constant buffers
		for (uint16_t i = 0; i < numConstantBuffers; i++)
		{
			ConstantBufferDX11* constantBuffer = new ConstantBufferDX11();

			D3D11_SHADER_BUFFER_DESC bufferDescription;
			memcpy(&bufferDescription, &constantBufferDescriptions[i], sizeof(D3D11_SHADER_BUFFER_DESC)); // TODO: refactor :/

			// Get name
			memcpy(constantBuffer->name, bufferDescription.Name, sizeof(char) * strlen(bufferDescription.Name));
			
			// Get Size
			constantBuffer->size = bufferDescription.Size;

			// Create CPU-side buffer
			constantBuffer->buffer = new uint8_t[constantBuffer->size];
			memset(constantBuffer->buffer, 0, constantBuffer->size);

			// Get bind point
			for (uint16_t k = 0; k < m_shaderReflectionDesc->BoundResources; ++k)
			{
				D3D11_SHADER_INPUT_BIND_DESC ibdesc;
				memset(&ibdesc, 0, sizeof(D3D11_SHADER_INPUT_BIND_DESC));
				hr = m_shaderReflection->GetResourceBindingDesc(k, &ibdesc);
				if (FAILED(hr)) g_log.error("Failed getting reflection D3D11_SHADER_INPUT_BIND_DESC on shader");

				if (strcmp(ibdesc.Name, constantBufferDescriptions[i].Name) == 0)
				{
					constantBuffer->bindpoint = ibdesc.BindPoint;
					break;
				}
			}

			if (constantBuffer->bindpoint == -1)
			{
				g_log.error("Did not find bindpoint for Constant buffer with the name %s", constantBufferDescriptions[i].Name);
				assert(false);
			}

			// get reflection for buffer variables
			ID3D11ShaderReflectionConstantBuffer* bufferReflection = m_shaderReflection->GetConstantBufferByName(bufferDescription.Name);
			
			constantBuffer->propertyList.reserve(bufferDescription.Variables);

			// get all variables in buffer
			for (unsigned j = 0; j < bufferDescription.Variables; ++j)
			{
				ConstantBufferPropertyDX11* constantBufferProperty = new ConstantBufferPropertyDX11();
				memset(constantBufferProperty, 0, sizeof(ConstantBufferPropertyDX11));

				// get variable description 
				D3D11_SHADER_VARIABLE_DESC variableDesc;
				memset(&variableDesc, 0, sizeof(D3D11_SHADER_VARIABLE_DESC));
				bufferReflection->GetVariableByIndex(j)->GetDesc(&variableDesc);
								
				memcpy(constantBufferProperty->name, variableDesc.Name, sizeof(char) * strlen(variableDesc.Name));
				constantBufferProperty->offset = variableDesc.StartOffset;
				constantBufferProperty->size = variableDesc.Size;
		
				constantBuffer->propertyList.push_back(constantBufferProperty);
			}

			// create handle to actual buffer
			D3D11_BUFFER_DESC newConstantBufferDesc;
			memset(&newConstantBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

			newConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			newConstantBufferDesc.ByteWidth = constantBufferDescriptions[i].Size;
			newConstantBufferDesc.CPUAccessFlags = 0;
			newConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			newConstantBufferDesc.MiscFlags = 0;
			newConstantBufferDesc.StructureByteStride = 0;

			// TODO: think if this is the correct location for this function, in essence, we are doing the devices job in this constructor?
			HRESULT hr = a_deviceReference.getD3D11Device()->CreateBuffer(&newConstantBufferDesc, nullptr, &constantBuffer->d3dhandle);

			m_bufferHandles.push_back(constantBuffer->d3dhandle);

			if (FAILED(hr))
			{
				g_log.error("failure creating constant buffer");
				return;
			}

			m_constantBuffers.push_back(constantBuffer);
		}
	}

	delete[] constantBufferDescriptions;

#ifdef AGN_DEBUG
	//AGN::logHResultData(hr);
#endif // AGN_DEBUG
	
}