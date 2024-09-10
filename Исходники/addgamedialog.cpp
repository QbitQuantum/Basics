BOOL OpenFileDialog(HWND hwndDlg, OPENFILENAMEA*ofn, char*exe) {
	//pointer zum exenamen
	char* exename = NULL;
	//buffer vom pfad
	static char szFile[260] = ""; //static damit noch nach dem aufruf lesbar bleibt
	//buffer vom filter
	char szFilter[260] = "";
	//backslash suchen
	exename = strrchr(exe, '\\') + 1;
	//kein backslash dann normal ret als exenamen verwenden
	if ((int)exename == 1) exename = exe;
	//filterstring aufbauen
	mir_snprintf(szFilter, SIZEOF(szFilter), "%s|%s|%s|*.*|", exename, exename, Translate("All Files"));
	//umbruch in 0 wandeln
	unsigned int sizeFilter = strlen(szFilter);
	for (unsigned int i = 0; i < sizeFilter; i++)
		if (szFilter[i] == '|') szFilter[i] = 0;
	//openfiledia vorbereiten
	memset(ofn, 0, sizeof(OPENFILENAMEA));
	ofn->lStructSize = sizeof(OPENFILENAMEA);
	ofn->hwndOwner = hwndDlg;
	ofn->lpstrFile = szFile;
	ofn->nMaxFile = SIZEOF(szFile);
	ofn->lpstrFilter = szFilter;
	ofn->nFilterIndex = 1;
	ofn->lpstrFileTitle = exe;
	ofn->nMaxFileTitle = 0;
	ofn->lpstrInitialDir = NULL;
	ofn->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return GetOpenFileNameA(ofn);
}