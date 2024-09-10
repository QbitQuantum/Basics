int CALLBACK wWinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPWSTR cmdline, int ncmd)
{
	wchar_t reg_location[] = L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E968-E325-11CE-BFC1-08002BE10318}\\0000\\UMD";
	
	RegOpenKeyExW(HKEY_LOCAL_MACHINE, reg_location, 0, KEY_WRITE, &display_reg_write);
	
	LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, reg_location, 0, KEY_READ, &display_reg_read);
	if (result == ERROR_SUCCESS) load_settings();

	DialogBoxParamW(h_instance, MAKEINTRESOURCE(IDD_ACE), NULL, dialog_proc, 0);

	return ERROR_SUCCESS;
}