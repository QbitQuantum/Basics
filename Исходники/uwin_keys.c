static SECURITY_ATTRIBUTES* security_attributes(void)
{
	static int			initialized;
	static SECURITY_ATTRIBUTES	asa;
	static int			aclbuf[512];
	static ACL*			acl = (ACL*)&aclbuf[0];
	static SECURITY_DESCRIPTOR	asd;
	static int			sid[SID_BUF_MAX];

	if (initialized < 0)
		return 0;
	if (initialized > 0)
		return &asa;
	initialized = -1;
	CopySid(sizeof(sid), (SID*)sid, &admins_sid_hdr);
	*GetSidSubAuthority((SID*)sid, 1) = DOMAIN_ALIAS_RID_ADMINS;
	InitializeSecurityDescriptor(&asd, SECURITY_DESCRIPTOR_REVISION);
	if (!SetSecurityDescriptorGroup(&asd, (SID*)sid, 0))
		return 0;
	if (!InitializeAcl(acl, sizeof(ACL) + 2 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD)) + GetLengthSid((SID*)sid) + GetLengthSid(&worldsid), ACL_REVISION))
		return 0;
	if (!AddAccessAllowedAce(acl, ACL_REVISION, GENERIC_ALL|READ_CONTROL|WRITE_DAC, (SID*)sid))
		return 0;
	if (!AddAccessAllowedAce(acl, ACL_REVISION, GENERIC_READ, &worldsid))
		return 0;
	if (!SetSecurityDescriptorDacl(&asd, 1, acl, 0))
		return 0;
	asa.nLength = sizeof(asa);
	asa.bInheritHandle = 0;
	asa.lpSecurityDescriptor = &asd;
	initialized = 1;
	return &asa;
}