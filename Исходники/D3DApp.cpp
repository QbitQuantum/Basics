ID3DBlob* D3DApp::GenerateShader(const std::string& filename, const std::string& function,
	const std::string& model, const D3D_SHADER_MACRO* pDefines)
{
	HRESULT hr = S_OK;

	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrorMessages = nullptr;

	UINT flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#endif

	std::ifstream shaderFile(filename);
	std::string hlslCode((std::istreambuf_iterator<char>(shaderFile)),
		std::istreambuf_iterator<char>());

	HR(D3DCompile(
		hlslCode.c_str(),
		hlslCode.size(),
		nullptr,
		pDefines,
		nullptr,
		function.c_str(),
		model.c_str(),
		flags,
		0,
		&pCompiledShader,
		&pErrorMessages));

	ReleaseCOM(pErrorMessages);

	return(pCompiledShader);
}