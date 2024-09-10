int
secure_file2(char *path, char *user, ACCESS_MASK mask, char *user2, ACCESS_MASK mask2)
{
	SECURITY_DESCRIPTOR	sd;
	SID	*usid = NULL;
	SID	*gsid;
	ACL	*pdacl;
	struct  stat sbuf;
	SECURITY_INFORMATION	si = 0;
	char	logb[LOG_BUF_SIZE] = {'\0' } ;
	char	*gname = NULL;

	if (path == NULL)
		return (0);

	if (lstat(path, &sbuf) == -1)
		return (0);	/* ignore non-existent files! */

	if (!has_privilege(SE_RESTORE_NAME))
		ena_privilege(SE_RESTORE_NAME);

	if (!has_privilege(SE_TAKE_OWNERSHIP_NAME))
		ena_privilege(SE_TAKE_OWNERSHIP_NAME);

	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);

	/* make PBS service account as the owner */
	usid = create_administrators_sid();

	if (usid == NULL)
		usid = getusersid(getlogin());

	if (usid) {
		if (SetSecurityDescriptorOwner(&sd, usid, FALSE) == 0) {
			sprintf(logb, "error setting owner for file %s", path);
			log_err(-1, "secure_file2", logb);
			LocalFree(usid);
			return (0);
		}
		si |= OWNER_SECURITY_INFORMATION;

		/* trick with setting perms, set ownership first! */
		if (SetFileSecurity(path, si, &sd) == 0) {
			sprintf(logb, "error setting actual owner for file %s", path);
			log_err(-1, "secure_file2", logb);
			LocalFree(usid);
			return (0);
		}

		InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
		si = 0;
	}

	/* can't use gsid=getgid() since gsid here must be LocalFree()d */
	if ((gname=getdefgrpname(getlogin()))) {
		gsid = getgrpsid(gname);
		(void)free(gname);
	} else {
		gsid = NULL;
	}
	if (gsid) {
		if (SetSecurityDescriptorGroup(&sd, gsid, FALSE) == 0) {
			sprintf(logb, "error setting group for file %s", path);
			log_err(-1, "secure_file2", logb);
			if (usid) LocalFree(usid);
			LocalFree(gsid);
			return (0);
		}
		si |= GROUP_SECURITY_INFORMATION;

	}

	pdacl = create_secure_dacl2(user, mask, user2, mask2, usid);
	if (pdacl == NULL) {
		sprintf(logb, "failed to create secure dacl for file %s", path);
		log_err(-1, "secure_file2", logb);
		if (usid) LocalFree(usid);
		if (gsid) LocalFree(gsid);
		return (0);
	}

	if (SetSecurityDescriptorDacl(&sd, TRUE, pdacl, TRUE) == 0) {
		sprintf(logb, "error setting dacl for file %s", path);
		log_err(-1, "secure_file2", logb);
		if (usid) LocalFree(usid);
		if (gsid) LocalFree(gsid);
		(void)free(pdacl);
		return (0);
	}
	si |= DACL_SECURITY_INFORMATION;

	if (SetFileSecurity(path, si, &sd) == 0) {
		sprintf(logb, "error setting security for file %s", path);
		log_err(-1, "secure_file2", logb);
		if (usid) LocalFree(usid);
		if (gsid) LocalFree(gsid);
		(void)free(pdacl);
		return (0);
	}

	if (usid) LocalFree(usid);
	if (gsid) LocalFree(gsid);
	(void)free(pdacl);

	/* Even though permissions have been set on the file, it can be   */
	/* overriden if a file attribute was given say a                  */
	/* FILE_ATTRIBUTE_READONLY flag previously outside of PBS. Any    */
	/* writes to the file would still fail even if Administrators     */
	/* have been given write permission.                              */
	/* The following call is to clear any special attributes that     */
	/* may have gotten set outside of PBS, negating PBS' permission   */
	/* change.							  */
	(void)SetFileAttributes(path, FILE_ATTRIBUTE_NORMAL);

	return (1);

}