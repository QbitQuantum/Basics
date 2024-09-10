static int
TestplatformChmod(
    const char *nativePath,
    int pmode)
{
    static const SECURITY_INFORMATION infoBits = OWNER_SECURITY_INFORMATION
	    | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
    static const DWORD readOnlyMask = FILE_DELETE_CHILD | FILE_ADD_FILE
	    | FILE_ADD_SUBDIRECTORY | FILE_WRITE_EA | FILE_APPEND_DATA
	    | FILE_WRITE_DATA | DELETE;

    /*
     * References to security functions (only available on NT and later).
     */

    const BOOL set_readOnly = !(pmode & 0222);
    BOOL acl_readOnly_found = FALSE, curAclPresent, curAclDefaulted;
    SID_IDENTIFIER_AUTHORITY userSidAuthority = {
	SECURITY_WORLD_SID_AUTHORITY
    };
    BYTE *secDesc = 0;
    DWORD secDescLen, attr, newAclSize;
    ACL_SIZE_INFORMATION ACLSize;
    PACL curAcl, newAcl = 0;
    WORD j;
    SID *userSid = 0;
    char *userDomain = 0;
    int res = 0;

    /*
     * Process the chmod request.
     */

    attr = GetFileAttributesA(nativePath);

    /*
     * nativePath not found
     */

    if (attr == 0xffffffff) {
	res = -1;
	goto done;
    }

    /*
     * If nativePath is not a directory, there is no special handling.
     */

    if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
	goto done;
    }

    /*
     * Set the result to error, if the ACL change is successful it will be
     * reset to 0.
     */

    res = -1;

    /*
     * Read the security descriptor for the directory. Note the first call
     * obtains the size of the security descriptor.
     */

    if (!GetFileSecurityA(nativePath, infoBits, NULL, 0, &secDescLen)) {
	DWORD secDescLen2 = 0;

	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
	    goto done;
	}

	secDesc = (BYTE *) ckalloc(secDescLen);
	if (!GetFileSecurityA(nativePath, infoBits,
		(PSECURITY_DESCRIPTOR) secDesc, secDescLen, &secDescLen2)
		|| (secDescLen < secDescLen2)) {
	    goto done;
	}
    }

    /*
     * Get the World SID.
     */

    userSid = (SID *) ckalloc(GetSidLengthRequired((UCHAR) 1));
    InitializeSid(userSid, &userSidAuthority, (BYTE) 1);
    *(GetSidSubAuthority(userSid, 0)) = SECURITY_WORLD_RID;

    /*
     * If curAclPresent == false then curAcl and curAclDefaulted not valid.
     */

    if (!GetSecurityDescriptorDacl((PSECURITY_DESCRIPTOR) secDesc,
	    &curAclPresent, &curAcl, &curAclDefaulted)) {
	goto done;
    }
    if (!curAclPresent || !curAcl) {
	ACLSize.AclBytesInUse = 0;
	ACLSize.AceCount = 0;
    } else if (!GetAclInformation(curAcl, &ACLSize, sizeof(ACLSize),
	    AclSizeInformation)) {
	goto done;
    }

    /*
     * Allocate memory for the new ACL.
     */

    newAclSize = ACLSize.AclBytesInUse + sizeof(ACCESS_DENIED_ACE)
	    + GetLengthSid(userSid) - sizeof(DWORD);
    newAcl = (ACL *) ckalloc(newAclSize);

    /*
     * Initialize the new ACL.
     */

    if (!InitializeAcl(newAcl, newAclSize, ACL_REVISION)) {
	goto done;
    }

    /*
     * Add denied to make readonly, this will be known as a "read-only tag".
     */

    if (set_readOnly && !AddAccessDeniedAce(newAcl, ACL_REVISION,
	    readOnlyMask, userSid)) {
	goto done;
    }

    acl_readOnly_found = FALSE;
    for (j = 0; j < ACLSize.AceCount; j++) {
	LPVOID pACE2;
	ACE_HEADER *phACE2;

	if (!GetAce(curAcl, j, &pACE2)) {
	    goto done;
	}

	phACE2 = (ACE_HEADER *) pACE2;

	/*
	 * Do NOT propagate inherited ACEs.
	 */

	if (phACE2->AceFlags & INHERITED_ACE) {
	    continue;
	}

	/*
	 * Skip the "read-only tag" restriction (either added above, or it is
	 * being removed).
	 */

	if (phACE2->AceType == ACCESS_DENIED_ACE_TYPE) {
	    ACCESS_DENIED_ACE *pACEd = (ACCESS_DENIED_ACE *) phACE2;

	    if (pACEd->Mask == readOnlyMask
		    && EqualSid(userSid, (PSID) &pACEd->SidStart)) {
		acl_readOnly_found = TRUE;
		continue;
	    }
	}

	/*
	 * Copy the current ACE from the old to the new ACL.
	 */

	if (!AddAce(newAcl, ACL_REVISION, MAXDWORD, (PACL *) pACE2,
		((PACE_HEADER) pACE2)->AceSize)) {
	    goto done;
	}
    }

    /*
     * Apply the new ACL.
     */

    if (set_readOnly == acl_readOnly_found || SetNamedSecurityInfoA(
	    (LPSTR) nativePath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION,
	    NULL, NULL, newAcl, NULL) == ERROR_SUCCESS) {
	res = 0;
    }

  done:
    if (secDesc) {
	ckfree((char *) secDesc);
    }
    if (newAcl) {
	ckfree((char *) newAcl);
    }
    if (userSid) {
	ckfree((char *) userSid);
    }
    if (userDomain) {
	ckfree((char *) userDomain);
    }

    if (res != 0) {
	return res;
    }

    /*
     * Run normal chmod command.
     */

    return chmod(nativePath, pmode);
}