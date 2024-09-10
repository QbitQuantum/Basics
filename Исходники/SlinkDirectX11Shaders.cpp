	static ID3DBlobPtr CompileShader(const char* shaderCode, size_t shaderLength, const char* shaderProfile) {
		ID3DBlobPtr blob = nullptr;
		ID3DBlobPtr errors = nullptr;
		HRESULT hr = D3DCompile(shaderCode, shaderLength, nullptr, nullptr, nullptr, "Main", shaderProfile, 0, 0, &blob, &errors);

		if (FAILED(hr)) {

			if (errors) {
				OutputDebugStringA((char*)errors->GetBufferPointer());
				errors->Release();
			}

			return nullptr;
		}

		return blob;
	}