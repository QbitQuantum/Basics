/********************************************************************
 AllocateAcl - allocate an acl and populate it with this user and
                 permission information user could be user or domain\user

********************************************************************/
HRESULT AllocateAcl(SCA_SMBP* pssp, PACL* ppACL)
{
    HRESULT hr = S_OK;
    EXPLICIT_ACCESSW* pEA = NULL;
    DWORD cEA = 0;
    DWORD dwCounter = 0;

    PSID psid = NULL;
    LPCWSTR wzUser = NULL;
    DWORD nPermissions = 0;
    DWORD nErrorReturn = 0;
    ACCESS_MODE accessMode = NOT_USED_ACCESS;

    cEA = pssp->dwUserPermissionCount + 1;
    if (cEA >= MAXSIZE_T / sizeof(EXPLICIT_ACCESSW))
    {
        ExitOnFailure1(hr = E_OUTOFMEMORY, "Too many user permissions to allocate: %u", cEA);
    }

    pEA = static_cast<EXPLICIT_ACCESSW*>(MemAlloc(cEA * sizeof(EXPLICIT_ACCESSW), TRUE));
    ExitOnNull(pEA, hr, E_OUTOFMEMORY, "failed to allocate memory for explicit access structure");

    // figure out how big the psid is
    for (dwCounter = 0; dwCounter < pssp->dwUserPermissionCount; ++dwCounter)
    {
        wzUser = pssp->pUserPerms[dwCounter].wzUser;
        nPermissions = pssp->pUserPerms[dwCounter].nPermissions;
        accessMode = pssp->pUserPerms[dwCounter].accessMode;
        //
        // create the appropriate SID
        //

        // figure out the right user to put into the access block
        if (0 == lstrcmpW(wzUser, L"Everyone"))
        {
            hr = AclGetWellKnownSid(WinWorldSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"Administrators"))
        {
            hr = AclGetWellKnownSid(WinBuiltinAdministratorsSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"LocalSystem"))
        {
            hr = AclGetWellKnownSid(WinLocalSystemSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"LocalService"))
        {
            hr = AclGetWellKnownSid(WinLocalServiceSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"NetworkService"))
        {
            hr = AclGetWellKnownSid(WinNetworkServiceSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"AuthenticatedUser"))
        {
            hr = AclGetWellKnownSid(WinAuthenticatedUserSid, &psid);
        }
        else if (0 == lstrcmpW(wzUser, L"Guests"))
        {
            hr = AclGetWellKnownSid(WinBuiltinGuestsSid, &psid);
        }
        else if(0 == lstrcmpW(wzUser, L"CREATOR OWNER"))
        {
            hr = AclGetWellKnownSid(WinCreatorOwnerSid, &psid);
        }
        else
        {
            hr = AclGetAccountSid(NULL, wzUser, &psid);
        }
        ExitOnFailure1(hr, "failed to get sid for account: %ls", wzUser);

        // we now have a valid pSid, fill in the EXPLICIT_ACCESS

        /* Permissions options:   (see sca.sdh for defined sdl options)
        #define GENERIC_READ      (0x80000000L)    2147483648
        #define GENERIC_WRITE     (0x40000000L)    1073741824
        #define GENERIC_EXECUTE   (0x20000000L)    536870912
        #define GENERIC_ALL       (0x10000000L)    268435456
        */
        pEA[dwCounter].grfAccessPermissions = nPermissions;
        pEA[dwCounter].grfAccessMode = accessMode;
        pEA[dwCounter].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
#pragma prefast(push)
#pragma prefast(disable:25029)
        ::BuildTrusteeWithSidW(&(pEA[dwCounter].Trustee), psid);
#pragma prefast(pop)
    }

    // create a new ACL that contains the ACE
    *ppACL = NULL;
#pragma prefast(push)
#pragma prefast(disable:25029)
    nErrorReturn = ::SetEntriesInAclW(dwCounter, pEA, NULL, ppACL);
#pragma prefast(pop)
    ExitOnFailure(hr = HRESULT_FROM_WIN32(nErrorReturn), "failed to allocate ACL");

LExit:
    if (psid)
    {
        AclFreeSid(psid);
    }

    ReleaseMem(pEA);

    return hr;
}