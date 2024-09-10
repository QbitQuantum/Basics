/*********************************************************************
 *
 * DES KW implementation
 *
 *********************************************************************/
static int
xmlSecMSCryptoKWDes3Sha1(void * context,
                       const xmlSecByte * in, xmlSecSize inSize, 
                       xmlSecByte * out, xmlSecSize outSize) {
    xmlSecMSCryptoKWDes3CtxPtr ctx = (xmlSecMSCryptoKWDes3CtxPtr)context;
    HCRYPTHASH mscHash = 0;
    DWORD retLen;
    int ret;

    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->sha1CryptProvider != 0, -1);
    xmlSecAssert2(ctx->sha1AlgorithmIdentifier != 0, -1);
    xmlSecAssert2(in != NULL, -1);
    xmlSecAssert2(inSize > 0, -1);
    xmlSecAssert2(out != NULL, -1);
    xmlSecAssert2(outSize > 0, -1);

    /* create */
    ret = CryptCreateHash(ctx->sha1CryptProvider,
        ctx->sha1AlgorithmIdentifier,
        0,
        0,
        &mscHash);
    if((ret == 0) || (mscHash == 0)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "CryptCreateHash",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    /* hash */
    ret = CryptHashData(mscHash,
        in, 
        inSize,
        0);
    if(ret == 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "CryptHashData",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    "size=%d", inSize);
        CryptDestroyHash(mscHash);
        return(-1);
    }

    /* get results */
    retLen = outSize;
    ret = CryptGetHashParam(mscHash,
        HP_HASHVAL,
        out,
        &retLen,
        0);
    if (ret == 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "CryptGetHashParam(HP_HASHVAL)",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", outSize);
        CryptDestroyHash(mscHash);
        return(-1);
    }

    /* done */
    CryptDestroyHash(mscHash);
    return(retLen);
}