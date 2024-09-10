void CreateCustomMenu(){
	FreeMenuIfNecessary();
	hMenu = CreatePopupMenu();
	HMENU hFilterSubMenu = CreatePopupMenu();
	HMENU hOptionsSubMenu = CreatePopupMenu();
    
	char *currFilter = go_GetCurrentFilterName();

    //Main Menu
    AppendMenu(hMenu, MF_STRING | MF_GRAYED, 0, VERSION);
	//AppendMenuW(hSubMenu, MF_SEPARATOR, 0, NULL);
	//AppendMenuW(hSubMenu, MF_STRING, CMD_ABOUT, L"About");
	AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFilterSubMenu, L"Filer");
	AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hOptionsSubMenu, L"Options");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, CMD_EXIT, L"Exit");

	//Sub Menu of Filters
	AppendMenuW(hFilterSubMenu, MF_STRING, CMD_FILTER_RELOAD, L"Reload current filter");
	AppendMenuW(hFilterSubMenu, MF_SEPARATOR, 0, NULL);
	int count = 0;
	char* name = go_GetNextFilterName();
	while ((strlen(name) > 0) && (count < 50)){
		if (strcmp(name , currFilter) == 0){
			AppendMenu(hFilterSubMenu, MF_STRING | MF_CHECKED, (UINT_PTR)hFilterSubMenu, name);
		}else{
			AppendMenu(hFilterSubMenu, MF_STRING, CMD_FILTERSELECT_START+count, name);
		}
		free(name);
		name = go_GetNextFilterName();
		count++;
	}
	free(name);
	AppendMenuW(hFilterSubMenu, MF_SEPARATOR, 0, NULL);
	if (strlen(currFilter) > 0){
		AppendMenuW(hFilterSubMenu, MF_STRING, CMD_FILTER_NONE, L"None");
	}else{
		AppendMenuW(hFilterSubMenu, MF_STRING | MF_CHECKED, CMD_FILTER_NONE, L"None");
	}
	free(currFilter);
	
	//Sub Menu of Options
	if (UseDoubleclick){
		AppendMenuW(hOptionsSubMenu, MF_STRING | MF_CHECKED, CMD_OPTIONS_USEDOUBLECLICK, L"Send Doubleclick");
	}else{
		AppendMenuW(hOptionsSubMenu, MF_STRING, CMD_OPTIONS_USEDOUBLECLICK, L"Send Doubleclick");
	}
	if (CheckForUpdates){
		AppendMenuW(hOptionsSubMenu, MF_STRING | MF_CHECKED, CMD_OPTIONS_CHECKUPDATES, L"Check for updates");
	}else{
		AppendMenuW(hOptionsSubMenu, MF_STRING, CMD_OPTIONS_CHECKUPDATES, L"Check for updates");
	}
	if (LaunchPoE){
		AppendMenuW(hOptionsSubMenu, MF_STRING | MF_CHECKED, CMD_OPTIONS_LAUNCHPOE, L"Launch PoE on start");
	}else{
		AppendMenuW(hOptionsSubMenu, MF_STRING, CMD_OPTIONS_LAUNCHPOE, L"Launch PoE on start");
	}
   // SetForegroundWindow(hWnd); // Win32 bug work-around
   // TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hWnd, NULL);

}