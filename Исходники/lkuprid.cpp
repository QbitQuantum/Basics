BOOL
LookupUserGroupFromRid(
    LPWSTR TargetComputer,
    DWORD Rid,
    LPWSTR Name,
    PDWORD cchName
    )
{
    PUSER_MODALS_INFO_2 umi2;
    NET_API_STATUS nas;

    UCHAR SubAuthorityCount;
    PSID pSid;
    SID_NAME_USE snu;

    WCHAR DomainName[DNLEN+1];
    DWORD cchDomainName = DNLEN;
    BOOL bSuccess = FALSE; // assume failure

    //
    // get the account domain Sid on the target machine
    // note: if you were looking up multiple sids based on the same
    // account domain, only need to call this once.
    //

    nas = NetUserModalsGet(TargetComputer, 2, (LPBYTE *)&umi2);

    if(nas != NERR_Success) {
        SetLastError(nas);
        return FALSE;
    }

    SubAuthorityCount = *GetSidSubAuthorityCount
                        (umi2->usrmod2_domain_id);

    //
    // allocate storage for new Sid. account domain Sid + account Rid
    //

    pSid = (PSID)HeapAlloc(GetProcessHeap(), 0,
            GetSidLengthRequired((UCHAR)(SubAuthorityCount + 1)));

    if(pSid != NULL) {

        if(InitializeSid(
                pSid,
                GetSidIdentifierAuthority(umi2->usrmod2_domain_id),
                (BYTE)(SubAuthorityCount+1)
                )) {

            DWORD SubAuthIndex = 0;

            //
            // copy existing subauthorities from account domain Sid into
            // new Sid
            //

            for( ; SubAuthIndex < SubAuthorityCount ; SubAuthIndex++) {
                *GetSidSubAuthority(pSid, SubAuthIndex) =
                *GetSidSubAuthority(umi2->usrmod2_domain_id,
                                    SubAuthIndex);
            }

            //
            // append Rid to new Sid
            //

            *GetSidSubAuthority(pSid, SubAuthorityCount) = Rid;

            bSuccess = LookupAccountSidW(
                    TargetComputer,
                    pSid,
                    Name,
                    cchName,
                    DomainName,
                    &cchDomainName,
                    &snu
                    );
        }

        HeapFree(GetProcessHeap(), 0, pSid);
    }

    NetApiBufferFree(umi2);

    return bSuccess;
}