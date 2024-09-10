/**********************************************************************
 *
 * S i g n F i l e
 */
static int
SignFile(FILE *outFile, FILE *inFile, CERTCertificate *cert)
{
    int nb;
    char ibuf[4096], digestdata[32];
    const SECHashObject *hashObj;
    void *hashcx;
    unsigned int len;

    SECItem digest;
    SEC_PKCS7ContentInfo *cinfo;
    SECStatus rv;

    if (outFile == NULL || inFile == NULL || cert == NULL)
        return -1;

    /* XXX probably want to extend interface to allow other hash algorithms */
    hashObj = HASH_GetHashObject(HASH_AlgSHA1);

    hashcx = (*hashObj->create)();
    if (hashcx == NULL)
        return -1;

    (*hashObj->begin)(hashcx);

    for (;;) {
        if (feof(inFile))
            break;
        nb = fread(ibuf, 1, sizeof(ibuf), inFile);
        if (nb == 0) {
            if (ferror(inFile)) {
                PORT_SetError(SEC_ERROR_IO);
                (*hashObj->destroy)(hashcx, PR_TRUE);
                return -1;
            }
            /* eof */
            break;
        }
        (*hashObj->update)(hashcx, (unsigned char *)ibuf, nb);
    }

    (*hashObj->end)(hashcx, (unsigned char *)digestdata, &len, 32);
    (*hashObj->destroy)(hashcx, PR_TRUE);

    digest.data = (unsigned char *)digestdata;
    digest.len = len;

    cinfo = SEC_PKCS7CreateSignedData(cert, certUsageObjectSigner, NULL,
                                      SEC_OID_SHA1, &digest, NULL, NULL);

    if (cinfo == NULL)
        return -1;

    rv = SEC_PKCS7IncludeCertChain(cinfo, NULL);
    if (rv != SECSuccess) {
        SEC_PKCS7DestroyContentInfo(cinfo);
        return -1;
    }

    if (no_time == 0) {
        rv = SEC_PKCS7AddSigningTime(cinfo);
        if (rv != SECSuccess) {
            /* don't check error */
        }
    }

    rv = SEC_PKCS7Encode(cinfo, SignOut, outFile, NULL, NULL, &pwdata);

    SEC_PKCS7DestroyContentInfo(cinfo);

    if (rv != SECSuccess)
        return -1;

    return 0;
}