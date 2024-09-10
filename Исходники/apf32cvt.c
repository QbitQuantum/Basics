void ConvertImports (char * File)
{
    PIMAGE_IMPORT_DESCRIPTOR ImageImportDescr,DataImportDescr;
    HANDLE  mFile;
    ULONG   ImportSize,
            ImportName,
            PreferredImportBase,
            ImportNameLen,
            DataImportBase;
    BOOL    BoolError;
    CHAR   *pchDot;
    LPVOID  FileBase=NULL;
    int     iNewImp;

    ULONG   ulBinaryType ;
    PIMAGE_NT_HEADERS NtHeaders;
    ULONG	CheckSum;
    ULONG	HeaderSum;
	
    
    // Get file attributes
    //
    OldAttributes = GetFileAttributes(File);
    if (OldAttributes != FILE_ATTRIBUTE_NORMAL) {
        BoolError = SetFileAttributes(File, FILE_ATTRIBUTE_NORMAL);
    }


    ulBinaryType = GetImageType ( File ) ;

    //
	// Open file
    //
    hFile=CreateFile(File,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        (HANDLE)NULL);
    if (hFile==INVALID_HANDLE_VALUE) {

#ifdef DEBUG
        Error = GetLastError();
        printf("Error in creating file %lx\n",Error);
#endif
        DoError (FAIL_OPEN, File);
        return;
    }

//
//  tomzak
//
    if ( ulBinaryType != NT_CODE ) {
        DoError (NOT_NT_IMAGE, File);
		//
		// Close file handle
		//
		BoolError = CloseHandle(hFile);
		if (!BoolError) {
			DoError(FAIL_CLOSE,NULL);
		}
        return ;
    }


    // Create the file map
    //
    mFile=CreateFileMapping(hFile,NULL,PAGE_READWRITE,0L,0L,NULL);

    if (!mFile) {

#ifdef DEBUG
        Error = GetLastError();
        printf("Can't make map object %lx\n",Error);
#endif

        DoError(CREATE_MAP,NULL);
        return;
    }

    // Map a view of the file as data
    //
    FileBase=MapViewOfFile(mFile, FILE_MAP_READ | FILE_MAP_WRITE, 0L, 0L, 0L);

    if (!FileBase) {
        DoError(VIEW_FILE_MAP,NULL);
    }

    // Get the address of the import descriptor as if the file was mapped
    // as data (the FALSE parameter below is the value of the parameter
    // MappedAsImage).
    DataImportDescr = (PIMAGE_IMPORT_DESCRIPTOR)RtlImageDirectoryEntryToData(
                        FileBase,
			FALSE,
                        IMAGE_DIRECTORY_ENTRY_IMPORT,
                        &ImportSize);

    // Get the address of the import descriptor as if the file was mapped
    // as an image (MappedAsImage = TRUE).
    ImageImportDescr = (PIMAGE_IMPORT_DESCRIPTOR)RtlImageDirectoryEntryToData(
        FileBase,
	TRUE,
        IMAGE_DIRECTORY_ENTRY_IMPORT,
        &ImportSize);

    // The preferred import base offset is ImageImportDescr - FileBase
    // (RVA)
    //
    PreferredImportBase = (ULONG)ImageImportDescr-(ULONG)FileBase;

    // Make sure it is positive;  it's a ULONG.
    //
    if (PreferredImportBase> MAX_ULONG) {
	PreferredImportBase = (-(INT)PreferredImportBase);
    }

    if (DataImportDescr) {
        printf("%s imports:\n",File);

        // Keep the import base around
        //
        DataImportBase = (ULONG)DataImportDescr;

        // Go through the import names and check to see if the name
        // should be changed by comparing it the the "new import" list
        //
        while (DataImportDescr->Name && DataImportDescr->FirstThunk) {

            // Actual import name address is
            //    (Name - PreferredImportBase) +
            //    ActualImportBase(added below).
            //
            // RVA - RVA
            //
            ImportName = (DataImportDescr->Name - PreferredImportBase);

            // Make sure it's positive
            //
            if (ImportName > MAX_ULONG) {
		 ImportName = (-(INT)ImportName);
            }

            // Add the actual import base
            //
            ImportName += DataImportBase;

            if ( (pchDot = strchr((CHAR *)ImportName, '.')) == NULL ) {
                ImportNameLen = strlen((CHAR *)ImportName);
            }
            else {
                ImportNameLen = abs((int)((ULONG)pchDot - ImportName));
            }

            printf("\t%-15s",ImportName);
            for (iNewImp = 0; iNewImp < cNewImports; iNewImp++) {

               // New imports must match in length and in all chars
               // except for the first -- i.e. looking for "*mport" to
               // match "import"
               //
               if ((ImportNameLen == strlen(apszNewImports[iNewImp])) &&
                   (!_strnicmp((CHAR *)ImportName+1, apszNewImports[iNewImp]+1,
                             ImportNameLen-1))) {
                   strncpy((CHAR *)ImportName, apszNewImports[iNewImp],1);
                   BoolError = FlushViewOfFile((PVOID)ImportName, 1);
                   printf(" --> changed to %s",ImportName);
                   break;
               }
            }
            printf("\n");

            // Go to next import descriptor
            //
            ++DataImportDescr;
        }
    }
    else {
        printf("%s has no imports\n",File);
        printf("Done\n\n\n");
    }

    
    //
    // If the file is being update, then recompute the checksum (see sdktools\bind\bind.c)
    //

    NtHeaders = RtlImageNtHeader(FileBase);

    NtHeaders->OptionalHeader.CheckSum = 0;
    CheckSumMappedFile(
                FileBase,
                GetFileSize(hFile, NULL),
                &HeaderSum,
                &CheckSum
                );

    NtHeaders->OptionalHeader.CheckSum = CheckSum;

    
    // Unmap view of file to save changes
    //
    BoolError = UnmapViewOfFile(FileBase);
    if (!BoolError) {
        DoError(FAIL_UNMAP,NULL);
    }

    // Close handle to map-object
    //
    BoolError = CloseHandle(mFile);
    if (!BoolError) {
        DoError(FAIL_CLOSE,NULL);
    }

    // Close file handle
    //
    BoolError = CloseHandle(hFile);
    if (!BoolError) {
        DoError(FAIL_CLOSE,NULL);
    }

    // Reset the file attributes
    //
    BoolError = SetFileAttributes(File, OldAttributes);
    if (!BoolError) {
        DoError(FAIL_RESETATTRIBUTES,File);
    }

} /* ConvertImports () */