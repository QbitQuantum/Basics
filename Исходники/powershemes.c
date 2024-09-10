BOOLEAN CALLBACK
callback_EnumPwrScheme(UINT uiIndex, DWORD dwName, LPTSTR sName, DWORD dwDesc,
                       LPWSTR sDesc, PPOWER_POLICY pp,LPARAM lParam)
{
	int index;

	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(sDesc);
	UNREFERENCED_PARAMETER(dwDesc);
	UNREFERENCED_PARAMETER(dwName);

	if (ValidatePowerPolicies(0,pp))
	{
		if (guiIndex >= MAX_POWER_POLICY)
		{
			// FIXME:
			// Implement store power policy dynamically
			return FALSE;
		}


		memcpy(&gPP[guiIndex], pp, sizeof(POWER_POLICY));
		guiIndex++;

		index = (int) SendMessage(hList,
			   CB_ADDSTRING,
			   0,
			   (LPARAM)sName);
		if (index == CB_ERR)
			return FALSE;

		SendMessage(hList,
			   CB_SETITEMDATA,
			   index,
			   (LPARAM)uiIndex);

		if (aps == uiIndex)
		{
			SendMessage(hList,
			   CB_SELECTSTRING,
			   TRUE,
			   (LPARAM)sName);
			LoadConfig(GetParent(hList));
		}
	}
	return TRUE;
}