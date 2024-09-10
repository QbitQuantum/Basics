static int
xmlSecMSCryptoKWAesBlockDecrypt(const xmlSecByte * in, xmlSecSize inSize,
                                xmlSecByte * out, xmlSecSize outSize,
                                void * context) {
    xmlSecMSCryptoKWAesCtxPtr ctx = (xmlSecMSCryptoKWAesCtxPtr)context;
    HCRYPTKEY cryptKey = 0;
    DWORD dwCLen;

    xmlSecAssert2(in != NULL, -1);
    xmlSecAssert2(inSize >= XMLSEC_KW_AES_BLOCK_SIZE, -1);
    xmlSecAssert2(out != NULL, -1);
    xmlSecAssert2(outSize >= inSize, -1);
    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->pubPrivKey != 0, -1);
    xmlSecAssert2(xmlSecBufferGetSize(&ctx->keyBuffer) == ctx->keySize, -1);

    /* Import this key and get an HCRYPTKEY handle, we do it again and again 
       to ensure we don't go into CBC mode */
    if (!xmlSecMSCryptoImportPlainSessionBlob(ctx->cryptProvider,
        ctx->pubPrivKey,
        ctx->algorithmIdentifier,
        xmlSecBufferGetData(&ctx->keyBuffer),
        xmlSecBufferGetSize(&ctx->keyBuffer),
        TRUE,
        &cryptKey))  {

        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecMSCryptoImportPlainSessionBlob",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }
    xmlSecAssert2(cryptKey != 0, -1);

    /* Set process last block to false, since we handle padding ourselves, and MSCrypto padding
     * can be skipped. I hope this will work .... */
    if(out != in) {
        memcpy(out, in, inSize);
    }
    dwCLen = inSize;
    if(!CryptDecrypt(cryptKey, 0, FALSE, 0, out, &dwCLen)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "CryptEncrypt",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        CryptDestroyKey(cryptKey);
        return(-1);
    }

    /* cleanup */
    CryptDestroyKey(cryptKey);
    return(dwCLen);
}