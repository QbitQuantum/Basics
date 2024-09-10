int EffectSystemD3D11::CreateEffect(const char *path)
{
	// 先把char转成wchar_t
	int wchar_size = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
	wchar_t *wchar_path = new wchar_t[wchar_size];
	ZeroMemory(wchar_path, wchar_size);
	MultiByteToWideChar(CP_ACP, 0, path, -1, wchar_path, wchar_size);

	// compile
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef PE_DEBUG_MODE
	flags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob *effectBlob = nullptr;
	ID3DBlob *errorBlob = nullptr;
	// dx11只能使用fx_5_0
	HRESULT hr = D3DCompileFromFile(wchar_path, nullptr, nullptr, nullptr, "fx_5_0", flags, 0, &effectBlob, &errorBlob);	
	if (FAILED(hr))
	{
		if (errorBlob != nullptr){
			LogSystem::GetInstance().Log("编译%s出错， D3D Error：%s", path, (char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
		return -1;
	}
	if (errorBlob != nullptr){
		errorBlob->Release();
	}

	// create effect
	ID3DX11Effect *effect;
	hr = D3DX11CreateEffectFromMemory(effectBlob->GetBufferPointer(), effectBlob->GetBufferSize(), 0, mDevice, &effect);
	if (FAILED(hr))
	{
		LogSystem::GetInstance().Log("创建%s出错", path);
		return -1;
	}

	mEffects.push_back(effect);
	return (mEffects.size() - 1);
}