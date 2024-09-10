ibool
os_awe_enable_lock_pages_in_mem(void)
/*=================================*/
				/* out: TRUE if success, FALSE if error;
				prints error info to stderr if no success */
{
#ifdef UNIV_SIMULATE_AWE

	return(TRUE);

#elif defined(__WIN2000__)
	struct {
		DWORD			Count;
		LUID_AND_ATTRIBUTES	Privilege[1];
	}	Info;
	HANDLE	hProcess;
	HANDLE	Token;
	BOOL	Result;

	hProcess = GetCurrentProcess();

	/* Open the token of the current process */

	Result = OpenProcessToken(hProcess,
				  TOKEN_ADJUST_PRIVILEGES, &Token);
	if (Result != TRUE) {
		fprintf(stderr,
			"InnoDB: AWE: Cannot open process token, error %lu\n",
			(ulint)GetLastError());
		return(FALSE);
	}

	Info.Count = 1;

	Info.Privilege[0].Attributes = SE_PRIVILEGE_ENABLED;

	/* Get the local unique identifier (LUID) of the SE_LOCK_MEMORY
	privilege */

	Result = LookupPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME,
				      &(Info.Privilege[0].Luid));
	if (Result != TRUE) {
		fprintf(stderr,
			"InnoDB: AWE: Cannot get local privilege"
			" value for %s, error %lu.\n",
			SE_LOCK_MEMORY_NAME, (ulint)GetLastError());

		return(FALSE);
	}

	/* Try to adjust the privilege */

	Result = AdjustTokenPrivileges(Token, FALSE,
				       (PTOKEN_PRIVILEGES)&Info,
				       0, NULL, NULL);
	/* Check the result */

	if (Result != TRUE) {
		fprintf(stderr,
			"InnoDB: AWE: Cannot adjust process token privileges,"
			" error %u.\n",
			GetLastError());
		return(FALSE);
	} else if (GetLastError() != ERROR_SUCCESS) {
		fprintf(stderr,
			"InnoDB: AWE: Cannot enable SE_LOCK_MEMORY privilege,"
			" error %lu.\n"
			"InnoDB: In Windows XP Home you cannot use AWE."
			" In Windows 2000 and XP\n"
			"InnoDB: Professional you must go to the"
			" Control Panel, to\n"
			"InnoDB: Security Settings, to Local Policies,"
			" and enable\n"
			"InnoDB: the 'lock pages in memory' privilege"
			" for the user who runs\n"
			"InnoDB: the MySQL server.\n", GetLastError());

		return(FALSE);
	}

	CloseHandle(Token);

	return(TRUE);
#else
#ifdef __WIN__
	fprintf(stderr,
		"InnoDB: AWE: Error: to use AWE you must use"
		" a ...-nt MySQL executable.\n");
#endif
	return(FALSE);
#endif
}