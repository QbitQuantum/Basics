int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
#ifdef UNDER_CE
                     LPWSTR
#else
                     LPSTR
#endif
                     lpCmdLine, int nCmdShow)
#endif
{
    CFileInStream archiveStream;
    CLookToRead lookStream;
    CSzArEx db;
    SRes res = SZ_OK;
    ISzAlloc allocImp;
    ISzAlloc allocTempImp;
    WCHAR sfxPath[MAX_PATH + 2];
    WCHAR path[MAX_PATH * 3 + 2];
    size_t pathLen;
    DWORD winRes;
    const wchar_t *cmdLineParams;
    const char *errorMessage = NULL;
    Bool useShellExecute = True;

#ifdef _CONSOLE
    SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#else
    hInstance = hInstance;
    hPrevInstance = hPrevInstance;
    lpCmdLine = lpCmdLine;
    nCmdShow = nCmdShow;
#endif

    CrcGenerateTable();

    allocImp.Alloc = SzAlloc;
    allocImp.Free = SzFree;

    allocTempImp.Alloc = SzAllocTemp;
    allocTempImp.Free = SzFreeTemp;

    FileInStream_CreateVTable(&archiveStream);
    LookToRead_CreateVTable(&lookStream, False);

    winRes = GetModuleFileNameW(NULL, sfxPath, MAX_PATH);
    if (winRes == 0 || winRes > MAX_PATH)
        return 1;
    {
        cmdLineParams = GetCommandLineW();
#ifndef UNDER_CE
        {
            Bool quoteMode = False;
            for (;; cmdLineParams++)
            {
                wchar_t c = *cmdLineParams;
                if (c == L'\"')
                    quoteMode = !quoteMode;
                else if (c == 0 || (c == L' ' && !quoteMode))
                    break;
            }
        }
#endif
    }

    {
        unsigned i;
        DWORD d;
        winRes = GetTempPathW(MAX_PATH, path);
        if (winRes == 0 || winRes > MAX_PATH)
            return 1;
        pathLen = wcslen(path);
        d = (GetTickCount() << 12) ^ (GetCurrentThreadId() << 14) ^ GetCurrentProcessId();
        for (i = 0;; i++, d += GetTickCount())
        {
            if (i >= 100)
            {
                res = SZ_ERROR_FAIL;
                break;
            }
            wcscpy(path + pathLen, L"7z");

            {
                wchar_t *s = path + wcslen(path);
                UInt32 value = d;
                unsigned k;
                for (k = 0; k < 8; k++)
                {
                    unsigned t = value & 0xF;
                    value >>= 4;
                    s[7 - k] = (char)((t < 10) ? ('0' + t) : ('A' + (t - 10)));
                }
                s[k] = '\0';
            }

            if (DoesFileOrDirExist(path))
                continue;
            if (CreateDirectoryW(path, NULL))
            {
                wcscat(path, L"\\");
                pathLen = wcslen(path);
                break;
            }
            if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
                res = SZ_ERROR_FAIL;
                break;
            }
        }
        if (res != SZ_OK)
            errorMessage = "Can't create temp folder";
    }

    if (res != SZ_OK)
    {
        if (!errorMessage)
            errorMessage = "Error";
        PrintErrorMessage(errorMessage);
        return 1;
    }

    if (InFile_OpenW(&archiveStream.file, sfxPath) != 0)
    {
        errorMessage = "can not open input file";
        res = SZ_ERROR_FAIL;
    }
    else
    {
        UInt64 pos = 0;
        if (!FindSignature(&archiveStream.file, &pos))
            res = SZ_ERROR_FAIL;
        else if (File_Seek(&archiveStream.file, (Int64 *)&pos, SZ_SEEK_SET) != 0)
            res = SZ_ERROR_FAIL;
        if (res != 0)
            errorMessage = "Can't find 7z archive";
    }

    if (res == SZ_OK)
    {
        lookStream.realStream = &archiveStream.s;
        LookToRead_Init(&lookStream);
    }

    SzArEx_Init(&db);
    if (res == SZ_OK)
    {
        res = SzArEx_Open(&db, &lookStream.s, &allocImp, &allocTempImp);
    }
    if (res == SZ_OK)
    {
        UInt32 executeFileIndex = (UInt32)(Int32)-1;
        UInt32 minPrice = 1 << 30;
        UInt32 i;
        UInt32 blockIndex = 0xFFFFFFFF; /* it can have any value before first call (if outBuffer = 0) */
        Byte *outBuffer = 0; /* it must be 0 before first call for each new archive. */
        size_t outBufferSize = 0;  /* it can have any value before first call (if outBuffer = 0) */

        for (i = 0; i < db.db.NumFiles; i++)
        {
            size_t offset = 0;
            size_t outSizeProcessed = 0;
            const CSzFileItem *f = db.db.Files + i;
            size_t len;
            WCHAR *temp;
            len = SzArEx_GetFileNameUtf16(&db, i, NULL);

            if (len >= MAX_PATH)
            {
                res = SZ_ERROR_FAIL;
                break;
            }

            temp = path + pathLen;

            SzArEx_GetFileNameUtf16(&db, i, temp);
            {
                res = SzArEx_Extract(&db, &lookStream.s, i,
                                     &blockIndex, &outBuffer, &outBufferSize,
                                     &offset, &outSizeProcessed,
                                     &allocImp, &allocTempImp);
                if (res != SZ_OK)
                    break;
            }
            {
                CSzFile outFile;
                size_t processedSize;
                size_t j;
                size_t nameStartPos = 0;
                for (j = 0; temp[j] != 0; j++)
                {
                    if (temp[j] == '/')
                    {
                        temp[j] = 0;
                        MyCreateDir(path);
                        temp[j] = CHAR_PATH_SEPARATOR;
                        nameStartPos = j + 1;
                    }
                }

                if (f->IsDir)
                {
                    MyCreateDir(path);
                    continue;
                }
                else
                {
                    unsigned extLen;
                    const WCHAR *name = temp + nameStartPos;
                    unsigned len = (unsigned)wcslen(name);
                    unsigned nameLen = FindExt(temp + nameStartPos, &extLen);
                    unsigned extPrice = FindItem(kExts, sizeof(kExts) / sizeof(kExts[0]), name + len - extLen, extLen);
                    unsigned namePrice = FindItem(kNames, sizeof(kNames) / sizeof(kNames[0]), name, nameLen);

                    unsigned price = namePrice + extPrice * 64 + (nameStartPos == 0 ? 0 : (1 << 12));
                    if (minPrice > price)
                    {
                        minPrice = price;
                        executeFileIndex = i;
                        useShellExecute = (extPrice != k_EXE_ExtIndex);
                    }

                    if (DoesFileOrDirExist(path))
                    {
                        errorMessage = "Duplicate file";
                        res = SZ_ERROR_FAIL;
                        break;
                    }
                    if (OutFile_OpenW(&outFile, path))
                    {
                        errorMessage = "Can't open output file";
                        res = SZ_ERROR_FAIL;
                        break;
                    }
                }
                processedSize = outSizeProcessed;
                if (File_Write(&outFile, outBuffer + offset, &processedSize) != 0 || processedSize != outSizeProcessed)
                {
                    errorMessage = "Can't write output file";
                    res = SZ_ERROR_FAIL;
                }

#ifdef USE_WINDOWS_FILE
                if (f->MTimeDefined)
                {
                    FILETIME mTime;
                    mTime.dwLowDateTime = f->MTime.Low;
                    mTime.dwHighDateTime = f->MTime.High;
                    SetFileTime(outFile.handle, NULL, NULL, &mTime);
                }
#endif

                {
                    SRes res2 = File_Close(&outFile);
                    if (res != SZ_OK)
                        break;
                    if (res2 != SZ_OK)
                    {
                        res = res2;
                        break;
                    }
                }
#ifdef USE_WINDOWS_FILE
                if (f->AttribDefined)
                    SetFileAttributesW(path, f->Attrib);
#endif
            }
        }

        if (res == SZ_OK)
        {
            if (executeFileIndex == (UInt32)(Int32)-1)
            {
                errorMessage = "There is no file to execute";
                res = SZ_ERROR_FAIL;
            }
            else
            {
                WCHAR *temp = path + pathLen;
                UInt32 j;
                SzArEx_GetFileNameUtf16(&db, executeFileIndex, temp);
                for (j = 0; temp[j] != 0; j++)
                    if (temp[j] == '/')
                        temp[j] = CHAR_PATH_SEPARATOR;
            }
        }
        IAlloc_Free(&allocImp, outBuffer);
    }
    SzArEx_Free(&db, &allocImp);

    File_Close(&archiveStream.file);

    if (res == SZ_OK)
    {
        HANDLE hProcess = 0;
        if (useShellExecute)
        {
            SHELLEXECUTEINFO ei;
            UINT32 executeRes;
            BOOL success;

            memset(&ei, 0, sizeof(ei));
            ei.cbSize = sizeof(ei);
            ei.lpFile = path;
            ei.fMask = SEE_MASK_NOCLOSEPROCESS
#ifndef UNDER_CE
                       | SEE_MASK_FLAG_DDEWAIT
#endif
                       /* | SEE_MASK_NO_CONSOLE */
                       ;
            if (wcslen(cmdLineParams) != 0)
                ei.lpParameters = cmdLineParams;
            ei.nShow = SW_SHOWNORMAL; /* SW_HIDE; */
            success = ShellExecuteEx(&ei);
            executeRes = (UINT32)(UINT_PTR)ei.hInstApp;
            if (!success || (executeRes <= 32 && executeRes != 0))  /* executeRes = 0 in Windows CE */
                res = SZ_ERROR_FAIL;
            else
                hProcess = ei.hProcess;
        }
        else
        {
            STARTUPINFOW si;
            PROCESS_INFORMATION pi;
            WCHAR cmdLine[MAX_PATH * 3];

            wcscpy(cmdLine, path);
            wcscat(cmdLine, cmdLineParams);
            memset(&si, 0, sizeof(si));
            si.cb = sizeof(si);
            if (CreateProcessW(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0)
                res = SZ_ERROR_FAIL;
            else
            {
                CloseHandle(pi.hThread);
                hProcess = pi.hProcess;
            }
        }
        if (hProcess != 0)
        {
            WaitForSingleObject(hProcess, INFINITE);
            CloseHandle(hProcess);
        }
    }

    path[pathLen] = L'\0';
    RemoveDirWithSubItems(path);

    if (res == SZ_OK)
        return 0;

    {
        if (res == SZ_ERROR_UNSUPPORTED)
            errorMessage = "Decoder doesn't support this archive";
        else if (res == SZ_ERROR_MEM)
            errorMessage = "Can't allocate required memory";
        else if (res == SZ_ERROR_CRC)
            errorMessage = "CRC error";
        else
        {
            if (!errorMessage)
                errorMessage = "ERROR";
        }
        if (errorMessage)
            PrintErrorMessage(errorMessage);
    }
    return 1;
}