/*---------------------------------------------------------------------------*\
 * NAME: CreateNewSD 
 * --------------------------------------------------------------------------*
 * DESCRIPTION: Creates a new security descriptor.
\*---------------------------------------------------------------------------*/
DWORD CreateNewSD (
    SECURITY_DESCRIPTOR **ppSecurityDesc
    )
{
    PACL    pAcl          = NULL;
    DWORD   cbSid         = 0;
    PSID    pSid          = NULL;
    PSID    psidGroup     = NULL;
    PSID    psidOwner     = NULL;
    DWORD   dwReturnValue = ERROR_SUCCESS;
    SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;

    if(!ppSecurityDesc) return ERROR_BAD_ARGUMENTS;
    
    *ppSecurityDesc = NULL;

    //Create a SID for the owner (BUILTIN\Administrators)
    if ( ! AllocateAndInitializeSid ( &SystemSidAuthority, 2, 
            SECURITY_BUILTIN_DOMAIN_RID, 
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0, &pSid) )
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }
    
    cbSid = GetLengthSid (pSid);

    *ppSecurityDesc = (SECURITY_DESCRIPTOR *) malloc (
         sizeof (ACL) +  (2 * cbSid) + sizeof (SECURITY_DESCRIPTOR));

    if(!*ppSecurityDesc)
    {
        dwReturnValue = ERROR_OUTOFMEMORY;
        goto CLEANUP;
    }

    psidGroup = (SID *) (*ppSecurityDesc + 1);
    psidOwner = (SID *) (((BYTE *) psidGroup) + cbSid);
    pAcl = (ACL *) (((BYTE *) psidOwner) + cbSid);

    if (!InitializeSecurityDescriptor (*ppSecurityDesc, SECURITY_DESCRIPTOR_REVISION))
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }

    if (!InitializeAcl (pAcl,
                        sizeof (ACL)+sizeof (ACCESS_ALLOWED_ACE)+cbSid,
                        ACL_REVISION2))
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }

    if (!SetSecurityDescriptorDacl (*ppSecurityDesc, TRUE, pAcl, FALSE))
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }

    memcpy (psidGroup, pSid, cbSid);
    if (!SetSecurityDescriptorGroup (*ppSecurityDesc, psidGroup, FALSE))
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }

    memcpy (psidOwner, pSid, cbSid);
    if (!SetSecurityDescriptorOwner (*ppSecurityDesc, psidOwner, FALSE))
    {
        dwReturnValue = GetLastError();
        goto CLEANUP;
    }

CLEANUP:

    if(dwReturnValue != ERROR_SUCCESS)
    {
        if(*ppSecurityDesc) free (*ppSecurityDesc);
    }

    if(pSid) FreeSid(pSid);

    return dwReturnValue;
}