int EDT_UtilReg_LogPermissions(HKEY hRootKey, const wchar_t *wzKey)
{
	int iReturnCode = EDT_OK;
	int err = ERROR_SUCCESS;

	HKEY hRegKey;
	LOG_ENTER();
	LOG_TIME(L"registry key (%ls\\%ls) --> \n",hRootKey==HKEY_CURRENT_USER?L"HKCU":L"HKLM",wzKey);

	if(ERROR_SUCCESS != (err = RegOpenKeyEx(hRootKey, wzKey, 0L, KEY_READ , &hRegKey)))
	{
		if(err != ERROR_FILE_NOT_FOUND)
		{
			LOG_ERRORCODE(L"RegOpenKeyEx failed",err);
			return EDT_ERR_REGISTRY_READ_FAILED;
		}
		else
		{
			LOG_EXIT(L"NOT FOUND\n");
			return EDT_ERR_REGISTRY_NOT_FOUND;
		}
	}
	PSECURITY_DESCRIPTOR pSecurityDescriptor = NULL;
	DWORD lcbSecurityDescriptor = 0;

	if(ERROR_INSUFFICIENT_BUFFER == (err = RegGetKeySecurity(hRegKey, DACL_SECURITY_INFORMATION, pSecurityDescriptor, &lcbSecurityDescriptor)))
	{     
		pSecurityDescriptor = (PSECURITY_DESCRIPTOR)malloc(lcbSecurityDescriptor);

		if(ERROR_SUCCESS != (err = RegGetKeySecurity(hRegKey, DACL_SECURITY_INFORMATION, pSecurityDescriptor, &lcbSecurityDescriptor)))
		{
			LOG_ERRORCODE(L"RegQueryValueEx failed",err);
			iReturnCode = EDT_ERR_REGISTRY_READ_FAILED;
		}
		else
		{
			BOOL bDaclPresent = FALSE;
			BOOL bDaclDefaulted = FALSE;
			PACL pDacl = NULL;

			GetSecurityDescriptorDacl(pSecurityDescriptor, &bDaclPresent, &pDacl, &bDaclDefaulted);
			if(bDaclPresent == TRUE)
			{
				if(pDacl == NULL)
				{
					LOG(L"A NULL discretionary access control list (DACL) found \nA NULL DACL implicitly allows all access to an object.\n");
				}
				else
				{
					LOG(L"A discretionary access control list (DACL) was found with Length = %d\n",pDacl->AclSize);
					LOG(L"Number of Access Control Elements (ACE's): %d\n",pDacl->AceCount);
					registryLogAces(pDacl);
				}
			}
			else
			{
				LOG(L"No discretionary access control list (DACL) found \n");
			}

			LPTSTR StringSecurityDescriptor;
			ULONG StringSecurityDescriptorLen;

			ConvertSecurityDescriptorToStringSecurityDescriptor(pSecurityDescriptor,SDDL_REVISION_1,DACL_SECURITY_INFORMATION,
				&StringSecurityDescriptor,&StringSecurityDescriptorLen);


			LOG(L"%s\n",(const wchar_t*)StringSecurityDescriptor);
			//parse info see http://msdn.microsoft.com/en-us/library/aa379570%28v=vs.85%29.aspx

			LocalFree(StringSecurityDescriptor);

		}
		free(pSecurityDescriptor);
	}
	else
	{
		LOG_ERRORCODE(L"RegGetKeySecurity failed",err);
	}

	if(ERROR_SUCCESS != (err = RegCloseKey(hRegKey)))
	{
		LOG_ERRORCODE(L"RegCloseKey failed",err);
	}

	LOG_EXIT(iReturnCode);
	return iReturnCode;
} 