// =========================================================================
// Decryption function
// Note: PlaintextLength must be set to the size of the PlaintextData buffer on
//       entry; on exit, this will be set to the size of the buffer used.
NTSTATUS
ImpCypherDecryptSectorData(
    IN      GUID* CypherGUID,
    IN      LARGE_INTEGER SectorID,  // Indexed from zero
    IN      int SectorSize, // In bytes
    IN      int KeyLength,  // In bits
    IN      FREEOTFEBYTE* Key,
    IN      char* KeyASCII,  // ASCII representation of "Key"
    IN      int IVLength,  // In bits
    IN      FREEOTFEBYTE* IV,
    IN      int CyphertextLength,  // In bytes
    IN      FREEOTFEBYTE* CyphertextData,
    OUT     FREEOTFEBYTE* PlaintextData
)
{
    NTSTATUS status = STATUS_SUCCESS;
    // libtomcrypt can't handle NULL IVs in CBC mode - it ASSERTs that IV != NULL
    char ltcNullIV[FREEOTFE_MAX_CYPHER_BLOCKSIZE];
    int cipher;
    symmetric_CBC *cbc;
    int errnum;
    unsigned int blockLength;


    DEBUGOUTCYPHERIMPL(DEBUGLEV_ENTER, (TEXT("ImpCypherDecryptData\n")));


    cbc = FREEOTFE_MEMALLOC(sizeof(symmetric_CBC));    
    FREEOTFE_MEMZERO(cbc, sizeof(symmetric_CBC));

    if (IsEqualGUID(&CIPHER_GUID_DES, CypherGUID))
        {
	status = InitLTCDESCypher(&cipher);
        blockLength = des_desc.block_length;
        }
    else if (IsEqualGUID(&CIPHER_GUID_3DES, CypherGUID))
        {
	status = InitLTC3DESCypher(&cipher);
        blockLength = des3_desc.block_length;
        }
    else
        {
	      DEBUGOUTCYPHERIMPL(DEBUGLEV_ERROR, (TEXT("Unsupported cipher GUID passed in.\n")));
        status = STATUS_INVALID_PARAMETER;
        }

    // libtomcrypt can't handle NULL IVs in CBC mode - it ASSERTs that IV != NULL
    if ( (IVLength == 0) || (IV == NULL) )
        {
        FREEOTFE_MEMZERO(&ltcNullIV, sizeof(ltcNullIV));
        IV = (char*)&ltcNullIV;
        }

    if NT_SUCCESS(status)
        {
        // Start a CBC session
        if ((errnum = cbc_start(
                                cipher, 
                                IV, 
                                Key, 
                                (KeyLength/8), 
                                0, 
                                cbc
                               )) != CRYPT_OK)
            {
            status = STATUS_UNSUCCESSFUL;
            DEBUGOUTCYPHERIMPL(DEBUGLEV_ERROR, (TEXT("Unable to start CBC session (errnum: %d)\n"), errnum));
            }
        else
            {
            if ((errnum = cbc_decrypt(
                                      CyphertextData, 
                                      PlaintextData, 
                                      CyphertextLength, 
                                      cbc
                                     )) != CRYPT_OK)
                {
                DEBUGOUTCYPHERIMPL(DEBUGLEV_ERROR, (TEXT("Unable to encrypt/decrypt block (errnum: %d)\n"), errnum));
                status = STATUS_UNSUCCESSFUL;
                }

            cbc_done(cbc);
            }
        }

    SecZeroMemory(cbc, sizeof(symmetric_CBC));
    FREEOTFE_FREE(cbc);

    DEBUGOUTCYPHERIMPL(DEBUGLEV_EXIT, (TEXT("ImpCypherDecryptData\n")));

    return status;
}