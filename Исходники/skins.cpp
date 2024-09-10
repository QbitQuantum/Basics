// returns true if at least one set of skin data was read, else false...
//
static bool Skins_Read(LPCSTR psModelFilename)
{
	LPCSTR psError = NULL;

	CWaitCursor;

	LPCSTR psSkinsPath = Skins_ModelNameToSkinPath(psModelFilename);	// eg "models/characters/skins"

	if (psSkinsPath)
	{
		string strThisModelBaseName(String_ToLower(Filename_WithoutExt(Filename_WithoutPath(psModelFilename))));

		char **ppsSkinFiles;
		int iSkinFiles;

		// scan for skin files...
		//
		ppsSkinFiles =	//ri.FS_ListFiles( "shaders", ".shader", &iSkinFiles );
						Sys_ListFiles(	va("%s%s",gamedir,psSkinsPath),// const char *directory, 
										".g2skin",	// const char *extension, 
										NULL,		// char *filter, 
										&iSkinFiles,// int *numfiles, 
										qfalse		// qboolean wantsubs 
										);

		if ( !ppsSkinFiles || !iSkinFiles )
		{
			CurrentSkins.clear();	
			CurrentSkinsSurfacePrefs.clear();
			return false;
		}

		if ( iSkinFiles > MAX_SKIN_FILES ) 
		{
			WarningBox(va("%d skin files found, capping to %d\n\n(tell me if this ever happens -Ste)", iSkinFiles, MAX_SKIN_FILES ));

			iSkinFiles = MAX_SKIN_FILES;
		}

		// load and parse skin files...
		//					
		// for now, I just scan each file and if it's out of date then I invalidate it's model-prefs info...
		//
		extern bool GetFileTime(LPCSTR psFileName, FILETIME &ft);
		for (int i=0; i<iSkinFiles; i++)
		{
			bool bReParseThisFile = false;

			char sFileName[MAX_QPATH];
			LPCSTR psFileName = ppsSkinFiles[i];
			Com_sprintf( sFileName, sizeof( sFileName ), "%s/%s", psSkinsPath, psFileName );
			psFileName = &sFileName[0];
											  
			// have a go at getting this time/date stamp if not already present...
			//
			if (!SkinFileTimeDates[psFileName].bValid)
			{
				FILETIME ft;
				if (GetFileTime(psFileName, ft))
				{
					SkinFileTimeDates[psFileName].ft = ft;
					SkinFileTimeDates[psFileName].bValid = true;
				}
			}

			// now see if there's a valid time-stamp, and use it if so, else give up and re-scan all files...
			//
			if (SkinFileTimeDates[psFileName].bValid)
			{
				FILETIME ft;
				if (GetFileTime(psFileName, ft))
				{
					LONG l = CompareFileTime( &SkinFileTimeDates[psFileName].ft, &ft);

					bReParseThisFile = (l<0);
				}
				else
				{
					bReParseThisFile = true;
				}
			}
			else
			{
				bReParseThisFile = true;
			}	
			
			if (bReParseThisFile)
			{
				G2SkinModelPrefs[sFileName].clear();
			}
		}		
		
		if (1)//bReParseSkinFiles || !CurrentSkins.size())
		{
			CurrentSkins.clear();	
			CurrentSkinsSurfacePrefs.clear();

			char *buffers[MAX_SKIN_FILES]={0};
//			long iTotalBytesLoaded = 0;
			for ( int i=0; i<iSkinFiles && !psError; i++ )
			{
				char sFileName[MAX_QPATH];

				string strThisSkinFile(ppsSkinFiles[i]);

				Com_sprintf( sFileName, sizeof( sFileName ), "%s/%s", psSkinsPath, strThisSkinFile.c_str() );
				StatusMessage( va("Scanning skin %d/%d: \"%s\"...",i+1,iSkinFiles,sFileName));

				//ri.Printf( PRINT_ALL, "...loading '%s'\n", sFileName );

				bool _bDiskLoadOccured = false;	// debug use only, but wtf?

#define LOAD_SKIN_FILE									\
/*iTotalBytesLoaded += */ ri.FS_ReadFile( sFileName, (void **)&buffers[i] );	\
if ( !buffers[i] )										\
{														\
	CurrentSkins.clear();								\
	CurrentSkinsSurfacePrefs.clear();					\
														\
	ri.Error( ERR_DROP, "Couldn't load %s", sFileName );\
}														\
_bDiskLoadOccured = true;


				// see if we should pay attention to the contents of this file...
				//
				CGPGroup	*pFileGroup			= NULL;
				CGPGroup *pParseGroup_Prefs	= NULL;
				CGenericParser2 SkinParser;
				//
				bool bParseThisFile = false;
				//
				// if we have any information about this skin file as regards what models it refers to, use the info...
				//
				if (G2SkinModelPrefs[sFileName].size())
				{
					map<string, int>::iterator it = G2SkinModelPrefs[sFileName].find( strThisModelBaseName );
					if (it != G2SkinModelPrefs[sFileName].end())
					{
						// this skin file contains this entry, so just check that we can setup the parse groups ok...
						//
						LOAD_SKIN_FILE;

						char *psDataPtr = buffers[i];
						if (SkinParser.Parse(&psDataPtr, true))
						{
							pFileGroup = SkinParser.GetBaseParseGroup();
							if (pFileGroup)
							{
								pParseGroup_Prefs = pFileGroup->FindSubGroup(sSKINKEYWORD_PREFS);//, true);
								if (pParseGroup_Prefs)
								{
									bParseThisFile = true;
								}
							}
						}
						else
						{
							ErrorBox(va("{} - Brace mismatch error in file \"%s\"!",sFileName));
						}
					}
				}
				else
				{
					// no size info for this file, so check it manually...
					//
					LOAD_SKIN_FILE;

					if (Skins_ParseThisFile(SkinParser, buffers[i], strThisModelBaseName, pFileGroup, pParseGroup_Prefs, 
											sFileName, G2SkinModelPrefs)
						)
					{
						bParseThisFile = true;
					}
				}

				if (bParseThisFile)
				{
					psError = Skins_Parse( strThisSkinFile, pFileGroup, pParseGroup_Prefs);
					if (psError)
					{
						ErrorBox(va("Skins_Read(): Error reading file \"%s\"!\n\n( Skins will be ignored for this model )\n\nError was:\n\n",sFileName,psError));
					}
				}
				else
				{
					//OutputDebugString(va("Skipping parse of file \"%s\" %s\n",sFileName, _bDiskLoadOccured?"":"( and no load! )"));
				}
			}
			//
			// free loaded skin files...
			//
			for ( i=0; i<iSkinFiles; i++ )
			{
				if (buffers[i])
				{
					ri.FS_FreeFile( buffers[i] );
				}
			}
		}

		StatusMessage(NULL);
		Sys_FreeFileList( ppsSkinFiles );
	}
	else
	{
		CurrentSkins.clear();	
		CurrentSkinsSurfacePrefs.clear();
	}

	if (psError)
	{
		return false;
	}

	return !!(CurrentSkins.size());
}