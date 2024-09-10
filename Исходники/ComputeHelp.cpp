bool ComputeShader::Init(TCHAR* shaderFile, TCHAR* blobFileAppendix, char* pFunctionName, D3D10_SHADER_MACRO* pDefines,
                         ID3D11Device* d3dDevice, ID3D11DeviceContext*d3dContext)
{
    HRESULT hr = S_OK;
    mD3DDevice = d3dDevice;
    mD3DDeviceContext = d3dContext;

    ID3DBlob* pCompiledShader = nullptr;
    ID3DBlob* pErrorBlob = nullptr;

    FILE* fShaderBlob = nullptr;

    TCHAR blobFilename[300];
    if(blobFileAppendix != nullptr)
    {
        size_t l1 = _tcslen(shaderFile);
        size_t l2 = _tcslen(_tcsrchr(shaderFile, _T('.')));
        _tcsncpy_s(blobFilename, shaderFile, l1 - l2);

        _tcscat_s(blobFilename, _T("_"));
        _tcscat_s(blobFilename, blobFileAppendix);
        _tcscat_s(blobFilename, _T(".blob"));

        //MessageBox(0, blobFilename, L"", 0);

        _tfopen_s(&fShaderBlob, blobFilename, _T("rb"));
    }

    DWORD dwShaderFlags =	D3DCOMPILE_ENABLE_STRICTNESS |
                            D3DCOMPILE_IEEE_STRICTNESS |
                            //D3DCOMPILE_WARNINGS_ARE_ERRORS |
                            D3DCOMPILE_PREFER_FLOW_CONTROL;

#if defined(DEBUG) || defined(_DEBUG)
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    dwShaderFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

    if(fShaderBlob == nullptr)
    {
        //hr = D3DX11CompileFromFile(shaderFile, pDefines, nullptr, pFunctionName, "cs_5_0",
        //dwShaderFlags, nullptr, nullptr, &pCompiledShader, &pErrorBlob, nullptr);

        hr = D3DCompileFromFile(shaderFile, pDefines, D3D_COMPILE_STANDARD_FILE_INCLUDE, pFunctionName, "cs_5_0",
                                dwShaderFlags, NULL, &pCompiledShader, &pErrorBlob);

        if(hr == S_OK)
        {
            if(blobFileAppendix != nullptr)
            {
                _tfopen_s(&fShaderBlob, blobFilename, _T("wb"));

                if(fShaderBlob != nullptr)
                {
                    size_t size = pCompiledShader->GetBufferSize();
                    fwrite(&size, sizeof(size_t), 1, fShaderBlob);
                    fwrite(pCompiledShader->GetBufferPointer(), size, 1, fShaderBlob);
                    fclose(fShaderBlob);
                }
            }
        }
    }
    else
    {
        int size = 0;
        fread_s(&size, sizeof(int), sizeof(int), 1, fShaderBlob);

        if(D3DCreateBlob(size, &pCompiledShader) == S_OK)
        {
            fread_s(pCompiledShader->GetBufferPointer(), size, size, 1, fShaderBlob);
        }

        fclose(fShaderBlob);
    }
    if (pErrorBlob)
    {
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    }

    if(hr == S_OK)
    {
        hr = mD3DDevice->CreateComputeShader(pCompiledShader->GetBufferPointer(),
                                             pCompiledShader->GetBufferSize(), nullptr, &mShader);
    }

    SAFE_RELEASE(pErrorBlob);
    SAFE_RELEASE(pCompiledShader);

    return (hr == S_OK);
}