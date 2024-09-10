/*
 * Construct a security descriptor whose discretionary access-control
 * list implements the specified mode bits.  The SIDs for owner, group,
 * and everyone are obtained from the global _pr_nt_sids structure.
 * Both the security descriptor and access-control list are returned
 * and should be freed by a _PR_NT_FreeSecurityDescriptorACL call.
 *
 * The accessTable array maps NSPR's read, write, and execute access
 * rights to the corresponding NT access rights for the securable
 * object.
 */
PRStatus
_PR_NT_MakeSecurityDescriptorACL(
    PRIntn mode,
    DWORD accessTable[],
    PSECURITY_DESCRIPTOR *resultSD,
    PACL *resultACL)
{
    PSECURITY_DESCRIPTOR pSD = NULL;
    PACL pACL = NULL;
    DWORD cbACL;  /* size of ACL */
    DWORD accessMask;

    if (_pr_nt_sids.owner == NULL) {
        PR_SetError(PR_NOT_IMPLEMENTED_ERROR, 0);
        return PR_FAILURE;
    }

    pSD = (PSECURITY_DESCRIPTOR) PR_Malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
    if (pSD == NULL) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    if (!SetSecurityDescriptorOwner(pSD, _pr_nt_sids.owner, FALSE)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    if (!SetSecurityDescriptorGroup(pSD, _pr_nt_sids.group, FALSE)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }

    /*
     * Construct a discretionary access-control list with three
     * access-control entries, one each for owner, primary group,
     * and Everyone.
     */

    cbACL = sizeof(ACL)
          + 3 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD))
          + GetLengthSid(_pr_nt_sids.owner)
          + GetLengthSid(_pr_nt_sids.group)
          + GetLengthSid(_pr_nt_sids.everyone);
    pACL = (PACL) PR_Malloc(cbACL);
    if (pACL == NULL) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    if (!InitializeAcl(pACL, cbACL, ACL_REVISION)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    accessMask = 0;
    if (mode & 00400) accessMask |= accessTable[0];
    if (mode & 00200) accessMask |= accessTable[1];
    if (mode & 00100) accessMask |= accessTable[2];
    if (accessMask && !AddAccessAllowedAce(pACL, ACL_REVISION, accessMask,
            _pr_nt_sids.owner)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    accessMask = 0;
    if (mode & 00040) accessMask |= accessTable[0];
    if (mode & 00020) accessMask |= accessTable[1];
    if (mode & 00010) accessMask |= accessTable[2];
    if (accessMask && !AddAccessAllowedAce(pACL, ACL_REVISION, accessMask,
            _pr_nt_sids.group)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }
    accessMask = 0;
    if (mode & 00004) accessMask |= accessTable[0];
    if (mode & 00002) accessMask |= accessTable[1];
    if (mode & 00001) accessMask |= accessTable[2];
    if (accessMask && !AddAccessAllowedAce(pACL, ACL_REVISION, accessMask,
            _pr_nt_sids.everyone)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }

    if (!SetSecurityDescriptorDacl(pSD, TRUE, pACL, FALSE)) {
        _PR_MD_MAP_DEFAULT_ERROR(GetLastError());
        goto failed;
    }

    *resultSD = pSD;
    *resultACL = pACL;
    return PR_SUCCESS;

failed:
    if (pSD) {
        PR_Free(pSD);
    }
    if (pACL) {
        PR_Free(pACL);
    }
    return PR_FAILURE;
}