bool Cef3DDirect3D12Renderer::CompileShader(ShaderType type, unsigned flags, const char* entryPoint, const std::string& source, ID3D10Blob** outBlob)
{
	ID3DBlob* errorMsgs = 0;
	HRESULT hr = D3DCompile(source.c_str(), source.length(), "", 0, 0,
		entryPoint, type == Vertex ? "vs_5_0" : "ps_5_0", flags, 0, outBlob, &errorMsgs);

	if (FAILED(hr))
		return false;
	return true;
}