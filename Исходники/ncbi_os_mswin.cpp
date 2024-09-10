bool CWinSecurity::GetObjectOwner(HANDLE         obj_handle,
                                  SE_OBJECT_TYPE obj_type,
                                  string* owner, string* group,
                                  unsigned int* uid, unsigned int* gid)
{
    PSID sid_owner;
    PSID sid_group;
    PSECURITY_DESCRIPTOR sd;

    DWORD res = GetSecurityInfo(obj_handle, obj_type, ACCOUNT_SECURITY_INFO,
                                &sid_owner, &sid_group, NULL, NULL, &sd );
    if ( res != ERROR_SUCCESS ) {
        CNcbiError::SetWindowsError(res);
        return false;
    }
    bool retval = s_GetOwnerGroupFromSIDs(sid_owner, sid_group, owner, group, uid, gid);
    LocalFree(sd);
    return retval;
}