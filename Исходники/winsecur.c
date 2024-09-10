int make_private_security_descriptor(DWORD permissions,
                                     PSECURITY_DESCRIPTOR *psd,
                                     PACL *acl,
                                     char **error)
{
    SID_IDENTIFIER_AUTHORITY world_auth = SECURITY_WORLD_SID_AUTHORITY;
    SID_IDENTIFIER_AUTHORITY nt_auth = SECURITY_NT_AUTHORITY;
    EXPLICIT_ACCESS ea[3];
    int acl_err;
    int ret = FALSE;

    /* Initialised once, then kept around to reuse forever */
    static PSID worldsid, networksid, usersid;

    *psd = NULL;
    *acl = NULL;
    *error = NULL;

    if (!got_advapi()) {
        *error = dupprintf("unable to load advapi32.dll");
        goto cleanup;
    }

    if (!usersid) {
        if ((usersid = get_user_sid()) == NULL) {
            *error = dupprintf("unable to construct SID for current user: %s",
                               win_strerror(GetLastError()));
            goto cleanup;
        }
    }

    if (!worldsid) {
        if (!AllocateAndInitializeSid(&world_auth, 1, SECURITY_WORLD_RID,
                                      0, 0, 0, 0, 0, 0, 0, &worldsid)) {
            *error = dupprintf("unable to construct SID for world: %s",
                               win_strerror(GetLastError()));
            goto cleanup;
        }
    }

    if (!networksid) {
        if (!AllocateAndInitializeSid(&nt_auth, 1, SECURITY_NETWORK_RID,
                                      0, 0, 0, 0, 0, 0, 0, &networksid)) {
            *error = dupprintf("unable to construct SID for "
                               "local same-user access only: %s",
                               win_strerror(GetLastError()));
            goto cleanup;
        }
    }

    memset(ea, 0, sizeof(ea));
    ea[0].grfAccessPermissions = permissions;
    ea[0].grfAccessMode = REVOKE_ACCESS;
    ea[0].grfInheritance = NO_INHERITANCE;
    ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[0].Trustee.ptstrName = (LPTSTR)worldsid;
    ea[1].grfAccessPermissions = permissions;
    ea[1].grfAccessMode = GRANT_ACCESS;
    ea[1].grfInheritance = NO_INHERITANCE;
    ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[1].Trustee.ptstrName = (LPTSTR)usersid;
    ea[2].grfAccessPermissions = permissions;
    ea[2].grfAccessMode = REVOKE_ACCESS;
    ea[2].grfInheritance = NO_INHERITANCE;
    ea[2].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[2].Trustee.ptstrName = (LPTSTR)networksid;

    acl_err = p_SetEntriesInAclA(3, ea, NULL, acl);
    if (acl_err != ERROR_SUCCESS || *acl == NULL) {
        *error = dupprintf("unable to construct ACL: %s",
                           win_strerror(acl_err));
        goto cleanup;
    }

    *psd = (PSECURITY_DESCRIPTOR)
        LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
    if (!*psd) {
        *error = dupprintf("unable to allocate security descriptor: %s",
                           win_strerror(GetLastError()));
        goto cleanup;
    }

    if (!InitializeSecurityDescriptor(*psd, SECURITY_DESCRIPTOR_REVISION)) {
        *error = dupprintf("unable to initialise security descriptor: %s",
                           win_strerror(GetLastError()));
        goto cleanup;
    }

    if (!SetSecurityDescriptorDacl(*psd, TRUE, *acl, FALSE)) {
        *error = dupprintf("unable to set DACL in security descriptor: %s",
                           win_strerror(GetLastError()));
        goto cleanup;
    }

    ret = TRUE;

  cleanup:
    if (!ret) {
        if (*psd) {
            LocalFree(*psd);
            *psd = NULL;
        }
        if (*acl) {
            LocalFree(*acl);
            *acl = NULL;
        }
    } else {
        sfree(*error);
        *error = NULL;
    }
    return ret;
}