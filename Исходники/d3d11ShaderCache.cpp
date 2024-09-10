static ID3DBlob *
_CompileShader(std::string const &target,
               std::string const &entry,
               std::string const &shaderSource) {
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pBlob = NULL;
    ID3DBlob* pBlobError = NULL;

    HRESULT hr = D3DCompile(shaderSource.c_str(), shaderSource.size(),
                            NULL, NULL, NULL,
                            entry.c_str(), target.c_str(),
                            dwShaderFlags, 0, &pBlob, &pBlobError);
    if (FAILED(hr)) {
        if ( pBlobError != NULL ) {
            OpenSubdiv::Far::Error(OpenSubdiv::Far::FAR_RUNTIME_ERROR,
                     "Error compiling HLSL shader: %s\n",
                     (CHAR*)pBlobError->GetBufferPointer());
            pBlobError->Release();
            return NULL;
        }
    }

    return pBlob;
}