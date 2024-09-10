HRESULT GetHash(LPCTSTR szFileName, ALG_ID iHashAlg, PBYTE pbHash, DWORD *pdwHash)
{

#define MAX_ARRAY_SIZE  16384
#define HASH_BUFFER_SIZE (MAX_ARRAY_SIZE-4)

    HRESULT    hr = E_FAIL;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    DWORD      dwBufferLen;
    BYTE      *pbBuffer = NULL;
    HANDLE     hSourceFile = INVALID_HANDLE_VALUE; 

    pbBuffer = NEW(BYTE[MAX_ARRAY_SIZE]);
    if (!pbBuffer) {
        hr = E_OUTOFMEMORY;
        goto exit;
    }

    if(!WszCryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) 
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto exit;
    }

    if(!CryptCreateHash(hProv, iHashAlg, 0, 0, &hHash)) 
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto exit;
    }

    // Open source file.
    hSourceFile = WszCreateFile (szFileName, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hSourceFile == INVALID_HANDLE_VALUE)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto exit;
    }

    while (TRUE) 
    {   
        if (!ReadFile (hSourceFile, pbBuffer, HASH_BUFFER_SIZE, &dwBufferLen, NULL)) 
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto exit;
        }
        
        if (!dwBufferLen) {
            break;
        }
                
        // Add data to hash object.
        if(!CryptHashData(hHash, pbBuffer, dwBufferLen, 0)) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto exit;
        }
    }

    if(!CryptGetHashParam(hHash, HP_HASHVAL, pbHash, pdwHash, 0)) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto exit;
    }

    hr = S_OK;

 exit:
    SAFEDELETEARRAY(pbBuffer);
    
    if (hHash)
        CryptDestroyHash(hHash);
    if (hProv)
        CryptReleaseContext(hProv,0);
    if (hSourceFile != INVALID_HANDLE_VALUE)
        CloseHandle(hSourceFile);

    return hr;
}