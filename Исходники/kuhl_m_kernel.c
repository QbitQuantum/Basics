BOOL kuhl_m_kernel_addWorldToMimikatz(SC_HANDLE monHandle)
{
	BOOL status = FALSE;
	DWORD dwSizeNeeded;
	PSECURITY_DESCRIPTOR oldSd, newSd;
	SECURITY_DESCRIPTOR dummySdForXP;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	EXPLICIT_ACCESS ForEveryOne = {
		SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG | SERVICE_INTERROGATE | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_PAUSE_CONTINUE | SERVICE_START | SERVICE_STOP | SERVICE_USER_DEFINED_CONTROL | READ_CONTROL,
		SET_ACCESS,
		NO_INHERITANCE,
		{NULL, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_SID, TRUSTEE_IS_WELL_KNOWN_GROUP, NULL}
	};
	if(!QueryServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, &dummySdForXP, 0, &dwSizeNeeded) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
	{
		if(oldSd = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, dwSizeNeeded))
		{
			if(QueryServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, oldSd, dwSizeNeeded, &dwSizeNeeded))
			{
				if(AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, (PSID *)&ForEveryOne.Trustee.ptstrName))
				{
					if(BuildSecurityDescriptor(NULL, NULL, 1, &ForEveryOne, 0, NULL, oldSd, &dwSizeNeeded, &newSd) == ERROR_SUCCESS)
					{
						status = SetServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, newSd);
						LocalFree(newSd);
					}
					FreeSid(ForEveryOne.Trustee.ptstrName);
				}
			}
			LocalFree(oldSd);
		}
	}
	return status;
}