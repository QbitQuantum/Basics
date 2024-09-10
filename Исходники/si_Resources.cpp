//////////////////////////////////////////////////////////////////////////////////////
//
// RESOURCES => Extraction de fmod.dll (en run-time grâce à l'option /DELAYLOAD:fmod.dll)
//              le déchargement éventuel de l'ancienne version nécessite /DELAY:UNLOAD
//
void fmod_extract (void)
{
	// on vérifie si fmod.dll est présent dans le répertoire système de windows
	// (/system pour win9x/ME, /system32 pour win2000/XP)

	char Path[MAX_PATH+1];
	GetSystemDirectory ( Path, MAX_PATH+1 );

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char searchFile[MAX_PATH+1];
	strcpy(searchFile, Path);
	strcat(searchFile, "\\fmod.dll");

	hFind = FindFirstFile(searchFile, &FindFileData);

	// la version est-elle à jour ?
	// si la version trouvée est inférieure à la version en ressource interne
	// nous devons décharger de la mémoire la première pour la remplacer par la
	// deuxième. Car l'appel de FSOUND_GetVersion() ci-dessous charge
	// automatiquement l'ancienne version pour toute la durée d'exécution.

	bool fmodIsUptodate = false;
	if ((hFind != INVALID_HANDLE_VALUE))						// si le fichier existe
		if (FSOUND_GetVersion() < FMOD_VERSION)					// si la version est inférieure
		{
			fmodIsUptodate = false;
			// décharge l'ancienne dll			
			#if _MSC_VER >= 1300
				if (FAILED(__FUnloadDelayLoadedDLL2("fmod.dll")))	// MSVC++ 7.0 et +
			#else
				//if (FAILED(__FUnloadDelayLoadedDLL("fmod.dll")))	// MSVC++ 6.0 et -
			#endif
				ERR("Error unloading the old fmod.dll.\nTry to delete %system%/fmod.dll and restart the game.\nIt will extract a new version automatically.\n");
		}
		else
			fmodIsUptodate = true;

	// s'il n'est pas présent ou la version plus ancienne on le crée
	if ((hFind == INVALID_HANDLE_VALUE) || (hFind != INVALID_HANDLE_VALUE && !fmodIsUptodate))
	{
		// déclarations et initialisations
		char		m_szFilename[MAX_PATH];
		HINSTANCE	m_hModule	= NULL;
		char		m_szType[MAX_PATH];
		DWORD		m_dwID;

		DWORD		dwID		= IDR_BINARY_FMOD;
		LPCSTR		szType		= "BINARY";
		LPCSTR		szFilename	= strcat(Path, "\\fmod.dll");

		memset(m_szType,0,sizeof m_szType);
		memcpy(m_szType,(void*)szType,strlen(szType));

		memset(m_szFilename,0,sizeof m_szFilename);
		memcpy(m_szFilename,szFilename,strlen(szFilename));

		m_dwID = dwID;

		// extraction de la ressource
		HRSRC	hRes		= FindResource(m_hModule, MAKEINTRESOURCE(m_dwID), m_szType);
		DWORD	dwDataSize	= SizeofResource(m_hModule,hRes);
		HGLOBAL	hGlob		= LoadResource(m_hModule,hRes);
		LPVOID	pData		= LockResource(hGlob);

		// création du fichier
		HANDLE hFile = CreateFile (m_szFilename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if( hFile == INVALID_HANDLE_VALUE )
		{
			UnlockResource(hGlob);
			FreeResource(hGlob);	
		}

		DWORD	dwBytesWritten=0;

		if( !WriteFile(hFile,pData,dwDataSize,&dwBytesWritten,NULL) 
			||
			dwBytesWritten != dwDataSize)
		{
			CloseHandle(hFile);
			UnlockResource(hGlob);
			FreeResource(hGlob);	
			if(DeleteFile(m_szFilename))
				memset(m_szFilename,0,sizeof m_szFilename);
		}

		CloseHandle(hFile);
		UnlockResource(hGlob);
		FreeResource(hGlob);
	}

	FindClose (hFind);
}