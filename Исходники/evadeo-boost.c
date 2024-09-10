int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	BOOL quiet = FALSE;
	
	if (wcscmp(lpCmdLine, L"/QUIET") == 0) {
		quiet = TRUE;
	}
	if (GetFileAttributes(L"\\Evadeo\\x.eva") == INVALID_FILE_ATTRIBUTES ||
		GetFileAttributes(L"\\Windows\\Desktop") == INVALID_FILE_ATTRIBUTES) {
		if (quiet == FALSE) {
			MessageBox(NULL, L"Cet outil n'est compatible qu'avec Evadeo X50 et X60",
				TEXT("Evadeo Boost"),
				MB_OK);
		}
		return 1;
	}
	if (registry_key_exists(HKEY_LOCAL_MACHINE,
		L"\\System\\StorageManager\\Profiles\\"
		"SDMemory\\FATFS", L"EnableCacheWarm") == TRUE) {
		if (quiet == FALSE) {
			MessageBox(NULL, L"Votre Evadeo est deja en mode turbo",
				TEXT("Evadeo Boost"),
				MB_OK);
		}
		return 0;
	}
	if (quiet == FALSE) {
		MessageBox(NULL, L"Evadeo Boost v1.2 par Axey pour www.evadeiste.fr\r\n"
			"Cliquez sur OK pour redemarrer l'Evadeo en mode turbo",
			TEXT("Evadeo Boost"), MB_OK);
	}
	update_registry();
	ForcePageout();    
	Sleep(1000);
	ForcePageout();
	SetSystemPowerState(NULL, POWER_STATE_RESET, 0);

	return 0;
}