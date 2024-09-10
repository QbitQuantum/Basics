static int OnContactSettingChanged(MCONTACT hContact, DBCONTACTWRITESETTING* pdbcws)
{
	if (hContact && pdbcws && (pdbcws->value.type <= DBVT_BYTE) && !lstrcmpA(pdbcws->szSetting, SET_CONTACT_GENDER))
		OnCListApplyIcons(hContact, 0);

	return 0;
}