int IconPressed(WPARAM wParam, LPARAM lParam) {
	StatusIconClickData *cd = (StatusIconClickData *)lParam;
	if(strcmp(cd->szModule, MODULE) != 0) return 0;

	HANDLE hContact = (HANDLE)wParam, hSub;
	if(ServiceExists(MS_MC_GETMOSTONLINECONTACT) && (hSub = (HANDLE)CallService(MS_MC_GETMOSTONLINECONTACT, (WPARAM)hContact, 0)) != 0)
		hContact = hSub;

	if(!CallService(MS_PROTO_ISPROTOONCONTACT, (WPARAM)hContact, (LPARAM)MODULE))
		return 0;

	HMENU hMenu = CreatePopupMenu();
	for(int i = 0; zap_array[i]; i++) {
		AppendMenuA(hMenu,MF_STRING,i+1, Translate(zap_array[i]));
	}	
	BOOL cmd = TrackPopupMenu(hMenu, TPM_NONOTIFY | TPM_RETURNCMD, cd->clickLocation.x, cd->clickLocation.y, 0, (HWND)CallService(MS_CLUI_GETHWND, 0, 0), 0);
	DestroyMenu(hMenu);

	if(cmd) {
		int zap_num = cmd - 1;
		NotifyZapSend(hContact, zap_num);
	}
	return 0;
}