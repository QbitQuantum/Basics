const char *win_dir_chooser(const char *message, const char *fname)
{
	static char szFileName[MAX_PATH]="";
	BROWSEINFO lpbi;
	LPITEMIDLIST pidl;

	//on vide la structure lpbi
	ZeroMemory(&lpbi,sizeof(BROWSEINFO));

	//on remplit la structure avec des informations utiles
	lpbi.hwndOwner = GET_HWND;
	lpbi.lpszTitle = "Choisissez un répertoire...";
	lpbi.pszDisplayName = szFileName;

	//puis on lance le sélecteur de répertoires.
	pidl = SHBrowseForFolder(&lpbi);

	//si l'utilisateur a sélectionné un fichier
	if(pidl!=0) {
		BOOL result = SHGetPathFromIDList(pidl,szFileName);

		//désallocation de la mémoire déjà utilisée
		IMalloc * imalloc = 0;
		if(SUCCEEDED(SHGetMalloc(&imalloc))) {
			imalloc->Free(pidl);
			imalloc->Release();
		}
		//puis là on retourne le résultat: le chemin absolu
		//du répertoire sélectionné
		if(result) return szFileName;
	}

	return 0;
}