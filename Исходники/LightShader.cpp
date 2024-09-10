bool LightShader::initializeShader(ID3D11Device * device, HWND hwnd, const WCHAR * vsFilename, const WCHAR * psFilename) {

	ID3D10Blob* errorBlob;
	ID3D10Blob* vertexShaderBlob;
	ID3D10Blob* pixelShaderBlob;


	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if _DEBUG
	flags |= D3DCOMPILE_DEBUG;
#endif

	// Compile the vertex shader code.
	if (FAILED(D3DCompileFromFile(vsFilename, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"DiffuseLightVertexShader", Globals::VERTEX_SHADER_VERSION,
		flags, 0, &vertexShaderBlob, &errorBlob))) {
		if (errorBlob) {
			outputShaderErrorMessage(errorBlob, hwnd, vsFilename);
		} else {
			MessageBox(hwnd, vsFilename, L"Missing Vertex Shader File", MB_OK);
		}

		return false;
	}

	if (FAILED(D3DCompileFromFile(psFilename, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"DiffuseLightPixelShader", Globals::PIXEL_SHADER_VERSION,
		flags, 0, &pixelShaderBlob, &errorBlob))) {
		if (errorBlob) {
			outputShaderErrorMessage(errorBlob, hwnd, psFilename);
		} else {
			MessageBox(hwnd, psFilename, L"Missing Pixel Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	if (FAILED(device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(), NULL, &vertexShader))) {
		MessageBox(NULL, L"Error creating Vertex Shader", L"ERROR", MB_OK);
		return false;
	}

	// Create the pixel shader from the buffer.
	if (FAILED(device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize(), NULL, &pixelShader))) {
		MessageBox(NULL, L"Error creating Pixel Shader", L"ERROR", MB_OK);
		return false;
	}


	if (FAILED(initInputLayout(device, vertexShaderBlob))) {
		MessageBox(NULL, L"Error creating Input Layout Buffer", L"ERROR", MB_OK);
		return false;
	}

	safeRelease(vertexShaderBlob);
	safeRelease(pixelShaderBlob);


	if (FAILED(initMatrixBuffer(device))) {
		MessageBox(NULL, L"Error creating Constant (Matrix) Buffer", L"ERROR", MB_OK);
		return false;
	}

	if (FAILED(initSamplerState(device))) {
		MessageBox(NULL, L"Error creating Sampler Shader", L"ERROR", MB_OK);
		return false;
	}

	if (FAILED(initLightBuffer(device))) {
		return false;
	}

	return true;
}