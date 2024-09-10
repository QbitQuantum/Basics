	explicit SecurityAttributes(MemoryPool& pool)
		: m_pool(pool)
	{
		// Ensure that our process has the SYNCHRONIZE privilege granted to everyone
		PSECURITY_DESCRIPTOR pOldSD = NULL;
		PACL pOldACL = NULL;

		// Pseudo-handles do not work on WinNT. Need real process handle.
		HANDLE hCurrentProcess = OpenProcess(READ_CONTROL | WRITE_DAC, FALSE, GetCurrentProcessId());
		if (hCurrentProcess == NULL) {
			Firebird::system_call_failed::raise("OpenProcess");
		}

		DWORD result = GetSecurityInfo(hCurrentProcess, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION,
							NULL, NULL, &pOldACL, NULL, &pOldSD);

		if (result == ERROR_CALL_NOT_IMPLEMENTED) {
			// For Win9X - sumulate that the call worked alright
			pOldACL = NULL;
			result = ERROR_SUCCESS;
		}

		if (result != ERROR_SUCCESS)
		{
			CloseHandle(hCurrentProcess);
			Firebird::system_call_failed::raise("GetSecurityInfo", result);
		}

		// NULL pOldACL means all privileges. If we assign pNewACL in this case
		// we'll lost all privileges except assigned SYNCHRONIZE
		if (pOldACL)
		{
			SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_WORLD_SID_AUTHORITY;
			PSID pSID = NULL;
			AllocateAndInitializeSid(&sidAuth, 1, SECURITY_WORLD_RID,
									 0, 0, 0, 0, 0, 0, 0, &pSID);

			EXPLICIT_ACCESS ea;
			memset(&ea, 0, sizeof(EXPLICIT_ACCESS));
			ea.grfAccessPermissions = SYNCHRONIZE;
			ea.grfAccessMode = GRANT_ACCESS;
			ea.grfInheritance = NO_INHERITANCE;
			ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
			ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
			ea.Trustee.ptstrName  = (LPTSTR) pSID;

			PACL pNewACL = NULL;
			SetEntriesInAcl(1, &ea, pOldACL, &pNewACL);

			SetSecurityInfo(hCurrentProcess, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION,
							NULL, NULL, pNewACL, NULL);

			if (pSID) {
				FreeSid(pSID);
			}
			if (pNewACL) {
				LocalFree(pNewACL);
			}
		}

		CloseHandle(hCurrentProcess);

		if (pOldSD) {
			LocalFree(pOldSD);
		}

		// Create and initialize the default security descriptor
		// to be assigned to various IPC objects.
		//
		// WARNING!!! The absent DACL means full access granted
		// to everyone, this is a huge security risk!

		PSECURITY_DESCRIPTOR p_security_desc = static_cast<PSECURITY_DESCRIPTOR>(
			pool.allocate(SECURITY_DESCRIPTOR_MIN_LENGTH));

		attributes.nLength = sizeof(attributes);
		attributes.lpSecurityDescriptor = p_security_desc;
		attributes.bInheritHandle = TRUE;

		if (!InitializeSecurityDescriptor(p_security_desc, SECURITY_DESCRIPTOR_REVISION) ||
			!SetSecurityDescriptorDacl(p_security_desc, TRUE, NULL, FALSE))
		{
			pool.deallocate(p_security_desc);
			attributes.lpSecurityDescriptor = NULL;
		}
	}