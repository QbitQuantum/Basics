static SECStatus
ssl3_CAPIPlatformSignHashes(SSL3Hashes *hash, PlatformKey key, SECItem *buf,
                            PRBool isTLS, KeyType keyType)
{
    SECStatus    rv             = SECFailure;
    PRBool       doDerEncode    = PR_FALSE;
    SECItem      hashItem;
    DWORD        argLen         = 0;
    DWORD        signatureLen   = 0;
    ALG_ID       hashAlg        = 0;
    HCRYPTHASH   hHash          = 0;
    DWORD        hashLen        = 0;
    unsigned int i              = 0;

    buf->data = NULL;

    switch (hash->hashAlg) {
        case SEC_OID_UNKNOWN:
            hashAlg = 0;
            break;
        case SEC_OID_SHA1:
            hashAlg = CALG_SHA1;
            break;
        case SEC_OID_SHA256:
            hashAlg = CALG_SHA_256;
            break;
        case SEC_OID_SHA384:
            hashAlg = CALG_SHA_384;
            break;
        case SEC_OID_SHA512:
            hashAlg = CALG_SHA_512;
            break;
        default:
            PORT_SetError(SSL_ERROR_UNSUPPORTED_HASH_ALGORITHM);
            return SECFailure;
    }

    switch (keyType) {
        case rsaKey:
            if (hashAlg == 0) {
                hashAlg = CALG_SSL3_SHAMD5;
            }
            hashItem.data = hash->u.raw;
            hashItem.len = hash->len;
            break;
        case dsaKey:
        case ecKey:
            if (keyType == ecKey) {
                doDerEncode = PR_TRUE;
            } else {
                doDerEncode = isTLS;
            }
            if (hashAlg == 0) {
                hashAlg = CALG_SHA1;
                hashItem.data = hash->u.s.sha;
                hashItem.len = sizeof(hash->u.s.sha);
            } else {
                hashItem.data = hash->u.raw;
                hashItem.len = hash->len;
            }
            break;
        default:
            PORT_SetError(SEC_ERROR_INVALID_KEY);
            goto done;
    }
    PRINT_BUF(60, (NULL, "hash(es) to be signed", hashItem.data, hashItem.len));

    if (!CryptCreateHash(key->hCryptProv, hashAlg, 0, 0, &hHash)) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, GetLastError());
        goto done;
    }
    argLen = sizeof(hashLen);
    if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashLen, &argLen, 0)) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, GetLastError());
        goto done;
    }
    if (hashLen != hashItem.len) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, 0);
        goto done;
    }
    if (!CryptSetHashParam(hHash, HP_HASHVAL, (BYTE*)hashItem.data, 0)) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, GetLastError());
        goto done;
    }
    if (!CryptSignHash(hHash, key->dwKeySpec, NULL, 0,
                       NULL, &signatureLen) || signatureLen == 0) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, GetLastError());
        goto done;
    }
    buf->data = (unsigned char *)PORT_Alloc(signatureLen);
    if (!buf->data)
        goto done;    /* error code was set. */

    if (!CryptSignHash(hHash, key->dwKeySpec, NULL, 0,
                       (BYTE*)buf->data, &signatureLen)) {
        PR_SetError(SSL_ERROR_SIGN_HASHES_FAILURE, GetLastError());
        goto done;
    }
    buf->len = signatureLen;

    /* CryptoAPI signs in little-endian, so reverse */
    for (i = 0; i < buf->len / 2; ++i) {
        unsigned char tmp = buf->data[i];
        buf->data[i] = buf->data[buf->len - 1 - i];
        buf->data[buf->len - 1 - i] = tmp;
    }
    if (doDerEncode) {
        SECItem   derSig = {siBuffer, NULL, 0};

        /* This also works for an ECDSA signature */
        rv = DSAU_EncodeDerSigWithLen(&derSig, buf, buf->len);
        if (rv == SECSuccess) {
            PORT_Free(buf->data);     /* discard unencoded signature. */
            *buf = derSig;            /* give caller encoded signature. */
        } else if (derSig.data) {
            PORT_Free(derSig.data);
        }
    } else {
        rv = SECSuccess;
    }

    PRINT_BUF(60, (NULL, "signed hashes", buf->data, buf->len));
done:
    if (hHash)
        CryptDestroyHash(hHash);
    if (rv != SECSuccess && buf->data) {
        PORT_Free(buf->data);
        buf->data = NULL;
    }
    return rv;
}