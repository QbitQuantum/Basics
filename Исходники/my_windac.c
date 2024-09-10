int my_security_attr_create(SECURITY_ATTRIBUTES **psa, const char **perror,
                            DWORD owner_rights, DWORD everyone_rights)
{
    /* Top-level SID authority */
    SID_IDENTIFIER_AUTHORITY world_auth= SECURITY_WORLD_SID_AUTHORITY;
    PSID everyone_sid= 0;
    HANDLE htoken= 0;
    SECURITY_ATTRIBUTES *sa= 0;
    PACL dacl= 0;
    DWORD owner_token_length, dacl_length;
    SECURITY_DESCRIPTOR *sd;
    PTOKEN_USER owner_token;
    PSID owner_sid;
    My_security_attr *attr;

    if (! is_nt())
    {
        *psa= 0;
        return 0;
    }

    /*
      Get SID of Everyone group. Easier to retrieve all SIDs each time
      this function is called than worry about thread safety.
    */
    if (! AllocateAndInitializeSid(&world_auth, 1, SECURITY_WORLD_RID,
                                   0, 0, 0, 0, 0, 0, 0, &everyone_sid))
    {
        *perror= "Failed to retrieve the SID of Everyone group";
        goto error;
    }

    /*
      Get SID of the owner. Using GetSecurityInfo this task can be done
      in just one call instead of five, but GetSecurityInfo declared in
      aclapi.h, so I hesitate to use it.
      SIC: OpenThreadToken works only if there is an active impersonation
      token, hence OpenProcessToken is used.
    */
    if (! OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &htoken))
    {
        *perror= "Failed to retrieve thread access token";
        goto error;
    }
    GetTokenInformation(htoken, TokenUser, 0, 0, &owner_token_length);

    if (! my_multi_malloc(key_memory_win_SECURITY_ATTRIBUTES,
                          MYF(MY_WME),
                          &sa, ALIGN_SIZE(sizeof(SECURITY_ATTRIBUTES)) +
                          sizeof(My_security_attr),
                          &sd, sizeof(SECURITY_DESCRIPTOR),
                          &owner_token, owner_token_length,
                          0))
    {
        *perror= "Failed to allocate memory for SECURITY_ATTRIBUTES";
        goto error;
    }
    memset(owner_token, 0, owner_token_length);
    if (! GetTokenInformation(htoken, TokenUser, owner_token,
                              owner_token_length, &owner_token_length))
    {
        *perror= "GetTokenInformation failed";
        goto error;
    }
    owner_sid= owner_token->User.Sid;

    if (! IsValidSid(owner_sid))
    {
        *perror= "IsValidSid failed";
        goto error;
    }

    /* Calculate the amount of memory that must be allocated for the DACL */
    dacl_length= sizeof(ACL) + (sizeof(ACCESS_ALLOWED_ACE)-sizeof(DWORD)) * 2 +
                 GetLengthSid(everyone_sid) + GetLengthSid(owner_sid);

    /* Create an ACL */
    if (! (dacl= (PACL) my_malloc(key_memory_win_PACL,
                                  dacl_length, MYF(MY_ZEROFILL|MY_WME))))
    {
        *perror= "Failed to allocate memory for DACL";
        goto error;
    }
    if (! InitializeAcl(dacl, dacl_length, ACL_REVISION))
    {
        *perror= "Failed to initialize DACL";
        goto error;
    }
    if (! AddAccessAllowedAce(dacl, ACL_REVISION, everyone_rights, everyone_sid))
    {
        *perror= "Failed to set up DACL";
        goto error;
    }
    if (! AddAccessAllowedAce(dacl, ACL_REVISION, owner_rights, owner_sid))
    {
        *perror= "Failed to set up DACL";
        goto error;
    }
    if (! InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION))
    {
        *perror= "Could not initialize security descriptor";
        goto error;
    }
    if (! SetSecurityDescriptorDacl(sd, TRUE, dacl, FALSE))
    {
        *perror= "Failed to install DACL";
        goto error;
    }

    sa->nLength= sizeof(*sa);
    sa->bInheritHandle= TRUE;
    sa->lpSecurityDescriptor= sd;
    /* Save pointers to everyone_sid and dacl to be able to clean them up */
    attr= (My_security_attr*) (((char*) sa) + ALIGN_SIZE(sizeof(*sa)));
    attr->everyone_sid= everyone_sid;
    attr->dacl= dacl;
    *psa= sa;

    CloseHandle(htoken);
    return 0;
error:
    if (everyone_sid)
        FreeSid(everyone_sid);
    if (htoken)
        CloseHandle(htoken);
    my_free(sa);
    my_free(dacl);
    *psa= 0;
    return 1;
}