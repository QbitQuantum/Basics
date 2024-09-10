	BOOL LoadAdvApi()
	{
		if (mh_AdvApi)
		{
			return TRUE;
		}

		for (int i = 0; i <= 1; i++)
		{
			if (i == 0)
			{
				_ASSERTE(_WIN32_WINNT_WIN7==0x601);
				OSVERSIONINFOEXW osvi = {sizeof(osvi), HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7)};
				DWORDLONG const dwlConditionMask = VerSetConditionMask(VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL);
				if (!_VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask))
					continue; // в Vista и ниже "KernelBase.dll" еще не было
				mh_AdvApi = LoadLibrary(L"KernelBase.dll");
			}
			else
			{
				mh_AdvApi = LoadLibrary(L"Advapi32.dll");
			}
			
			if (!mh_AdvApi)
			{
				#ifdef _DEBUG
				mn_LastError = GetLastError();
				#endif
				return FALSE;
			}

			AddAccessAllowedAce = (AddAccessAllowedAce_t)GetProcAddress(mh_AdvApi, "AddAccessAllowedAce");
			AddAccessDeniedAce = (AddAccessDeniedAce_t)GetProcAddress(mh_AdvApi, "AddAccessDeniedAce");
			AllocateAndInitializeSid = (AllocateAndInitializeSid_t)GetProcAddress(mh_AdvApi, "AllocateAndInitializeSid");
			GetLengthSid = (GetLengthSid_t)GetProcAddress(mh_AdvApi, "GetLengthSid");
			InitializeAcl = (InitializeAcl_t)GetProcAddress(mh_AdvApi, "InitializeAcl");
			InitializeSecurityDescriptor = (InitializeSecurityDescriptor_t)GetProcAddress(mh_AdvApi, "InitializeSecurityDescriptor");
			SetSecurityDescriptorDacl = (SetSecurityDescriptorDacl_t)GetProcAddress(mh_AdvApi, "SetSecurityDescriptorDacl");

			if (AddAccessAllowedAce && AddAccessDeniedAce && AllocateAndInitializeSid &&
				GetLengthSid && InitializeAcl && InitializeSecurityDescriptor && SetSecurityDescriptorDacl)
			{
				return TRUE;
			}

	    	UnloadAdvApi();
	    	return FALSE;
	    }
		return FALSE;
	}