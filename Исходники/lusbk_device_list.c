static BOOL l_EnumKey_Instances(KUSB_ENUM_REGKEY_PARAMS* RegEnumParams)
{
	LONG status;
	PKLST_DEVINFO_EL newDevItem = NULL;
	HDEVINFO hDevInfo = NULL;
	DWORD length;
	DWORD iDeviceInterface = (DWORD) - 1;

	if (!RegEnumParams->Exclusive.DevInterfaceGuid)
	{
		// Apply DeviceInterfaceGUID filter:
		mLst_ApplyPatternMatch(RegEnumParams->PatternMatch, DeviceInterfaceGUID, RegEnumParams->TempItem->DeviceInterfaceGUID, goto NextInstance);

		hDevInfo = SetupDiGetClassDevsA(&RegEnumParams->DevInterfaceGuid, RegEnumParams->TempItem->DeviceID, NULL, RegEnumParams->DigcFlags | DIGCF_DEVICEINTERFACE);
		if (!IsHandleValid(hDevInfo))
		{
			USBDBGN("SetupDiGetClassDevsA Failed. ErrorCode:%08Xh", GetLastError());
			return TRUE;
		}
	}