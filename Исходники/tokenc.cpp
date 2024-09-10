BOOL AcquireCreds()
{
    SECURITY_STATUS   ss;
    TimeStamp         Lifetime;
    PSecPkgInfo       pkgInfo;

    //  Set the default package to negotiate.
    tstrcpy_s(g_lpPackageName, 1024, TEXT("Negotiate"));

    // Initialize the security package.
    ss = QuerySecurityPackageInfo(g_lpPackageName, &pkgInfo);

    // get the max token size
    g_cbMaxMessage = pkgInfo->cbMaxToken;
    FreeContextBuffer(pkgInfo);

    // set the max token sizes
    g_pInBuf = (PBYTE)malloc(g_cbMaxMessage);
    g_pOutBuf = (PBYTE)malloc(g_cbMaxMessage);

    // get the security handles
    ss = AcquireCredentialsHandle(
        NULL,
        g_lpPackageName,
        SECPKG_CRED_INBOUND,
        NULL,
        NULL,
        NULL,
        NULL,
        &hcred,
        &Lifetime);

    if (!SEC_SUCCESS(ss))
    {
        fprintf(stderr, "AcquireCreds failed: 0x%08x\n", ss);
        return(FALSE);
    }

    return (TRUE);
}