static int
_libssh2_wincng_asn_decode(unsigned char *pbEncoded,
                           unsigned long cbEncoded,
                           LPCSTR lpszStructType,
                           unsigned char **ppbDecoded,
                           unsigned long *pcbDecoded)
{
    unsigned char *pbDecoded = NULL;
    unsigned long cbDecoded = 0;
    int ret;

    ret = CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                              lpszStructType,
                              pbEncoded, cbEncoded, 0, NULL,
                              NULL, &cbDecoded);
    if (!ret) {
        return -1;
    }

    pbDecoded = malloc(cbDecoded);
    if (!pbDecoded) {
        return -1;
    }

    ret = CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                              lpszStructType,
                              pbEncoded, cbEncoded, 0, NULL,
                              pbDecoded, &cbDecoded);
    if (!ret) {
        free(pbDecoded);
        return -1;
    }


    *ppbDecoded = pbDecoded;
    *pcbDecoded = cbDecoded;

    return 0;
}