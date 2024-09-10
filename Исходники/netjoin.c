int
_cdecl
main(
    int argc,
    char *argv[]
    )
{
    NTSTATUS NtStatus;

    HKEY hKey;

    WCHAR UnicodeDomainName[ 32 ];
    WCHAR UnicodePassword[ 32 ];
    DWORD cbUnicodePassword = sizeof( UnicodePassword );
    DWORD cbUnicodeDomainName = sizeof( UnicodeDomainName );

    DWORD dwType;
    DWORD rc;

    ACCESS_MASK         DesiredAccess;
    LSA_HANDLE          PolicyHandle = NULL;

    PPOLICY_PRIMARY_DOMAIN_INFO PrimaryDomainInfo = NULL;

    LSA_ENUMERATION_HANDLE      TrustEnumContext = 0;
    PLSA_TRUST_INFORMATION      TrustEnumBuffer = NULL;
    DWORD                       TrustEnumCount = 0;

    //
    // Get computer name as the password to use.
    //

    if (!GetComputerNameW( UnicodePassword, &cbUnicodePassword )) {
        fprintf( stderr, "NETJOIN: Unable to read computer name from registry - %u\n", GetLastError() );
        exit( 1 );
        }

    if ((rc = RegOpenKeyW( HKEY_LOCAL_MACHINE,
                           L"System\\CurrentControlSet\\Services\\LanmanWorkstation\\Parameters",
                           &hKey
                         )
        ) ||
        (rc = RegQueryValueExW( hKey,
                                L"Domain",
                                NULL,
                                &dwType,
                                (LPBYTE)UnicodeDomainName,
                                &cbUnicodeDomainName
                              )
        )
       ) {
        fprintf( stderr, "NETJOIN: Unable to read domain name from registry - %u\n", rc );
        exit( 1 );
        }

    DesiredAccess = POLICY_VIEW_LOCAL_INFORMATION |
                        // needed to read domain info and trusted account info
                    POLICY_TRUST_ADMIN |
                        // needed to add and delete trust accounts
                    POLICY_CREATE_SECRET ;
                        // needed to add and delete secret

    NtStatus = OpenAndVerifyLSA( &PolicyHandle,
                                 DesiredAccess,
                                 UnicodeDomainName,
                                 &PrimaryDomainInfo
                               );

    if (!NT_SUCCESS( NtStatus )) {
        fprintf( stderr, "NETJOIN: Unable to read domain name from registry - %u\n", GetLastError() );
        exit( 1 );
        }

    //
    // now the domain names match and the PrimaryDomainInfo has the SID of the
    // domain, we can add trust entry and secret in LSA for this domain.
    // Before adding this, clean up old entries.
    //

    for(;;) {

        DWORD i;
        PLSA_TRUST_INFORMATION  TrustedDomainAccount;

        NtStatus = LsaEnumerateTrustedDomains( PolicyHandle,
                                               &TrustEnumContext,
                                               (PVOID *)&TrustEnumBuffer,
                                               TRUST_ENUM_PERF_BUF_SIZE,
                                               &TrustEnumCount
                                             );

        if (NtStatus == STATUS_NO_MORE_ENTRIES) {

            //
            // we are done
            //

            break;
            }

        if (NtStatus != STATUS_MORE_ENTRIES) {
            if (!NT_SUCCESS( NtStatus )) {
                FailureMessage( "LsaEnumerateTrustedDomains", NtStatus );
                goto Cleanup;
                }
            }

        //
        // delete trusted accounts and the corresponding secrets
        //

        for( i = 0, TrustedDomainAccount = TrustEnumBuffer;
                    i < TrustEnumCount;
                        TrustedDomainAccount++, i++ ) {

            NtStatus = DeleteATrustedDomain( PolicyHandle,
                                             TrustedDomainAccount
                                           );

            if (!NT_SUCCESS( NtStatus )) {
                FailureMessage( "DeleteATrustedDomain", NtStatus );
                goto Cleanup;
                }
            }

        if (NtStatus != STATUS_MORE_ENTRIES) {

            //
            // we have cleaned up all old entries.
            //

            break;
            }

        //
        // free up used enum buffer
        //

        if (TrustEnumBuffer != NULL) {
            LsaFreeMemory( TrustEnumBuffer );
            TrustEnumBuffer = NULL;
            }
        }

    //
    // add a new trust for the specified domain
    //

    NtStatus = AddATrustedDomain( PolicyHandle,
                                  (PLSA_TRUST_INFORMATION) PrimaryDomainInfo,
                                  UnicodePassword
                                );
    if (!NT_SUCCESS( NtStatus )) {
        FailureMessage( "AddATrustedDomain", NtStatus );
        }
    else {
        //
        // Give LSA a chance to do its thing.
        //

        Sleep( 10000 );
        }

Cleanup:

    if (PrimaryDomainInfo != NULL) {
        LsaFreeMemory( PrimaryDomainInfo );
        }

    if (TrustEnumBuffer != NULL) {
        LsaFreeMemory( TrustEnumBuffer );
        }

    if (PolicyHandle != NULL) {
        LsaClose( PolicyHandle );
        }

    if (NT_SUCCESS( NtStatus )) {
        fprintf( stderr,
                 "NETJOIN: Computer == '%ws' joined the '%ws' domain.\n",
                 UnicodePassword,
                 UnicodeDomainName
               );
        return 0;
        }
    else {
        fprintf( stderr,
                 "NETJOIN: Computer == '%ws' unable to join the '%ws' domain - Status == %08x\n",
                 UnicodePassword,
                 UnicodeDomainName,
                 NtStatus
               );
        return 1;
        }
}