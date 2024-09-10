INT32 LibraryFile::Init(SuperGallery *ParentGal, PathName *APath, SGLibType Type, BOOL Updated, BOOL DoScroll)
{
#ifndef EXCLUDE_GALS
	if(ParentGal == NULL || APath == NULL || !Libraries.IsEmpty())
	{
		ERROR3("LibraryFile::Init - NULL parameters are illegal OR Init called > 1 times");
		if(!Libraries.IsEmpty())
			return(Libraries.GetCount());
		else
			return 0;
	}

	BOOL ok = TRUE;

	// Tidy up Path a bit
	String_256 OurPath(APath->GetPath());
	LibraryFile::TidyUpSubPath(&OurPath);

	// Now point Path to the new pathname
	PathName ModifiedPath(OurPath);
	PathName *Path = &ModifiedPath;

	if(!ModifiedPath.IsValid())
	{
		ERROR3("LibraryFile::Init -> Modified library path is invalid");
		return 0;
	}

	// Remember the pathname and type
	MyPath = *Path;
	MyType = Type;

	ParentGallery = ParentGal;
	if(ParentGallery->IsKindOf(CC_RUNTIME_CLASS(LibraryGallery)))
		ParentLibraryGallery = (LibraryGallery *)ParentGal;
	else
	{
		ERROR3("LibraryFile::Init passed a non-library gallery - yikes...");
		return 0;
	}

	// Need to reset the Quiet status before a stream of Library::Init calls
	ParentLibraryGallery->SetQuietStatus(FALSE);

	BOOL Retry = TRUE;
	while(Retry)
	{
		Retry = FALSE;
	
		// Would be nice to have a way of adding a file to a path in PathName... Is there one ?
		if(!SGLibOil::FileExists(Path))
		{
			// We're opening the font gallery, but can't find the font library path - don't warn
			if(Type == SGLib_Font)
				return 0;

			// tell the user that the directory doesn't exist
			String_256 WarnMsg;
			String_256 DefaultIndex;
			String_256 IndexDesc;
			BOOL CanGenerate;
		
			ok = LibraryFile::GetSubIndexDetails(ParentLibraryGallery, &DefaultIndex, &IndexDesc, &CanGenerate);

			String_256 TmpPath(Path->GetLocation(FALSE));
			LibraryFile::TidyUpSubPath(&TmpPath);

			// Taken out by Graham 30/10/97: If the gallery had no directory specified,
			//we used to throw a warning which said "do you want to specify another folder?"
			//We don't do this any more, because the default is to open all galleries empty and
			//then download stuff from the Xara web site
#if 0 
			WarnMsg.MakeMsg(_R(IDS_BROWSE_OR_SCAN), (TCHAR *)IndexDesc, (TCHAR *)TmpPath);
			Error::SetError(0, WarnMsg, 0);
			INT32 ButtonPressed = InformWarning(0, _R(IDS_BROWSE), _R(IDS_RETRY), _R(IDS_CANCEL)/*, _R(IDS_HELP)*/);
#else	// WEBSTER
			INT32 ButtonPressed = 3;
#endif  // WEBSTER
			TRACEUSER( "Richard", _T("ButtonPressed: %d\n"), ButtonPressed);
			Error::ClearError();
			switch(ButtonPressed)
			{
				case 1:
				{
					// Open the Browse dialog (or the Add.. dialog as it seems to be called now)
					PathName ThePath(*Path);
				
					// This returns FALSE if Cancel was hit, or an error occurred.
 					if(!SGLibOil::GetLibPath(ParentLibraryGallery, &ThePath, CanGenerate, Type))
					{
						ERROR3("GetLibPath returned FALSE in LF::Init");
						return 0;
					}
					else
					{
						ModifiedPath = ThePath;
						if(!ModifiedPath.IsValid())
						{
							ERROR3("LibraryFile::Init -> scanned library path is invalid");
							return 0;
						}

						// Remember the pathname
						MyPath = ThePath;

						switch(Type)
						{
							case SGLib_ClipArt:
							case SGLib_Bitmap:
								LibClipartSGallery::DefaultLibraryPath = MyPath.GetPath();
								LibClipartSGallery::ClipartPath = LibClipartSGallery::DefaultLibraryPath;
								break;

							case SGLib_ClipArt_WebThemes:
								LibClipartSGallery::DefaultLibraryPath = MyPath.GetPath();
								LibClipartSGallery::WebThemePath = LibClipartSGallery::DefaultLibraryPath;
								break;

#ifndef STANDALONE
							case SGLib_Texture:
							case SGLib_Fractal:
								LibFillsSGallery::DefaultLibraryPath = MyPath.GetPath();
								break;

							case SGLib_Font:
								// WEBSTER-Martin-09/01/97 - Put back by Ranbir.
								//#ifndef WEBSTER
								FontsSGallery::DefaultLibraryPath = MyPath.GetPath();
								break; // Not in webster so we get the error below
								//#endif // WEBSTER
#endif
							default:
								ERROR2(FALSE,"Library::ScanForLocation Type not present!");
								break;
						}
					}
					break;
				}						

				case 2:
					Retry = TRUE;
#if 0
					{
						// Scan
						String_256 Result;
						if(!Library::ScanForLocation(Type, &Result))
						{
							ERROR3("No libraries found...");
							return 0;
						}

						if(!ModifiedPath.SetPathName(Result))
						{
							ERROR3("LibraryFile::Init -> scanned library path is invalid");
							return 0;
						}

						// Remember the pathname and type
						MyPath = *Path;
					}
#endif
					break;

				case 3:
					// Cancel
					return 0;
			}
		}
	}

	// Wipe libraries added to gallery for scroll / redraw purposes...
	InitScrollRedrawSystem();

	// Check the actual path exists
   	if(SGLibOil::FileExists(Path))
	{
		// Would be nice to have a way of adding a file to a path in PathName... Is there one ?
		String_256 IndexFile((const TCHAR *)Path->GetPath(TRUE)); // "%s\\XaraInfo\\index.txt"
		IndexFile += String_16(_R(IDS_LIBRARIES_XARAINFO_DIRNAME));
		IndexFile += TEXT("\\") + String_16(_R(IDS_LIBRARIES_INDEX_FILENAME));

		PathName IndexFilePath(IndexFile);
		if(!IndexFilePath.IsValid())
		{
			ERROR3("LibraryFile::Init indexfilepath is invalid");
			return 0;
		}

		CCDiskFile MainIndex;
		if (!MainIndex.InitLexer(FALSE))
		{
			// SetError!
			ERROR3("LibraryFile::LibraryFile InitLexer failed");
			return(0);
		}

	   	if(SGLibOil::FileExists(&IndexFilePath))
		{
			// Count lines in index file
			INT32 Count = CountLines(&IndexFilePath);

			TRACEUSER( "Richard", _T("%d lines in index file\n"), Count);

			// Used for the percentage display
			INT32 CurrentGroupNumber = 0;

			// Just in case there's a slow job already going on...
			SmashSlowJob();
			String_64 SlowJob(_R(IDS_LIBRARY_SCANNING));
			BeginSlowJob(Count, FALSE, &SlowJob);
 		
			// Now use the index file to create each group in turn
			if (MainIndex.open(IndexFilePath, ios::in))
			{
				MainIndex.SetWhitespace("");		// Setting this to blank lets us read non-"'d strings
				MainIndex.SetDelimiters(",");		// ,s delimit our fields
				MainIndex.SetCommentMarker('#');	// #'d lines are commented out
				MainIndex.SetStringDelimiters("");	// No string delimiters

				String_64 Directory;
				String_64 Description;
				String_64 SubIndex;
				String_64 Kind;
				LexTokenType TT;
	
				BOOL EscapePressed = FALSE;

				while(ok && !EscapePressed)
				{
					if(!MainIndex.GetToken()) break;		// Get SubLib directory name

					// Keep reading tokens until we hit a normal one... (skips line ends and
					// comments for us
					TT = MainIndex.GetTokenType();		
					while (TT != TOKEN_NORMAL && ok)
					{
						ok = MainIndex.GetToken();
						if(!ok) break;
						TT = MainIndex.GetTokenType();		
						ok = (TT != TOKEN_EOF);
						if(!ok) break;
					}
					if(!ok) break;
	
					Directory = MainIndex.GetTokenBuf();
					KillLeadingSpaces(&Directory);

					if(!MainIndex.GetToken()) break;		// Get ','
					if(!MainIndex.GetToken()) break;		// Get Description
					String_256 Description256;
					Description256 = MainIndex.GetTokenBuf();
					KillLeadingSpaces(&Description256);
					Description256.Left(&Description, 60);

					if(!MainIndex.GetToken()) break;		// Get ','
					if(!MainIndex.GetToken()) break;		// Get Sub Library Index name
					SubIndex = MainIndex.GetTokenBuf();
					KillLeadingSpaces(&SubIndex);

					if(!MainIndex.GetToken()) break;		// Get ','
					if(!MainIndex.GetToken()) break;		// Get type of files in sublib
					Kind = MainIndex.GetTokenBuf();
					KillLeadingSpaces(&Kind);
	
					BOOL Match = FALSE;
					Match = ParentLibraryGallery->CheckForIndexMatch(&Kind);

					if(Match)
					{				
						// Show status of additions
						EscapePressed = !ContinueSlowJob(CurrentGroupNumber++);
				
						// Sort pathname of sublib directory out	
						String_256 SubP(Path->GetPath(TRUE));
						SubP += Directory;
						PathName SubPath(SubP);
						if(!SubPath.IsValid())
						{
							ERROR3("LibraryFile::Init - invalid subpath");
							if(MainIndex.isOpen())
								MainIndex.close();
							EndSlowJob();								
							return 0;
						}
																   
						// Go ahead and add the new group
						if(ok)
						{
							// Create the sub lib
							Library *NewSubLib = new Library;

							if (NewSubLib != NULL)
							{
								// Create the new group in the gallery (note the TRUE for create a virtualised one if
								// we can to save time / memory)
								if(NewSubLib->Init(ParentGal, &SubPath, &Description, &SubIndex, Type, Updated, TRUE))
								{
									Libraries.AddTail(NewSubLib);

									// Keep track of libraries added for redraw purposes...
									AddNewFolderToScrollRedrawSystem(NewSubLib);
								}
								else
								{
									// This check is new, should be ok...
									delete NewSubLib;
									NewSubLib = NULL;
									ERROR3("Library::Init failed in LibraryFile::Init");
									ok = FALSE;
								}
							}
						}
					}
				}

			} else {
				// Failed to open the index file...

				// SetError?!
				ERROR3("LibraryFile::LibraryFile couldn't open index file");
				ok = FALSE;
			}

			EndSlowJob();								

		} else {
			// The directory given had no XaraInfo\index.txt file, maybe it's a sublib, check
			// For defaults...
			ok = CheckForSubIndexes(ParentGal, Path, Type, Updated);
		}

		// reclaim lexer-buffer memory
		MainIndex.DeinitLexer();

		// And close the file
		if(MainIndex.isOpen())
			MainIndex.close();

		// Scroll / redraw the newly added groups...
		if(DoScroll)
			DoScrollRedraw();
	}
	else
	{
		TRACEUSER( "Richard", _T("Path doesn't exist\n"));
	}

	// And return the number of items created
	return(Libraries.GetCount());
#endif
	return 0;
}