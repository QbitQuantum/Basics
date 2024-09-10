CPixelBufferView::PixelShaderPtr CPixelBufferView::CreatePixelShaderFromResource(const TCHAR* resourceName)
{
	HRESULT result = S_OK;

	auto shaderResourceInfo = FindResource(GetModuleHandle(nullptr), resourceName, _T("TEXTFILE"));
	assert(shaderResourceInfo != nullptr);

	auto shaderResourceHandle = LoadResource(GetModuleHandle(nullptr), shaderResourceInfo);
	auto shaderResourceSize = SizeofResource(GetModuleHandle(nullptr), shaderResourceInfo);

	auto shaderResource = reinterpret_cast<const char*>(LockResource(shaderResourceHandle));

	UINT compileFlags = 0;
#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	Framework::Win32::CComPtr<ID3DBlob> shaderBinary;
	Framework::Win32::CComPtr<ID3DBlob> compileErrors;
	result = D3DCompile(shaderResource, shaderResourceSize, "ps", nullptr, nullptr, "main",
	                    "ps_3_0", compileFlags, 0, &shaderBinary, &compileErrors);
	assert(SUCCEEDED(result));

	PixelShaderPtr shader;
	result = m_device->CreatePixelShader(reinterpret_cast<DWORD*>(shaderBinary->GetBufferPointer()), &shader);
	assert(SUCCEEDED(result));

	return shader;
}