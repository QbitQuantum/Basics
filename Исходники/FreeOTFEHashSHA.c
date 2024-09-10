// =========================================================================
// Hash function
NTSTATUS
ImpHashHashData(
    IN      GUID* HashGUID,
    IN      unsigned int DataLength,  // In bits
    IN      FREEOTFEBYTE* Data,
    IN OUT  unsigned int* HashLength,  // In bits
    OUT     FREEOTFEBYTE* Hash
)
{
    NTSTATUS status = STATUS_SUCCESS;
    hash_state md;
    WCHAR* tmpGUIDStr;

    DEBUGOUTHASHIMPL(DEBUGLEV_ENTER, (TEXT("ImpHashHashData\n")));
    if (IsEqualGUID(&HASH_GUID_SHA512, HashGUID))
        {
        if (*HashLength < (sha512_desc.hashsize * 8))
            {
            DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("output hash length buffer too small (got: %d; need: %d)\n"),
                *HashLength,
                (sha512_desc.hashsize * 8)
                ));
            status = STATUS_BUFFER_TOO_SMALL;
            }
        else
            {
            sha512_desc.init(&md);
            sha512_desc.process(&md, Data, (DataLength / 8));
            sha512_desc.done(&md, Hash);
        
            *HashLength = (sha512_desc.hashsize * 8);
            }
            
        }
    else if (IsEqualGUID(&HASH_GUID_SHA384, HashGUID))
        {
        if (*HashLength < (sha384_desc.hashsize * 8))
            {
            DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("output hash length buffer too small (got: %d; need: %d)\n"),
                *HashLength,
                (sha384_desc.hashsize * 8)
                ));
            status = STATUS_BUFFER_TOO_SMALL;
            }
        else
            {
            sha384_desc.init(&md);
            sha384_desc.process(&md, Data, (DataLength / 8));
            sha384_desc.done(&md, Hash);
        
            *HashLength = (sha384_desc.hashsize * 8);
            }
            
        }
    else if (IsEqualGUID(&HASH_GUID_SHA256, HashGUID))
        {
        if (*HashLength < (sha256_desc.hashsize * 8))
            {
            DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("output hash length buffer too small (got: %d; need: %d)\n"),
                *HashLength,
                (sha256_desc.hashsize * 8)
                ));
            status = STATUS_BUFFER_TOO_SMALL;
            }
        else
            {
            sha256_desc.init(&md);
            sha256_desc.process(&md, Data, (DataLength / 8));
            sha256_desc.done(&md, Hash);
        
            *HashLength = (sha256_desc.hashsize * 8);
            }
            
        }
    else if (IsEqualGUID(&HASH_GUID_SHA224, HashGUID))
        {
        if (*HashLength < (sha224_desc.hashsize * 8))
            {
            DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("output hash length buffer too small (got: %d; need: %d)\n"),
                *HashLength,
                (sha224_desc.hashsize * 8)
                ));
            status = STATUS_BUFFER_TOO_SMALL;
            }
        else
            {
            sha224_desc.init(&md);
            sha224_desc.process(&md, Data, (DataLength / 8));
            sha224_desc.done(&md, Hash);
        
            *HashLength = (sha224_desc.hashsize * 8);
            }
            
        }
    else if (IsEqualGUID(&HASH_GUID_SHA1, HashGUID))
        {
        if (*HashLength < (sha1_desc.hashsize * 8))
            {
            DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("output hash length buffer too small (got: %d; need: %d)\n"),
                *HashLength,
                (sha1_desc.hashsize * 8)
                ));
            status = STATUS_BUFFER_TOO_SMALL;
            }
        else
            {
            sha1_desc.init(&md);
            sha1_desc.process(&md, Data, (DataLength / 8));
            sha1_desc.done(&md, Hash);
        
            *HashLength = (sha1_desc.hashsize * 8);
            }
            
        }
    else
        {
        DEBUGOUTHASHIMPL(DEBUGLEV_ERROR, (TEXT("Driver doesn't recognise GUID\n")));
        GUIDToWCHAR(HashGUID, &tmpGUIDStr);
        DEBUGOUTHASHIMPL(DEBUGLEV_INFO, (TEXT("Hash passed in: %ls\n"), tmpGUIDStr));
        SecZeroAndFreeWCHARMemory(tmpGUIDStr);
        status = STATUS_INVALID_PARAMETER;
        }
        
    DEBUGOUTHASHIMPL(DEBUGLEV_EXIT, (TEXT("ImpHashHashData\n")));
      
    return status;
}