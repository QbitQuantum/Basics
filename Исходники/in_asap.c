static void expandFileSongs(HWND playlistWnd, int index)
{
	const char *fn;
	fileinfo fi;
	int song;
	ASAP_ModuleInfo module_info;
	char *p;
	int j;
	fn = (const char *) SendMessage(mod.hMainWindow, WM_WA_IPC, index, IPC_GETPLAYLISTFILE);
	song = extractSongNumber(fn, fi.file);
	if (song >= 0 || !ASAP_IsOurFile(fi.file))
		return;
	if (!loadModule(fi.file, module, &module_len))
		return;
	if (!ASAP_GetModuleInfo(&module_info, fi.file, module, module_len))
		return;
	SendMessage(playlistWnd, WM_WA_IPC, IPC_PE_DELETEINDEX, index);
	p = fi.file + strlen(fi.file);
	for (j = 0; j < module_info.songs; j++) {
		COPYDATASTRUCT cds;
		sprintf(p, "#%d", j + 1);
		fi.index = index + j;
		cds.dwData = IPC_PE_INSERTFILENAME;
		cds.lpData = &fi;
		cds.cbData = sizeof(fileinfo);
		SendMessage(playlistWnd, WM_COPYDATA, 0, (LPARAM) &cds);
	}
}