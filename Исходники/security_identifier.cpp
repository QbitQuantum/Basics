CL_SecurityIdentifier CL_SecurityIdentifier::get_thread_group()
{
#ifdef WIN32
	PSID pSid = 0;
	PSECURITY_DESCRIPTOR securityDescriptor = 0;
	DWORD result = GetSecurityInfo(
		GetCurrentThread(),
		SE_KERNEL_OBJECT,
		GROUP_SECURITY_INFORMATION,
		0,
		&pSid,
		0,
		0,
		&securityDescriptor);
	if (result != ERROR_SUCCESS)
		throw CL_Exception("Unable to get thread user SID");

	CL_SecurityIdentifier identifier(pSid);
	LocalFree(securityDescriptor);
	return identifier;
#else
	return CL_SecurityIdentifier(getgid(), type_group);
#endif
}