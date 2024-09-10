int uIsAdmin(sys_call_error_fun fun)
{
#ifdef _WIN32
    /* Open a handle to the access token for the calling process.*/
    BOOL b;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    b = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup);
    if (b)
    {
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &b))
        {
            b = (int)FALSE;
            sys_call_error("CheckTokenMembership");
        }
        FreeSid(AdministratorsGroup);
    }
    else sys_call_error("AllocateAndInitializeSid");

    return (int)b;
#else
    if (geteuid() == 0)
        return 1;
    else
        return 0;
#endif
}