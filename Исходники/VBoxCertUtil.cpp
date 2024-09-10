/**
 * Removes a certificate, given by file, from a store
 *
 * @returns true on success, false on failure (error message written).
 * @param   dwDst           The destination, like
 *                          CERT_SYSTEM_STORE_LOCAL_MACHINE or
 *                          ERT_SYSTEM_STORE_CURRENT_USER.
 * @param   pszStoreNm      The store name.
 * @param   pszCertFile     The file containing the certificate to add.
 */
static bool removeCertFromStoreByFile(DWORD dwDst, const char *pszStoreNm, const char *pszCertFile)
{
    /*
     * Read the certificate file first.
     */
    PCCERT_CONTEXT  pSrcCtx   = NULL;
    HCERTSTORE      hSrcStore = NULL;
    if (!readCertFile(pszCertFile, &pSrcCtx, &hSrcStore))
        return false;

    WCHAR wszName[1024];
    if (!CertGetNameStringW(pSrcCtx, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0 /*dwFlags*/, NULL /*pvTypePara*/,
                            wszName, sizeof(wszName)))
    {
        RTMsgError("CertGetNameStringW(Subject) failed: %s\n", errorToString(GetLastError()));
        wszName[0] = '\0';
    }

    /*
     * Open the destination store.
     */
    bool fRc = false;
    HCERTSTORE hDstStore = openCertStore(dwDst, pszStoreNm);
    if (hDstStore)
    {
        if (pSrcCtx)
        {
            fRc = true;
            unsigned        cDeleted = 0;
            PCCERT_CONTEXT  pCurCtx  = NULL;
            while ((pCurCtx = CertEnumCertificatesInStore(hDstStore, pCurCtx)) != NULL)
            {
                if (CertCompareCertificate(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, pCurCtx->pCertInfo, pSrcCtx->pCertInfo))
                {
                    if (g_cVerbosityLevel > 1)
                        RTMsgInfo("Removing '%ls'...", wszName);
                    PCCERT_CONTEXT pDeleteCtx = CertDuplicateCertificateContext(pCurCtx);
                    if (pDeleteCtx)
                    {
                        if (CertDeleteCertificateFromStore(pDeleteCtx))
                            cDeleted++;
                        else
                            RTMsgError("CertDeleteFromStore('%ls') failed: %s\n", wszName, errorToString(GetLastError()));
                    }
                    else
                        RTMsgError("CertDuplicateCertificateContext('%ls') failed: %s\n", wszName, errorToString(GetLastError()));
                }
            }

            if (!cDeleted)
                RTMsgInfo("Found no matching certificates to remove.");
        }
        else
        {
            RTMsgError("Path not implemented at line %d\n",  __LINE__);
        }

        CertCloseStore(hDstStore, CERT_CLOSE_STORE_CHECK_FLAG);
    }
    if (pSrcCtx)
        CertFreeCertificateContext(pSrcCtx);
    if (hSrcStore)
        CertCloseStore(hSrcStore, CERT_CLOSE_STORE_CHECK_FLAG);
    return fRc;
}