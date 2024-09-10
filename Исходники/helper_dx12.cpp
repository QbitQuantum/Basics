ComPtr<ID3DBlob> afCompileShader(const char* name, const char* entryPoint, const char* target)
{
	char path[MAX_PATH];
	sprintf_s(path, sizeof(path), "%s.hlsl", name);
	//	sprintf_s(path, sizeof(path), "hlsl/%s.hlsl", name);
#ifdef _DEBUG
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#endif
	ComPtr<ID3DBlob> blob, err;
	WCHAR wname[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, path, -1, wname, dimof(wname));
	D3DCompileFromFile(wname, nullptr, nullptr, entryPoint, target, flags, 0, &blob, &err);
	if (err) {
		MessageBoxA(nullptr, (const char*)err->GetBufferPointer(), name, MB_OK | MB_ICONERROR);
	}
	return blob;
}