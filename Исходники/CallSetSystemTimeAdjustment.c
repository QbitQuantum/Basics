BOOL CallSetSystemTimeAdjustment(DWORD dwTimeAdjustment) {
	HANDLE hToken;
	BOOL bTimeAdjustmentDisabled = FALSE;

	if (dwTimeAdjustment == 0)
		bTimeAdjustmentDisabled = TRUE;
//	else
//		dwTimeAdjustment = atoi(argv[2]); // 100ns

	/* Get hToken */
	if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		PrintErrorMessage((__FILE__), "OpenProcessToken()", __LINE__);
		exit(1);
	}
	
	/* enable SE_SYSTEMTIME_NAME Privilege */
	if (!SetPrivilege(hToken, SE_SYSTEMTIME_NAME, TRUE)) {
	    CloseHandle(hToken);
		PrintErrorMessage((__FILE__), "SetPrivilege(hToken, SE_SYSTEMTIME_NAME, TRUE)", __LINE__);
		exit(1);
	}

	CloseHandle(hToken);

	/* Call SetSystemTimeAdjustment() */
	printf("SetSystemTimeAdjustment() Calling...\n");
	if (!SetSystemTimeAdjustment(dwTimeAdjustment, bTimeAdjustmentDisabled)) {
		if (bTimeAdjustmentDisabled)
			PrintErrorMessage((__FILE__), "SetSystemTimeAdjustment(0, TRUE)", __LINE__);
		else
			PrintErrorMessage((__FILE__), "SetSystemTimeAdjustment(dwTimeAdjustment, FALSE)", __LINE__);
		exit(1);
	}
	else {
		printf("dwTimeAdjustment: %ld [100-nanosecond unit]\n", dwTimeAdjustment);
		printf("bTimeAdjustmentDisabled : %s \n", bTimeAdjustmentDisabled ? "True (Sync RTC see KB232488)" : "False (Ignore RTC)");
	}
	return TRUE;
}