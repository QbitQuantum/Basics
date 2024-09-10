/******************************************************************************
 *
 * Utils
 *
 * Low level helper routines for importing plain text keys in MS HKEY handle,
 * since MSCrypto API does not support import of plain text (session) keys
 * just like that. These functions are based upon MS kb article #228786
 * and "Base Provider Key BLOBs" article for priv key blob format.
 *
 ******************************************************************************/
BOOL
xmlSecMSCryptoCreatePrivateExponentOneKey(HCRYPTPROV hProv, HCRYPTKEY *hPrivateKey)
{
    HCRYPTKEY hKey = 0;
    LPBYTE keyBlob = NULL;
    DWORD keyBlobLen;
    PUBLICKEYSTRUC* pubKeyStruc;
    RSAPUBKEY* rsaPubKey;
    DWORD bitLen;
    BYTE *ptr;
    int n;
    BOOL res = FALSE;

    xmlSecAssert2(hProv != 0, FALSE);
    xmlSecAssert2(hPrivateKey != NULL, FALSE);

    /* just in case */
    *hPrivateKey = 0;

    /* Generate the private key */
    if(!CryptGenKey(hProv, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &hKey)) {
        xmlSecMSCryptoError("CryptGenKey", NULL);
        goto done;
    }

    /* Export the private key, we'll convert it to a private exponent of one key */
    if(!CryptExportKey(hKey, 0, PRIVATEKEYBLOB, 0, NULL, &keyBlobLen)) {
        xmlSecMSCryptoError("CryptExportKey", NULL);
        goto done;
    }

    keyBlob = (LPBYTE)xmlMalloc(sizeof(BYTE) * keyBlobLen);
    if(keyBlob == NULL) {
        xmlSecMallocError(sizeof(BYTE) * keyBlobLen, NULL);
        goto done;
    }

    if(!CryptExportKey(hKey, 0, PRIVATEKEYBLOB, 0, keyBlob, &keyBlobLen)) {
        xmlSecMSCryptoError("CryptExportKey", NULL);
        goto done;
    }
    CryptDestroyKey(hKey);
    hKey = 0;

    /* Get the bit length of the key */
    if(keyBlobLen < sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY)) {
        xmlSecMSCryptoError2("CryptExportKey", NULL,
                             "len=%ld",
                             (long int)keyBlobLen);
        goto done;
    }
    pubKeyStruc = (PUBLICKEYSTRUC*)keyBlob;
    if(pubKeyStruc->bVersion != 0x02) {
        xmlSecMSCryptoError2("CryptExportKey", NULL,
                             "pubKeyStruc->bVersion=%ld",
                             (long int)pubKeyStruc->bVersion);
        goto done;
    }
    if(pubKeyStruc->bType != PRIVATEKEYBLOB) {
        xmlSecMSCryptoError2("CryptExportKey", NULL,
                             "pubKeyStruc->bType=%ld",
                             (long int)pubKeyStruc->bType);
        goto done;
    }

    /* aleksey: don't ask me why it is RSAPUBKEY, just don't ask */
    rsaPubKey = (RSAPUBKEY*)(keyBlob + sizeof(PUBLICKEYSTRUC));

    /* check that we have RSA private key */
    if(rsaPubKey->magic != 0x32415352) {
        xmlSecMSCryptoError2("CryptExportKey", NULL,
                             "rsaPubKey->magic=0x%08lx",
                             (long int)rsaPubKey->magic);
        goto done;
    }
    bitLen = rsaPubKey->bitlen;

    /*  Modify the Exponent in Key BLOB format Key BLOB format is documented in SDK */
    rsaPubKey->pubexp = 1;

    /* Private-key BLOBs, type PRIVATEKEYBLOB, are used to store private keys outside a CSP.
     * Base provider private-key BLOBs have the following format:
     *
     * PUBLICKEYSTRUC  publickeystruc ;
     * RSAPUBKEY rsapubkey;
     * BYTE modulus[rsapubkey.bitlen/8];                1/8
     * BYTE prime1[rsapubkey.bitlen/16];                1/16
     * BYTE prime2[rsapubkey.bitlen/16];                1/16
     * BYTE exponent1[rsapubkey.bitlen/16];             1/16
     * BYTE exponent2[rsapubkey.bitlen/16];             1/16
     * BYTE coefficient[rsapubkey.bitlen/16];           1/16
     * BYTE privateExponent[rsapubkey.bitlen/8];        1/8
     */
    if(keyBlobLen < sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY) + bitLen / 2 + bitLen / 16) {
        xmlSecMSCryptoError2("CryptExportKey", NULL,
                             "keBlobLen=%ld", keyBlobLen);
        goto done;
    }
    ptr = (BYTE*)(keyBlob + sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY));

    /* Skip modulus, prime1, prime2 */
    ptr += bitLen / 8;
    ptr += bitLen / 16;
    ptr += bitLen / 16;

    /* Convert exponent1 to 1 */
    for (n = 0; n < (bitLen / 16); n++) {
        if (n == 0) ptr[n] = 1;
        else ptr[n] = 0;
    }
    ptr += bitLen / 16;

    /* Convert exponent2 to 1 */
    for (n = 0; n < (bitLen / 16); n++) {
        if (n == 0) ptr[n] = 1;
        else ptr[n] = 0;
    }
    ptr += bitLen / 16;

    /* Skip coefficient */
    ptr += bitLen / 16;

    /* Convert privateExponent to 1 */
    for (n = 0; n < (bitLen / 16); n++) {
        if (n == 0) ptr[n] = 1;
        else ptr[n] = 0;
    }

    /* Import the exponent-of-one private key. */
    if (!CryptImportKey(hProv, keyBlob, keyBlobLen, 0, 0, &hKey)) {
        xmlSecMSCryptoError("CryptImportKey", NULL);
        goto done;
    }
    (*hPrivateKey) = hKey;
    hKey = 0;
    res = TRUE;

done:
    if(keyBlob != NULL) {
        xmlFree(keyBlob);
    }
    if (hKey != 0) {
        CryptDestroyKey(hKey);
    }

    return res;
}