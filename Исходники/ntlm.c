NTLM_CONTEXT* ntlm_ContextNew()
{
	HKEY hKey;
	LONG status;
	DWORD dwType;
	DWORD dwSize;
	DWORD dwValue;
	NTLM_CONTEXT* context;

	context = (NTLM_CONTEXT*) calloc(1, sizeof(NTLM_CONTEXT));

	if (!context)
		return NULL;

	context->NTLMv2 = TRUE;
	context->UseMIC = FALSE;
	context->SendVersionInfo = TRUE;
	context->SendSingleHostData = FALSE;
	context->SendWorkstationName = TRUE;

	status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\WinPR\\NTLM"), 0, KEY_READ | KEY_WOW64_64KEY, &hKey);

	if (status == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hKey, _T("NTLMv2"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->NTLMv2 = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("UseMIC"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->UseMIC = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("SendVersionInfo"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->SendVersionInfo = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("SendSingleHostData"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->SendSingleHostData = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("SendWorkstationName"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->SendWorkstationName = dwValue ? 1 : 0;

		if (RegQueryValueEx(hKey, _T("WorkstationName"), NULL, &dwType, NULL, &dwSize) == ERROR_SUCCESS)
		{
			char* workstation = (char*) malloc(dwSize + 1);

			if (!workstation)
				return NULL;

			status = RegQueryValueExA(hKey, "WorkstationName", NULL, &dwType, (BYTE*) workstation, &dwSize);
			workstation[dwSize] = '\0';

			if (ntlm_SetContextWorkstation(context, workstation) < 0)
				return NULL;

			free(workstation);
		}

		RegCloseKey(hKey);
	}

	/*
	 * Extended Protection is enabled by default in Windows 7,
	 * but enabling it in WinPR breaks TS Gateway at this point
	 */
	context->SuppressExtendedProtection = FALSE;

	status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("System\\CurrentControlSet\\Control\\LSA"), 0, KEY_READ | KEY_WOW64_64KEY, &hKey);

	if (status == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hKey, _T("SuppressExtendedProtection"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			context->SuppressExtendedProtection = dwValue ? 1 : 0;

		RegCloseKey(hKey);
	}

	context->NegotiateFlags = 0;
	context->LmCompatibilityLevel = 3;
	context->state = NTLM_STATE_INITIAL;
	FillMemory(context->MachineID, sizeof(context->MachineID), 0xAA);

	if (context->NTLMv2)
		context->UseMIC = TRUE;

	return context;
}