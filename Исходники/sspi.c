SECURITY_STATUS
WINAPI
EnumerateSecurityPackagesA(
	PULONG pcPackages,
	PSecPkgInfoA* ppPackageInfo
	)
{
    SECURITY_STATUS ret;
    PSecPkgInfoW info = NULL;

    ret = EnumerateSecurityPackagesW(pcPackages, &info);
    if (ret == SEC_E_OK && *pcPackages && info)
    {
        /* *ppPackageInfo = thunk_PSecPkgInfoWToA(*pcPackages, info);
        if (*pcPackages && !*ppPackageInfo)
        {
            *pcPackages = 0;
            ret = SEC_E_INSUFFICIENT_MEMORY;
        } */
        FreeContextBuffer(info);
    }
    *ppPackageInfo = NULL;
	UNIMPLEMENTED;

    return ret;
}