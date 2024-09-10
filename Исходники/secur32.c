static void test_kerberos(void)
{
    SecPkgInfoA *info;
    TimeStamp ttl;
    CredHandle cred;
    SECURITY_STATUS status;

    SEC_CHAR provider[] = {'K','e','r','b','e','r','o','s',0};

    static const ULONG expected_flags =
          SECPKG_FLAG_INTEGRITY
        | SECPKG_FLAG_PRIVACY
        | SECPKG_FLAG_TOKEN_ONLY
        | SECPKG_FLAG_DATAGRAM
        | SECPKG_FLAG_CONNECTION
        | SECPKG_FLAG_MULTI_REQUIRED
        | SECPKG_FLAG_EXTENDED_ERROR
        | SECPKG_FLAG_IMPERSONATION
        | SECPKG_FLAG_ACCEPT_WIN32_NAME
        | SECPKG_FLAG_NEGOTIABLE
        | SECPKG_FLAG_GSS_COMPATIBLE
        | SECPKG_FLAG_LOGON
        | SECPKG_FLAG_MUTUAL_AUTH
        | SECPKG_FLAG_DELEGATION
        | SECPKG_FLAG_READONLY_WITH_CHECKSUM;
    static const ULONG optional_mask =
          SECPKG_FLAG_RESTRICTED_TOKENS
        | SECPKG_FLAG_APPCONTAINER_CHECKS;

    status = QuerySecurityPackageInfoA(provider, &info);
    ok(status == SEC_E_OK, "Kerberos package not installed, skipping test\n");
    if(status != SEC_E_OK)
        return;

    ok( (info->fCapabilities & ~optional_mask) == expected_flags, "got %08x, expected %08x\n", info->fCapabilities, expected_flags );
    ok( info->wVersion == 1, "got %u\n", info->wVersion );
    ok( info->wRPCID == RPC_C_AUTHN_GSS_KERBEROS, "got %u\n", info->wRPCID );
    ok( info->cbMaxToken >= 12000, "got %u\n", info->cbMaxToken );
    ok( !lstrcmpA( info->Name, "Kerberos" ), "got %s\n", info->Name );
    ok( !lstrcmpA( info->Comment, "Microsoft Kerberos V1.0" ), "got %s\n", info->Comment );
    FreeContextBuffer( info );

    status = AcquireCredentialsHandleA( NULL, provider, SECPKG_CRED_OUTBOUND, NULL,
                                        NULL, NULL, NULL, &cred, &ttl );
    todo_wine ok( status == SEC_E_OK, "AcquireCredentialsHandleA returned %08x\n", status );
    if(status == SEC_E_OK)
        FreeCredentialHandle( &cred );
}