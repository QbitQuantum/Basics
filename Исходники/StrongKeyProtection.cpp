    
    LPCWSTR                 KeyName = L"SampleStrongKey";
    PBYTE                   Signature = NULL;
    DWORD                   SignatureLength = 0;
    DWORD                   ResultLength = 0;
    
    BCRYPT_PKCS1_PADDING_INFO PKCS1PaddingInfo;
    VOID                    *pPaddingInfo;
    HWND                    hwndConsole = NULL;

    //
    // Open Microsoft KSP (Key Storage Provider) 
    //

    secStatus = NCryptOpenStorageProvider(
                                        &ProviderHandle,            // Pointer to a variable that recieves the provider handle
                                        MS_KEY_STORAGE_PROVIDER,    // Storage provider identifier(null terminated unicode string); If NULL, default provider is loaded
                                        0);                         // Flags
    if( FAILED(secStatus) )
    {
        ReportError(secStatus);
        goto cleanup;
    }

    //
    // Create an RSA key signature key in MS KSP.
    // NCRYPT_OVERWRITE_KEY_FLAG - is used to overwrite an existing key with the provided name.
    //

    secStatus = NCryptCreatePersistedKey(
                                        ProviderHandle,             // Handle of the key storage provider
                                        &KeyHandle,                 // Address of the variable that recieves the key handle