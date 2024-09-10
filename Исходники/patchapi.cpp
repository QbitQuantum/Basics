unsigned GetNextVMSessionPIDEx( HANDLE hList, VMType *pVMType )
{
	TCHAR *tszNames[] = {_T("VirtualBox.exe"), _T("vmware-vmx.exe"), _T("vmware-vmx-debug.exe"), _T("vmware-vmx-stats.exe")};
	unsigned PID = 0;
	unsigned idxMatch = 0;
	for (;;)
	{
		PID = FindProcessByNames(hList, tszNames, __countof(tszNames), false, &idxMatch);
		if ((PID == -1) || !PID)
			return 0;
		if (idxMatch)
			break;
		//Skip VirtualBox processes not running any VMs
		wchar_t sessionName[MAX_PATH];
		if (GetVMSessionNameW(PID, sessionName, __countof(sessionName)))
			break;
	}
	if (pVMType)
	{
		if (!PID)
			*pVMType = kVMUnknown;
		{
			BazisLib::WOW64APIProvider wow;
#ifdef _WIN64
			bool Is64 = !wow.IsWow64Process(PID);
#else
			bool Is64 = wow.IsWow64Process() && !wow.IsWow64Process(PID);
#endif
			if (idxMatch)
				*pVMType = Is64 ? kVMWare64 : kVMWare32;
			else
				*pVMType = Is64 ? kVBox64 : kVBox32;
		}
	}
	return PID;
}