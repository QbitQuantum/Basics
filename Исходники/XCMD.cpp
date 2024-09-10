HRESULT DEVI(PTSTR ptzCmd)
{
	// Lookup device
	HDEVINFO hDev = SetupDiGetClassDevs(NULL, NULL, 0, DIGCF_ALLCLASSES);
	if (hDev == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	// Build SPDRP_HARDWAREID list
	TCHAR tzDevID[MAX_DevID];
	PTSTR p = tzDevID + 1;
	SP_DEVINFO_DATA sdDev = {sizeof(SP_DEVINFO_DATA)};
	for (UINT i = 0; (NUM_DevID < MAX_DevID) && SetupDiEnumDeviceInfo(hDev, i, &sdDev); i++)
	{
#if (_MSC_VER < 1300)
		PCM_Get_DevNode_Status CM_Get_DevNode_Status = (PCM_Get_DevNode_Status) GetProcAddress(GetModuleHandle(TEXT("SetupAPI")), "CM_Get_DevNode_Status");
		if (CM_Get_DevNode_Status)
#endif
		{
			// Exclude configured device
			ULONG uProblem = 0;
			ULONG uStatus = DN_HAS_PROBLEM;
			CM_Get_DevNode_Status(&uStatus, &uProblem, sdDev.DevInst, 0);
			if (uProblem != CM_PROB_NOT_CONFIGURED)
			{
#ifndef _DEBUG
				continue;
#endif
			}
		}

		// Get device ID
		if (SetupDiGetDeviceRegistryProperty(hDev, &sdDev, SPDRP_HARDWAREID, NULL, (PBYTE) p, MAX_DevID - NUM_DevID, NULL) && UStrCmpNI(p, TEXT("ACPI"), 4))
		{
			Log(IDS_FoundDevice, p);

			// Trim some stuff for quick search
			UINT j = 0;
			for (UINT k = 0; p[j]; j++)
			{
				if ((p[j] == '&') && (++k == 2))
				{
					break;
				}
			}
			p[-1] = j;
			for (p += j; *p; p++);
			p += 2;
		}
	}
	p[-1] = 0;

	SetupDiDestroyDeviceInfoList(hDev);
	if (tzDevID[0] == 0)
	{
		// No device
		return ERROR_NO_MATCH;
	}

	// Parse param
	BOOL bInstall = (ptzCmd[0] == '$');
	if (bInstall) ptzCmd++;
	PTSTR ptzClass = UStrChr(ptzCmd, ',');
	if (ptzClass) *ptzClass++ = 0;

	if (UStrCmpI(ptzCmd + UStrLen(ptzCmd) - 4, TEXT(".CAB")))
	{
		// Lookup driver from directory
		return DevDir(ptzCmd, tzDevID, ptzClass);
	}
	else
	{
		// Lookup CAB file
		TCHAR tzDevInf[MAX_PATH * 16];
		g_ptzDevInf = tzDevInf;
		HRESULT hResult = SetupIterateCabinet(ptzCmd, 0, (PSP_FILE_CALLBACK) DevCab, tzDevID) ? S_OK : E_FAIL;
		if (bInstall)
		{
			for (PTSTR p = tzDevInf; p < g_ptzDevInf; p += UStrLen(p) + 1)
			{
				PTSTR ptzDevID = p;
				p += UStrLen(p) + 1;
				DevIns(ptzDevID, p);
			}
		}
		return hResult;
	}
}