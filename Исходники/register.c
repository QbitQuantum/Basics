/***************************************************************************
 *              WINTRUST_RegisterHttpsProv
 *
 * Register HTTPSPROV_ACTION actions and usages.
 *
 * NOTES
 *   HTTPSPROV_ACTION ({573E31F8-AABA-11D0-8CCB-00C04FC295EE})
 *   is defined in softpub.h
 */
static BOOL WINTRUST_RegisterHttpsProv(void)
{
    BOOL RegisteredOK = TRUE;
    static CHAR SoftpubLoadUsage[] = "SoftpubLoadDefUsageCallData";
    static CHAR SoftpubFreeUsage[] = "SoftpubFreeDefUsageCallData";
    static GUID ProvGUID = HTTPSPROV_ACTION;
    CRYPT_REGISTER_ACTIONID ProvInfo;
    CRYPT_PROVIDER_REGDEFUSAGE DefUsage = { sizeof(CRYPT_PROVIDER_REGDEFUSAGE),
                                            &ProvGUID,
                                            NULL, /* Will be filled later */
                                            SoftpubLoadUsage,
                                            SoftpubFreeUsage };

    ProvInfo.cbStruct                   = sizeof(CRYPT_REGISTER_ACTIONID);
    ProvInfo.sInitProvider              = SoftpubInitialization;
    ProvInfo.sObjectProvider            = SoftpubMessage;
    ProvInfo.sSignatureProvider         = SoftpubSignature;
    ProvInfo.sCertificateProvider       = HTTPSCertificateTrust;
    ProvInfo.sCertificatePolicyProvider = SoftpubCertCheck;
    ProvInfo.sFinalPolicyProvider       = HTTPSFinalProv;
    ProvInfo.sTestPolicyProvider        = NullCTRE; /* No diagnostic policy */
    ProvInfo.sCleanupProvider           = SoftpubCleanup;

    DefUsage.pwszDllName = WINTRUST_Alloc(sizeof(SP_POLICY_PROVIDER_DLL_NAME));
    lstrcpyW(DefUsage.pwszDllName, SP_POLICY_PROVIDER_DLL_NAME);

    if (!WintrustAddDefaultForUsage(szOID_PKIX_KP_SERVER_AUTH, &DefUsage))
        RegisteredOK = FALSE;
    if (!WintrustAddDefaultForUsage(szOID_PKIX_KP_CLIENT_AUTH, &DefUsage))
        RegisteredOK = FALSE;
    if (!WintrustAddDefaultForUsage(szOID_SERVER_GATED_CRYPTO, &DefUsage))
        RegisteredOK = FALSE;
    if (!WintrustAddDefaultForUsage(szOID_SGC_NETSCAPE, &DefUsage))
        RegisteredOK = FALSE;

    WINTRUST_Free(DefUsage.pwszDllName);

    if (!WintrustAddActionID(&ProvGUID, 0, &ProvInfo))
        RegisteredOK = FALSE;

    return RegisteredOK;
}