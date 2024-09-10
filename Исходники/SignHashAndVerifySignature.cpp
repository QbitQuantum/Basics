    
    PBYTE                   HashDigest       = NULL;
    DWORD                   HashDigestLength = 0;

    DWORD                   ResultLength     = 0;
    
    *DataDigestPointer = NULL;
    *DataDigestLengthPointer = 0;

    //
    // Open a Hash algorithm handle
    //

    Status = BCryptOpenAlgorithmProvider(
                                        &HashAlgHandle,
                                        BCRYPT_SHA1_ALGORITHM,
                                        NULL,
                                        0);
    if( !NT_SUCCESS(Status) )
    {
        ReportError(Status);
        goto cleanup;
    }

    
    //
    // Calculate the length of the Hash
    //
    
    Status= BCryptGetProperty(
                                        HashAlgHandle, 