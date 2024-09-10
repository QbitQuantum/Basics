/**
 * Adds a certificate to a store.
 *
 * @returns true on success, false on failure (error message written).
 * @param   dwDst           The destination, like
 *                          CERT_SYSTEM_STORE_LOCAL_MACHINE or
 *                          CERT_SYSTEM_STORE_CURRENT_USER.
 * @param   pszStoreNm      The store name.
 * @param   kpCertBuf       Buffer that contains a certificate
 * @param   cbCertBuf       Size of @param kpCertBuf in bytes
 */
bool addCertToStore(DWORD dwDst, const char *pszStoreNm, const unsigned char kpCertBuf[], DWORD cbCertBuf)
{
    /*
     * Get certificate from buffer.
     */
    PCCERT_CONTEXT  pSrcCtx = NULL;
    bool            fRc     = false;

    if (!readCertBuf(kpCertBuf, cbCertBuf, &pSrcCtx))
    {
        RTMsgError("Unable to get certificate context: %d", GetLastError());
        return fRc;
    }

    /*
     * Open the certificates store.
     */
    HCERTSTORE hDstStore = openCertStore(dwDst, pszStoreNm);
    if (hDstStore)
    {
        /*
         * Finally, add certificate to store
         */
        if (CertAddCertificateContextToStore(hDstStore, pSrcCtx, CERT_STORE_ADD_REPLACE_EXISTING, NULL))
            fRc = true;
        else
            RTMsgError("Unable to install certificate: %d", GetLastError());

        CertCloseStore(hDstStore, CERT_CLOSE_STORE_CHECK_FLAG);
    }
    else
        RTMsgError("Unable to open certificates store: %d", GetLastError());

    /* Release resources */
    CertFreeCertificateContext(pSrcCtx);

    return fRc;
}