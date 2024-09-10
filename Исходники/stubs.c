SECURITY_STATUS SEC_ENTRY
EnumerateSecurityPackagesW(
    unsigned long SEC_FAR *     pcPackages,         // Receives num. packages
    PSecPkgInfoW SEC_FAR *      ppPackageInfo       // Receives array of info
    )
{
    SECURITY_STATUS SecStatus;

    SecStatus = QuerySecurityPackageInfoW(
                    PACKAGE_NAME,
                    ppPackageInfo
                    );
    if (SecStatus == SEC_E_OK)
    {
        *pcPackages = 1;
    }

    return(SecStatus);
}