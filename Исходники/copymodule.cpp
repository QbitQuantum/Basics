void copyModuleMenuItem(char* module, MCONTACT hContact)
{
	ModuleAndContact *mac = (ModuleAndContact *)mir_calloc(sizeof(ModuleAndContact));
	mac->hContact = hContact;
	strncpy(mac->module, module, 255);

	CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_COPY_MOD), 0, copyModDlgProc, (LPARAM)mac);
}