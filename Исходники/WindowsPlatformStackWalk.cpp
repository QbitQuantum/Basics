/** 
 * Upload locally built symbols to network symbol storage.
 *
 * Use case:
 *   Game designers use game from source (without prebuild game .dll-files).
 *   In this case all game .dll-files are compiled locally.
 *   For post-mortem debug programmers need .dll and .pdb files from designers.
 */
bool FWindowsPlatformStackWalk::UploadLocalSymbols()
{
	InitStackWalking();

#if WINVER > 0x502
	// Upload locally compiled files to symbol storage.
	FString SymbolStorage;
	if (!GConfig->GetString( CrashReporterSettings, TEXT( "UploadSymbolsPath" ), SymbolStorage, GEditorPerProjectIni ) || SymbolStorage.IsEmpty())
	{
		// Nothing to do.
		return true;
	}
	// Prepare string
	SymbolStorage.ReplaceInline( TEXT( "/" ), TEXT( "\\" ), ESearchCase::CaseSensitive );
	SymbolStorage = TEXT( "SRV*" ) + SymbolStorage;

	int32 ErrorCode = 0;
	HANDLE ProcessHandle = GetCurrentProcess();

	// Enumerate process modules.
	HMODULE* ModuleHandlePointer = GetProcessModules( ProcessHandle );
	if (!ModuleHandlePointer)
	{
		ErrorCode = GetLastError();
		return false;
	}

#if WITH_EDITOR
	// Get Unreal Engine Editor directory for detecting non-game editor binaries.
	FString EnginePath = FPaths::ConvertRelativePathToFull( FPaths::EngineDir() );
	FPaths::MakePlatformFilename( EnginePath );
#endif

	// Upload all locally built modules.
	for (int32 ModuleIndex = 0; ModuleHandlePointer[ModuleIndex]; ModuleIndex++)
	{
		WCHAR ImageName[MAX_PATH] = {0};
		FGetModuleFileNameEx( ProcessHandle, ModuleHandlePointer[ModuleIndex], ImageName, MAX_PATH );

#if WITH_EDITOR
		WCHAR RelativePath[MAX_PATH];
		// Skip binaries inside Unreal Engine Editor directory (non-game editor binaries)
		if (PathRelativePathTo( RelativePath, *EnginePath, FILE_ATTRIBUTE_DIRECTORY, ImageName, 0 ) && FCString::Strncmp( RelativePath, TEXT( "..\\" ), 3 ))
		{
			continue;
		}
#endif

		WCHAR DebugName[MAX_PATH];
		FCString::Strcpy( DebugName, ImageName );

		if (PathRenameExtensionW( DebugName, L".pdb" ))
		{
			// Upload only if found .pdb file
			if (PathFileExistsW( DebugName ))
			{
				// Upload original file
				UE_LOG( LogWindows, Log, TEXT( "Uploading to symbol storage: %s" ), ImageName );
				if (!SymSrvStoreFileW( ProcessHandle, *SymbolStorage, ImageName, SYMSTOREOPT_PASS_IF_EXISTS ))
				{
					UE_LOG( LogWindows, Warning, TEXT( "Uploading to symbol storage failed: %s. Error: %d" ), ImageName, GetLastError() );
				}

				// Upload debug symbols
				UE_LOG( LogWindows, Log, TEXT( "Uploading to symbol storage: %s" ), DebugName );
				if (!SymSrvStoreFileW( ProcessHandle, *SymbolStorage, DebugName, SYMSTOREOPT_PASS_IF_EXISTS ))
				{
					UE_LOG( LogWindows, Warning, TEXT( "Uploading to symbol storage failed: %s. Error: %d" ), DebugName, GetLastError() );
				}
			}
		}
	}
#else
	UE_LOG( LogWindows, Log, TEXT( "Symbol server not supported on Windows XP." ) );
#endif
	return true;
}