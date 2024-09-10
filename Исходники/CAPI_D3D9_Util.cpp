ID3DBlob* ShaderCompile(char * shaderName, const char * shaderSrcString, const char * profile)
{
    ID3DBlob* pShaderCode = NULL;
    ID3DBlob* pErrorMsg = NULL;

    if (FAILED(D3DCompile(shaderSrcString, strlen(shaderSrcString),NULL,NULL,NULL,
                          "main",profile,D3DCOMPILE_OPTIMIZATION_LEVEL3,0,
                          &pShaderCode,&pErrorMsg)))
        MessageBoxA(NULL,(char *) pErrorMsg->GetBufferPointer(),"", MB_OK);
    if (pErrorMsg) pErrorMsg->Release();

    //Now write out blob
    char tempString[1000];
    int numDWORDs = ((int)pShaderCode->GetBufferSize())/4;
    DWORD * ptr = (DWORD *)pShaderCode->GetBufferPointer();
    sprintf_s(tempString,"DWORD %s[%d] = {",shaderName,numDWORDs);
    OutputDebugStringA(tempString);
    for (int i = 0; i < numDWORDs; i++)
    {
        sprintf_s(tempString,"%lu,",ptr[i]);
        OutputDebugStringA(tempString);
    }
    OutputDebugStringA("};\n");

    return(pShaderCode);
}