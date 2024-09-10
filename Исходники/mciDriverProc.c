LRESULT	CALLBACK
DriverProc(DWORD dwDriverID,
	HDRVR hDriver,
	UINT uMsg,
	LPARAM lParam1,
	LPARAM lParam2)
{
	LPDRVCONFIGINFO lpDrvConfigInfo;
	LPSTR lpszOpenParam;
	DWORD dwOpenParam;
	DWORD dwCloseParam1, dwCloseParam2;
	HWND hConfigWndParent;

	LPMCI_OPEN_DRIVER_PARMS lpMciOpenDriverParms;
	DWORD dwMciOpenFlags;
	LPMCI_OPEN_PARMS lpMciOpenParms;
	DWORD dwMciGenericFlags;
	LPMCI_GENERIC_PARMS lpMciGenericParms;
	DWORD dwMciGetDevCapsFlags;
	LPMCI_GETDEVCAPS_PARMS lpMciGetDevCapsParms;
	DWORD dwMciInfoFlags;
	LPMCI_INFO_PARMS lpMciInfoParms;
	DWORD dwMciStatusFlags;
	LPMCI_STATUS_PARMS lpMciStatusParms;

	switch (uMsg)
	{
	case DRV_INSTALL:
		lpDrvConfigInfo = (LPDRVCONFIGINFO) lParam2;
		return XXXX_Install(dwDriverID, hDriver,
			lpDrvConfigInfo);
	case DRV_REMOVE:
		return XXXX_Remove(dwDriverID, hDriver);
	case DRV_LOAD:
		return XXXX_Load(dwDriverID, hDriver);
	case DRV_FREE:
		return XXXX_Free(dwDriverID, hDriver);
	case DRV_ENABLE:
		return XXXX_Enable(dwDriverID, hDriver);
	case DRV_DISABLE:
		return XXXX_Disable(dwDriverID, hDriver);
	case DRV_OPEN:
		lpszOpenParam = (LPSTR) lParam1;
		dwOpenParam = (DWORD) lParam2;
		lpMciOpenDriverParms = (LPMCI_OPEN_DRIVER_PARMS) dwOpenParam;
		return XXXX_mciOpen(dwDriverID, hDriver,
			lpszOpenParam, lpMciOpenDriverParms);
	case DRV_CLOSE:
		dwCloseParam1 = (DWORD) lParam1;
		dwCloseParam2 = (DWORD) lParam2;
		return XXXX_Close(dwDriverID, hDriver,
			dwCloseParam1, dwCloseParam2);
	case DRV_QUERYCONFIGURE:
		return XXXX_QueryConfigure(dwDriverID, hDriver);
	case DRV_CONFIGURE:
		hConfigWndParent = (HWND) lParam1;
		lpDrvConfigInfo = (LPDRVCONFIGINFO) lParam2;
		return XXXX_Configure(dwDriverID, hDriver,
			hConfigWndParent, lpDrvConfigInfo);
	case MCI_OPEN_DRIVER:
		dwMciOpenFlags = (DWORD) lParam1;
		lpMciOpenParms = (LPMCI_OPEN_PARMS) lParam2;
		return XXXX_mciOpenDriver(dwDriverID, hDriver,
			dwMciOpenFlags, lpMciOpenParms);
	case MCI_CLOSE_DRIVER:
		dwMciGenericFlags = (DWORD) lParam1;
		lpMciGenericParms = (LPMCI_GENERIC_PARMS) lParam2;
		return XXXX_mciCloseDriver(dwDriverID, hDriver,
			dwMciGenericFlags, lpMciGenericParms);
	case MCI_GETDEVCAPS:
		dwMciGetDevCapsFlags = (DWORD) lParam1;
		lpMciGetDevCapsParms = (LPMCI_GETDEVCAPS_PARMS) lParam2;
		return XXXX_mciGetDevCaps(dwDriverID, hDriver,
			dwMciGetDevCapsFlags, lpMciGetDevCapsParms);
	case MCI_INFO:
		dwMciInfoFlags = (DWORD) lParam1;
		lpMciInfoParms = (LPMCI_INFO_PARMS) lParam2;
		return XXXX_mciInfo(dwDriverID, hDriver,
			dwMciInfoFlags, lpMciInfoParms);
	case MCI_STATUS:
		dwMciStatusFlags = (DWORD) lParam1;
		lpMciStatusParms = (LPMCI_STATUS_PARMS) lParam2;
		return XXXX_mciStatus(dwDriverID, hDriver,
			dwMciStatusFlags, lpMciStatusParms);
	}

	return DefDriverProc(dwDriverID, hDriver, uMsg, lParam1, lParam2);

}