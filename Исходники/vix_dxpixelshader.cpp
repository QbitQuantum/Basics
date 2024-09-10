    bool DXPixelShader::VInitShader(File* file)
    {
        HRESULT hr = S_OK;

        BYTE* data = new BYTE[VIX_LARGE_BUFSIZE];
        file->Seek(0, FileSeek::End);
        size_t _size = file->Tell();
        file->Seek(0, FileSeek::Set);
        file->Read(data, _size); //read all of the file into memory

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // Disable optimizations to further improve shader debugging
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
       
        ID3DBlob* errorBlob = nullptr;
        hr = D3DCompile2(data, _size, nullptr, nullptr,
            nullptr, "main", "ps_5_0", NULL, NULL, NULL, NULL, NULL,
            &m_shaderBlob, &errorBlob);
        //hr = D3DReadFileToBlob(file->FilePath().c_str(), &m_shaderBlob);
        if (FAILED(hr))
        {
            if (errorBlob)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
                errorBlob->Release();
            }
            return false;
        }
        if (errorBlob) errorBlob->Release();

        // Create the vertex shader
        hr = m_device->CreatePixelShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), nullptr, &m_shader);
        if (FAILED(hr))
        {
            ReleaseCOM(m_shaderBlob);
            return false;
        }

        return true;
    }