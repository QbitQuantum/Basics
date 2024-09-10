	std::shared_ptr<Shader> Shader::CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath)
	{
		std::shared_ptr<Shader> shader;
		CComPtr<ID3DBlob> errorBlob;
		CComPtr<ID3DBlob> shaderBlob;

		if (SUCCEEDED(D3DCompileFromFile(convert(filePath).c_str(),
			nullptr, nullptr, D3D11::ToShaderEntryPoint(type), D3D11::ToShaderLevel(type), 0, 0, &shaderBlob, &errorBlob)))
		{
			std::string debugName = filePath;
			shader = Shader::CreateFromBlob(device, type, shaderBlob, "Shader: " + debugName);
		}
		else
		{
			const char* errorText = (const char*)errorBlob->GetBufferPointer();
			TalonLog(errorText);
		}

		return shader;
	}