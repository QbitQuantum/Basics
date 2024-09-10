PixelShaderBinary::PixelShaderBinary(const std::string& filepath)
{
	std::ifstream file(filepath, std::ifstream::binary);
	if(!file)
		throw std::runtime_error("Opening file '" + filepath + "'failed!");

	//std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

	file.seekg(0, std::ifstream::end);
	std::streamoff size = file.tellg();
	D3DCreateBlob(size, m_ShaderBinary.rebind());
	file.seekg(0, std::ifstream::beg);
	file.read(static_cast<char*>(m_ShaderBinary->GetBufferPointer()), size);
	/*
	com_ptr<ID3DBlob> errors;
	HRESULT result = D3DCompile(content.c_str(),
								content.size(),
								NULL,
								NULL,
								NULL,
								"main",
								"ps_4_0",
								D3DCOMPILE_DEBUG | D3DCOMPILE_OPTIMIZATION_LEVEL0,
								0,
								m_ShaderBinary.rebind(),
								errors.rebind());

	if (FAILED(result))
	{			
		throw std::runtime_error("Compile shader '" + filepath + "' failed with error message: "
									+ static_cast<char*>(errors->GetBufferPointer()));
	}
	*/


}