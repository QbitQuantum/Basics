/*
========================
idSaveGameThread::Enumerate
========================
*/
int idSaveGameThread::Enumerate()
{
	idSaveLoadParms* callback = data.saveLoadParms;
	idStr saveFolder = "savegame";
	
	callback->detailList.Clear();
	
	int ret = ERROR_SUCCESS;
	if( fileSystem->IsFolder( saveFolder, "fs_savePath" ) == FOLDER_YES )
	{
		idFileList* files = fileSystem->ListFilesTree( saveFolder, SAVEGAME_DETAILS_FILENAME );
		const idStrList& fileList = files->GetList();
		
		for( int i = 0; i < fileList.Num() && !callback->cancelled; i++ )
		{
			idSaveGameDetails* details = callback->detailList.Alloc();
			// We have more folders on disk than we have room in our save detail list, stop trying to read them in and continue with what we have
			if( details == NULL )
			{
				break;
			}
			idStr directory = fileList[i];
			
			idFile* file = fileSystem->OpenFileRead( directory.c_str() );
			
			if( file != NULL )
			{
				// Read the DETAIL file for the enumerated data
				if( callback->mode & SAVEGAME_MBF_READ_DETAILS )
				{
					if( !SavegameReadDetailsFromFile( file, *details ) )
					{
						details->damaged = true;
						ret = -1;
					}
				}
#ifdef _WIN32 // DG: unification of win32 and posix savagame code
				// Use the date from the directory
				WIN32_FILE_ATTRIBUTE_DATA attrData;
				BOOL attrRet = GetFileAttributesEx( file->GetFullPath(), GetFileExInfoStandard, &attrData );
				delete file;
				if( attrRet == TRUE )
				{
					FILETIME		lastWriteTime = attrData.ftLastWriteTime;
					const ULONGLONG second = 10000000L; // One second = 10,000,000 * 100 nsec
					SYSTEMTIME		base_st = { 1970, 1, 0, 1, 0, 0, 0, 0 };
					ULARGE_INTEGER	itime;
					FILETIME		base_ft;
					BOOL			success = SystemTimeToFileTime( &base_st, &base_ft );
					
					itime.QuadPart = ( ( ULARGE_INTEGER* )&lastWriteTime )->QuadPart;
					if( success )
					{
						itime.QuadPart -= ( ( ULARGE_INTEGER* )&base_ft )->QuadPart;
					}
					else
					{
						// Hard coded number of 100-nanosecond units from 1/1/1601 to 1/1/1970
						itime.QuadPart -= 116444736000000000LL;
					}
					itime.QuadPart /= second;
					details->date = itime.QuadPart;
				}
#else
				// DG: just use the idFile object's timestamp - the windows code gets file attributes and
				//  other complicated stuff like that.. I'm wonderin what that was good for.. this seems to work.
				details->date = file->Timestamp();
#endif // DG end
			}
			else
			{
				details->damaged = true;
			}
			
			// populate the game details struct
			directory = directory.StripFilename();
			details->slotName = directory.c_str() + saveFolder.Length() + 1; // Strip off the prefix too
// JDC: I hit this all the time			assert( fileSystem->IsFolder( directory.c_str(), "fs_savePath" ) == FOLDER_YES );
		}
		fileSystem->FreeFileList( files );
	}
	else
	{
		callback->errorCode = SAVEGAME_E_FOLDER_NOT_FOUND;
		ret = -3;
	}
	
	if( data.saveLoadParms->cancelled )
	{
		data.saveLoadParms->errorCode = SAVEGAME_E_CANCELLED;
	}
	
	return ret;
}