void editSetting(MCONTACT hContact, char* module, char* setting)
{
	DBVARIANT dbv = { 0 }; // freed in the dialog
	if (!GetSetting(hContact, module, setting, &dbv))
	{
		struct DBsetting *dbsetting = (struct DBsetting *)mir_alloc(sizeof(struct DBsetting)); // gets free()ed in the window proc

		dbsetting->dbv = dbv; // freed in the dialog
		dbsetting->hContact = hContact;
		dbsetting->module = mir_tstrdup(module);
		dbsetting->setting = mir_tstrdup(setting);

		if (dbv.type == DBVT_UTF8)
			CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_EDIT_SETTING), hwnd2mainWindow, EditSettingDlgProc, (LPARAM)dbsetting);
		else
			CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_EDIT_SETTING), hwnd2mainWindow, EditSettingDlgProc, (LPARAM)dbsetting);
	}
}