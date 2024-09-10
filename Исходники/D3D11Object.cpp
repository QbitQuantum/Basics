//--------------------------------------------------------------------------------------
// Helper function to compile an hlsl shader from file, 
// its binary compiled code is returned
//--------------------------------------------------------------------------------------
HRESULT D3D11Object::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, 
LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    // find the file
    //WCHAR str[MAX_PATH];
    //V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, szFileName ) );
	WCHAR *str = szFileName;
    // open the file 
	//"createFile" creates or opens the file
    HANDLE hFile = CreateFile( szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN, NULL );
    if( INVALID_HANDLE_VALUE == hFile )
        return E_FAIL;

    // Get the file size
    LARGE_INTEGER FileSize;
    GetFileSizeEx( hFile, &FileSize );

    // create enough space for the file data
    BYTE* pFileData = new BYTE[ FileSize.LowPart ];
    if( !pFileData )
        return E_OUTOFMEMORY;

    // read the data in
    DWORD BytesRead;
    if( !ReadFile( hFile, pFileData, FileSize.LowPart, &BytesRead, NULL ) )
        return E_FAIL; 

    CloseHandle( hFile );

    // Compile the shader
    char pFilePathName[MAX_PATH];        
    WideCharToMultiByte(CP_ACP, 0, str, -1, pFilePathName, MAX_PATH, NULL, NULL);
    ID3DBlob* pErrorBlob;
    hr = D3DCompile( pFileData, FileSize.LowPart, pFilePathName, NULL, NULL, szEntryPoint, 
                      szShaderModel, D3D10_SHADER_ENABLE_STRICTNESS, 0, ppBlobOut, &pErrorBlob );


    delete []pFileData;
  
    if( FAILED(hr) )
    {
        printf( (char*)pErrorBlob->GetBufferPointer() );
        SAFE_RELEASE( pErrorBlob );
        return hr;
    }
    SAFE_RELEASE( pErrorBlob );

    return S_OK;
}