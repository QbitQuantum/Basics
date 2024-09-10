int MainInteractive()
{
	HANDLE hClient = NULL;
	WLAN_INTERFACE_INFO sInfo[64];
	RPC_TSTR strGuid = NULL;

	TCHAR szBuffer[256];
	DWORD dwRead;
	if (OpenHandleAndCheckVersion(&hClient) != ERROR_SUCCESS)
	{
		_tsystem(_T("PAUSE"));
		return -1;
	}

	UINT nCount = EnumInterface(hClient, sInfo);
	for (UINT i = 0; i < nCount; ++i)
	{
		if (UuidToString(&sInfo[i].InterfaceGuid, &strGuid) == RPC_S_OK)
		{
			ULONG ulOperationMode = -1;
			PULONG pOperationMode;
			DWORD dwResult = GetInterface(wlan_intf_opcode_current_operation_mode, (PVOID*)&pOperationMode, &sInfo[i].InterfaceGuid);
			if (dwResult != ERROR_SUCCESS)
			{
				_tprintf(_T("GetInterface error, error code = %d\n"), dwResult);
				_tsystem(_T("PAUSE"));
			}
			else
			{
				ulOperationMode = *pOperationMode;
				WlanFreeMemory(pOperationMode);
			}

			_tprintf(_T("%d. %s\n\tName: %s\n\tDescription: %s\n\tState: %s\n\tOperation Mode: %s\n"),
				i,
				strGuid,
				getAdapterNameFromGuid((TCHAR*) strGuid).c_str(),
				sInfo[i].strInterfaceDescription,
				GetInterfaceStateString(sInfo[i].isState),
				GetInterfaceOperationModeString(ulOperationMode));

			RpcStringFree(&strGuid);
		}
	}

	UINT nChoice = 0;
	GUID ChoiceGUID;
	LPGUID pChoiceGUID = NULL;
	_tprintf(_T("Enter the choice (0, 1,..) of the wireless card you want to operate on:\n"));

	if (ReadConsole(GetStdHandle(STD_INPUT_HANDLE), szBuffer, _countof(szBuffer), &dwRead, NULL) == FALSE)
	{
		_putts(_T("Error input."));
		_tsystem(_T("PAUSE"));
		return -1;
	}
	szBuffer[dwRead] = 0;

	// TCHAR *aaa = _T("42dfd47a-2764-43ac-b58e-3df569c447da");
	// dwRead = sizeof(aaa);

	TCHAR buf[256];
	_stprintf_s(buf, 256, _T("{%s}"), szBuffer);

	if (dwRead > 32)
	{
		if (myGUIDFromString(buf, &ChoiceGUID) != TRUE)
		{
			_tprintf(_T("UuidFromString error, error code = %d\n"), -1);
			_tsystem(_T("PAUSE"));
		}
		else
		{
			pChoiceGUID = &ChoiceGUID;
		}
	}
	else
	{
		nChoice = _ttoi(szBuffer);

		if (nChoice > nCount)
		{
			_putts(_T("No such index."));
			_tsystem(_T("PAUSE"));
			return -1;
		}

		pChoiceGUID = &sInfo[nChoice].InterfaceGuid;
	}

	UINT nSTate = 0;
	ULONG ulOperationMode = -1;
	_tprintf(_T("Enter the operation mode (0, 1 or 2) you want to switch to for the chosen wireless card:\n"));
	_tprintf(_T("0: Extensible Station (ExtSTA)\n1: Network Monitor (NetMon)\n2: Extensible Access Point (ExtAP)\n"));

	if (ReadConsole(GetStdHandle(STD_INPUT_HANDLE), szBuffer, _countof(szBuffer), &dwRead, NULL) == FALSE)
	{
		_putts(_T("Error input."));
		_tsystem(_T("PAUSE"));
		return -1;
	}
	szBuffer[dwRead] = 0;
	nSTate = _ttoi(szBuffer);

	if (nSTate != 0 && nSTate != 1 && nSTate != 2)
	{
		_putts(_T("Only 0, 1 and 2 are valid inputs."));
		_tsystem(_T("PAUSE"));
		return -1;
	}
	if (nSTate == 0)
	{
		ulOperationMode = DOT11_OPERATION_MODE_EXTENSIBLE_STATION;
	}
	else if (nSTate == 1)
	{
		ulOperationMode = DOT11_OPERATION_MODE_NETWORK_MONITOR;
	}
	else // nSTate == 2
	{
		ulOperationMode = DOT11_OPERATION_MODE_EXTENSIBLE_AP;
	}

	DWORD dwResult = SetInterface(wlan_intf_opcode_current_operation_mode, (PVOID*)&ulOperationMode, pChoiceGUID);
	if (dwResult != ERROR_SUCCESS)
	{
		_tprintf(_T("SetInterface error, error code = %d\n"), dwResult);
		_tsystem(_T("PAUSE"));
	}
	else
	{
		_tprintf(_T("SetInterface success!\n"));
	}

	return 0;
}