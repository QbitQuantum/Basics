/*
 * Query specified package for it's maximum token size.
 */
static int getMaxTokenSize(char *package, ULONG * maxTokenSize)
{
    SECURITY_STATUS status;
    SecPkgInfoA *packageSecurityInfo = NULL;

    status = pSFT->QuerySecurityPackageInfoA(package, &packageSecurityInfo);
    if (status == SEC_E_OK) {
        *maxTokenSize = packageSecurityInfo->cbMaxToken;
        if (pSFT->FreeContextBuffer(packageSecurityInfo) != SEC_E_OK) {
            NE_DEBUG(NE_DBG_HTTPAUTH,
                     "sspi: Unable to free security package info.");
        }
    } else {
        NE_DEBUG(NE_DBG_HTTPAUTH,
                 "sspi: QuerySecurityPackageInfo [failed] [%x].", status);
        return -1;
    }

    return 0;
}