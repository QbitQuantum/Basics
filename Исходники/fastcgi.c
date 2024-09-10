/* Do some black magic with the NT security API.
 * We prepare a DACL (Discretionary Access Control List) so that
 * we, the creator, are allowed all access, while "Everyone Else"
 * is only allowed to read and write to the pipe.
 * This avoids security issues on shared hosts where a luser messes
 * with the lower-level pipe settings and screws up the FastCGI service.
 */
static PACL prepare_named_pipe_acl(PSECURITY_DESCRIPTOR sd, LPSECURITY_ATTRIBUTES sa)
{
	DWORD req_acl_size;
	char everyone_buf[32], owner_buf[32];
	PSID sid_everyone, sid_owner;
	SID_IDENTIFIER_AUTHORITY
			siaWorld = SECURITY_WORLD_SID_AUTHORITY,
			siaCreator = SECURITY_CREATOR_SID_AUTHORITY;
	PACL acl;

	sid_everyone = (PSID)&everyone_buf;
	sid_owner = (PSID)&owner_buf;

	req_acl_size = sizeof(ACL) +
		(2 * ((sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD)) + GetSidLengthRequired(1)));

	acl = malloc(req_acl_size);

	if (acl == NULL) {
		return NULL;
	}

	if (!InitializeSid(sid_everyone, &siaWorld, 1)) {
		goto out_fail;
	}
	*GetSidSubAuthority(sid_everyone, 0) = SECURITY_WORLD_RID;

	if (!InitializeSid(sid_owner, &siaCreator, 1)) {
		goto out_fail;
	}
	*GetSidSubAuthority(sid_owner, 0) = SECURITY_CREATOR_OWNER_RID;

	if (!InitializeAcl(acl, req_acl_size, ACL_REVISION)) {
		goto out_fail;
	}

	if (!AddAccessAllowedAce(acl, ACL_REVISION, FILE_GENERIC_READ | FILE_GENERIC_WRITE, sid_everyone)) {
		goto out_fail;
	}

	if (!AddAccessAllowedAce(acl, ACL_REVISION, FILE_ALL_ACCESS, sid_owner)) {
		goto out_fail;
	}

	if (!InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION)) {
		goto out_fail;
	}

	if (!SetSecurityDescriptorDacl(sd, TRUE, acl, FALSE)) {
		goto out_fail;
	}

	sa->lpSecurityDescriptor = sd;

	return acl;

out_fail:
	free(acl);
	return NULL;
}