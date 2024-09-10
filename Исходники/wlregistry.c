BOOLEAN
WinLdrLoadNLSData(IN OUT PLOADER_PARAMETER_BLOCK LoaderBlock,
                  IN LPCSTR DirectoryPath,
                  IN LPCSTR AnsiFileName,
                  IN LPCSTR OemFileName,
                  IN LPCSTR LanguageFileName)
{
    CHAR FileName[255];
    ULONG AnsiFileId;
    ULONG OemFileId;
    ULONG LanguageFileId;
    ULONG AnsiFileSize, OemFileSize, LanguageFileSize;
    ULONG TotalSize;
    ULONG_PTR NlsDataBase;
    PVOID NlsVirtual;
    BOOLEAN AnsiEqualsOem = FALSE;
    FILEINFORMATION FileInfo;
    ULONG BytesRead;
    ARC_STATUS Status;

    /* There may be a case, when OEM and ANSI page coincide */
    if (!strcmp(AnsiFileName, OemFileName))
        AnsiEqualsOem = TRUE;

    /* Open file with ANSI and store its size */
    //Print(L"Loading %s...\n", Filename);
    strcpy(FileName, DirectoryPath);
    strcat(FileName, AnsiFileName);
    Status = ArcOpen(FileName, OpenReadOnly, &AnsiFileId);
    if (Status != ESUCCESS)
        goto Failure;

    Status = ArcGetFileInformation(AnsiFileId, &FileInfo);
    if (Status != ESUCCESS)
        goto Failure;
    AnsiFileSize = FileInfo.EndingAddress.LowPart;
    TRACE("AnsiFileSize: %d\n", AnsiFileSize);
    ArcClose(AnsiFileId);

    /* Open OEM file and store its length */
    if (AnsiEqualsOem)
    {
        OemFileSize = 0;
    }
    else
    {
        //Print(L"Loading %s...\n", Filename);
        strcpy(FileName, DirectoryPath);
        strcat(FileName, OemFileName);
        Status = ArcOpen(FileName, OpenReadOnly, &OemFileId);
        if (Status != ESUCCESS)
            goto Failure;

        Status = ArcGetFileInformation(OemFileId, &FileInfo);
        if (Status != ESUCCESS)
            goto Failure;
        OemFileSize = FileInfo.EndingAddress.LowPart;
        ArcClose(OemFileId);
    }
    TRACE("OemFileSize: %d\n", OemFileSize);

    /* And finally open the language codepage file and store its length */
    //Print(L"Loading %s...\n", Filename);
    strcpy(FileName, DirectoryPath);
    strcat(FileName, LanguageFileName);
    Status = ArcOpen(FileName, OpenReadOnly, &LanguageFileId);
    if (Status != ESUCCESS)
        goto Failure;

    Status = ArcGetFileInformation(LanguageFileId, &FileInfo);
    if (Status != ESUCCESS)
        goto Failure;
    LanguageFileSize = FileInfo.EndingAddress.LowPart;
    ArcClose(LanguageFileId);
    TRACE("LanguageFileSize: %d\n", LanguageFileSize);

    /* Sum up all three length, having in mind that every one of them
       must start at a page boundary => thus round up each file to a page */
    TotalSize = MM_SIZE_TO_PAGES(AnsiFileSize) +
        MM_SIZE_TO_PAGES(OemFileSize)  +
        MM_SIZE_TO_PAGES(LanguageFileSize);

    /* Store it for later marking the pages as NlsData type */
    TotalNLSSize = TotalSize;

    NlsDataBase = (ULONG_PTR)MmAllocateMemoryWithType(TotalSize*MM_PAGE_SIZE, LoaderNlsData);

    if (NlsDataBase == 0)
        goto Failure;

    NlsVirtual = PaToVa((PVOID)NlsDataBase);
    LoaderBlock->NlsData->AnsiCodePageData = NlsVirtual;
    LoaderBlock->NlsData->OemCodePageData = (PVOID)((PUCHAR)NlsVirtual +
        (MM_SIZE_TO_PAGES(AnsiFileSize) << MM_PAGE_SHIFT));
    LoaderBlock->NlsData->UnicodeCodePageData = (PVOID)((PUCHAR)NlsVirtual +
        (MM_SIZE_TO_PAGES(AnsiFileSize) << MM_PAGE_SHIFT) +
        (MM_SIZE_TO_PAGES(OemFileSize) << MM_PAGE_SHIFT));

    /* Ansi and OEM data are the same - just set pointers to the same area */
    if (AnsiEqualsOem)
        LoaderBlock->NlsData->OemCodePageData = LoaderBlock->NlsData->AnsiCodePageData;


    /* Now actually read the data into memory, starting with Ansi file */
    strcpy(FileName, DirectoryPath);
    strcat(FileName, AnsiFileName);
    Status = ArcOpen(FileName, OpenReadOnly, &AnsiFileId);
    if (Status != ESUCCESS)
        goto Failure;

    Status = ArcRead(AnsiFileId, VaToPa(LoaderBlock->NlsData->AnsiCodePageData), AnsiFileSize, &BytesRead);
    if (Status != ESUCCESS)
        goto Failure;

    ArcClose(AnsiFileId);

    /* OEM now, if it doesn't equal Ansi of course */
    if (!AnsiEqualsOem)
    {
        strcpy(FileName, DirectoryPath);
        strcat(FileName, OemFileName);
        Status = ArcOpen(FileName, OpenReadOnly, &OemFileId);
        if (Status != ESUCCESS)
            goto Failure;

        Status = ArcRead(OemFileId, VaToPa(LoaderBlock->NlsData->OemCodePageData), OemFileSize, &BytesRead);
        if (Status != ESUCCESS)
            goto Failure;

        ArcClose(OemFileId);
    }

    /* finally the language file */
    strcpy(FileName, DirectoryPath);
    strcat(FileName, LanguageFileName);
    Status = ArcOpen(FileName, OpenReadOnly, &LanguageFileId);
    if (Status != ESUCCESS)
        goto Failure;

    Status = ArcRead(LanguageFileId, VaToPa(LoaderBlock->NlsData->UnicodeCodePageData), LanguageFileSize, &BytesRead);
    if (Status != ESUCCESS)
        goto Failure;

    ArcClose(LanguageFileId);

    //
    // THIS IS HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACK
    // Should go to WinLdrLoadOemHalFont(), when it will be implemented
    //
    LoaderBlock->OemFontFile = VaToPa(LoaderBlock->NlsData->UnicodeCodePageData);

    /* Convert NlsTables address to VA */
    LoaderBlock->NlsData = PaToVa(LoaderBlock->NlsData);

    return TRUE;

Failure:
    UiMessageBox("Error reading NLS file %s", FileName);
    return FALSE;
}