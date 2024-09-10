static ID3DBlob* CompileShader(const wchar* path, const char* functionName, ShaderType type, ShaderProfile profile,
                              const D3D_SHADER_MACRO* defines, bool forceOptimization, GrowableList<wstring>& filePaths)
{
    if(FileExists(path) == false)
    {
        Assert_(false);
        throw Exception(L"Shader file " + std::wstring(path) + L" does not exist");
    }

    uint64 profileIdx = uint64(profile) * uint64(ShaderType::NumTypes) + uint64(type);
    Assert_(profileIdx < TotalNumProfiles);
    const char* profileString = ProfileStrings[profileIdx];

    // Make a hash off the expanded shader code
    string shaderCode = GetExpandedShaderCode(path, filePaths);
    wstring cacheName = MakeShaderCacheName(shaderCode, functionName, profileString, defines);

    if(FileExists(cacheName.c_str()))
    {
        File cacheFile(cacheName.c_str(), FileOpenMode::Read);

        const uint64 shaderSize = cacheFile.Size();
        Array<uint8> compressedShader;
        compressedShader.Init(shaderSize);
        cacheFile.Read(shaderSize, compressedShader.Data());

        ID3DBlob* decompressedShader[1] = { nullptr };
        uint32 indices[1] = { 0 };
        DXCall(D3DDecompressShaders(compressedShader.Data(), shaderSize, 1, 0,
                                    indices, 0, decompressedShader, nullptr));

        return decompressedShader[0];
    }

    WriteLog("Compiling %s shader %s_%s %s\n", TypeStrings[uint64(type)],
                WStringToAnsi(GetFileName(path).c_str()).c_str(),
                functionName, MakeDefinesString(defines).c_str());

    // Loop until we succeed, or an exception is thrown
    while(true)
    {
        UINT flags = D3DCOMPILE_WARNINGS_ARE_ERRORS;
        #ifdef _DEBUG
            flags |= D3DCOMPILE_DEBUG;
            // This is causing some shader bugs
            /*if(forceOptimization == false)
                flags |= D3DCOMPILE_SKIP_OPTIMIZATION;*/
        #endif

        ID3DBlob* compiledShader;
        ID3DBlobPtr errorMessages;
        FrameworkInclude include;
        HRESULT hr = D3DCompileFromFile(path, defines, &include, functionName,
                                        profileString, flags, 0, &compiledShader, &errorMessages);

        if(FAILED(hr))
        {
            if(errorMessages)
            {
                wchar message[1024] = { 0 };
                char* blobdata = reinterpret_cast<char*>(errorMessages->GetBufferPointer());

                MultiByteToWideChar(CP_ACP, 0, blobdata, static_cast<int>(errorMessages->GetBufferSize()), message, 1024);
                std::wstring fullMessage = L"Error compiling shader file \"";
                fullMessage += path;
                fullMessage += L"\" - ";
                fullMessage += message;

                // Pop up a message box allowing user to retry compilation
                int retVal = MessageBoxW(nullptr, fullMessage.c_str(), L"Shader Compilation Error", MB_RETRYCANCEL);
                if(retVal != IDRETRY)
                    throw DXException(hr, fullMessage.c_str());
            }
            else
            {
                Assert_(false);
                throw DXException(hr);
            }
        }
        else
        {
            // Compress the shader
            D3D_SHADER_DATA shaderData;
            shaderData.pBytecode = compiledShader->GetBufferPointer();
            shaderData.BytecodeLength = compiledShader->GetBufferSize();
            ID3DBlobPtr compressedShader;
            DXCall(D3DCompressShaders(1, &shaderData, D3D_COMPRESS_SHADER_KEEP_ALL_PARTS, &compressedShader));

            // Create the cache directory if it doesn't exist
            if(DirectoryExists(baseCacheDir.c_str()) == false)
                Win32Call(CreateDirectory(baseCacheDir.c_str(), nullptr));

            if(DirectoryExists(cacheDir.c_str()) == false)
                Win32Call(CreateDirectory(cacheDir.c_str(), nullptr));

            File cacheFile(cacheName.c_str(), FileOpenMode::Write);

            // Write the compiled shader to disk
            uint64 shaderSize = compressedShader->GetBufferSize();
            cacheFile.Write(shaderSize, compressedShader->GetBufferPointer());

            return compiledShader;
        }
    }
}