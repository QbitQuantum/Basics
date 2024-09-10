/*---------------------------------------------------------------------------*\
 * NAME: ListACL                                                             *
 * --------------------------------------------------------------------------*
 * DESCRIPTION: 
\*---------------------------------------------------------------------------*/
void ListACL (
    PACL Acl,
    DWORD dwSDType
    )
{
    ACL_SIZE_INFORMATION     aclSizeInfo                      = {0};
    ACL_REVISION_INFORMATION aclRevInfo                       = {0};
    ULONG                    i;
    LPVOID                   pvAce                            = NULL;
    ACE_HEADER               *pAceHeader                      = NULL;
    ACCESS_ALLOWED_ACE       *pAccessAllowedAce               = NULL;
    ACCESS_DENIED_ACE        *pAccessDeniedAce                = NULL;
    TCHAR                    tszDomainName [SIZE_NAME_BUFFER] = {0};
    TCHAR                    tszUserName [SIZE_NAME_BUFFER]   = {0};
    DWORD                    cchName = 0;
    SID_NAME_USE             snu;

    if (!GetAclInformation (Acl,
                            &aclSizeInfo,
                            sizeof (ACL_SIZE_INFORMATION),
                            AclSizeInformation))
    {
        _tprintf (_T("Could not get AclSizeInformation"));
        return;
    }

    if (!GetAclInformation (Acl,
                            &aclRevInfo,
                            sizeof (ACL_REVISION_INFORMATION),
                            AclRevisionInformation))
    {
        _tprintf (_T("Could not get AclRevisionInformation"));
        return;
    }

    for (i = 0; i < aclSizeInfo.AceCount; i++)
    {
        if (!GetAce (Acl, i, &pvAce))
            return;

        pAceHeader = (ACE_HEADER *) pvAce;

        if (pAceHeader->AceType == ACCESS_ALLOWED_ACE_TYPE)
        {
            pAccessAllowedAce = (ACCESS_ALLOWED_ACE *) pvAce;
            cchName = SIZE_NAME_BUFFER-1;
            LookupAccountSid (NULL,
                              &pAccessAllowedAce->SidStart,
                              tszUserName,
                              &cchName,
                              tszDomainName,
                              &cchName,
                              &snu);


            DisplayAccess(pAccessAllowedAce->Mask, 
                          dwSDType, 
                          _T("permitted"), 
                          tszUserName, 
                          tszDomainName);

        } 
        else if (pAceHeader->AceType == ACCESS_DENIED_ACE_TYPE)
        {
            pAccessDeniedAce = (ACCESS_DENIED_ACE *) pvAce;
            cchName = SIZE_NAME_BUFFER-1;
            LookupAccountSid (NULL,
                              &pAccessDeniedAce->SidStart,
                              tszUserName,
                              &cchName,
                              tszDomainName,
                              &cchName,
                              &snu);

            DisplayAccess(pAccessDeniedAce->Mask, 
                          dwSDType, 
                          _T("denied"), 
                          tszUserName, 
                          tszDomainName);
  
        }
   }
}