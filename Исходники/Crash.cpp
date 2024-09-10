static bool OnCrash(const wchar_t * dumpPath,
                    const wchar_t * miniDumpId,
                    void * context,
                    EXCEPTION_POINTERS * exinfo,
                    MDRawAssertionInfo * assertion,
                    bool succeeded)
{
    if (!succeeded)
    {
        constexpr const char * DumpFailedMessage = "Failed to create the dump. Please file an issue with OpenRCT2 on GitHub and provide latest save, and provide information about what you did before the crash occured.";
        printf("%s\n", DumpFailedMessage);
        if (!gOpenRCT2SilentBreakpad)
        {
            MessageBoxA(NULL, DumpFailedMessage, OPENRCT2_NAME, MB_OK | MB_ICONERROR);
        }
        return succeeded;
    }

    // Get filenames
    wchar_t dumpFilePath[MAX_PATH];
    wchar_t saveFilePath[MAX_PATH];
    swprintf_s(dumpFilePath, sizeof(dumpFilePath), L"%s%s.dmp", dumpPath, miniDumpId);
    swprintf_s(saveFilePath, sizeof(saveFilePath), L"%s%s.sv6", dumpPath, miniDumpId);

    // Try to rename the files
    wchar_t dumpFilePathNew[MAX_PATH];
    swprintf_s(dumpFilePathNew, sizeof(dumpFilePathNew), L"%s%s(%s_%s).dmp", dumpPath, miniDumpId, _wszCommitSha1Short, _wszArchitecture);
    if (_wrename(dumpFilePath, dumpFilePathNew) == 0)
    {
        std::wcscpy(dumpFilePath, dumpFilePathNew);
    }

    // Log information to output
    wprintf(L"Dump Path: %s\n", dumpPath);
    wprintf(L"Dump File Path: %s\n", dumpFilePath);
    wprintf(L"Dump Id: %s\n", miniDumpId);
    wprintf(L"Version: %s\n", WSZ(OPENRCT2_VERSION));
    wprintf(L"Commit: %s\n", _wszCommitSha1Short);

    utf8 * saveFilePathUTF8 = widechar_to_utf8(saveFilePath);
    SDL_RWops * rw = SDL_RWFromFile(saveFilePathUTF8, "wb+");
    free(saveFilePathUTF8);

    bool savedGameDumped = false;
    if (rw != NULL) {
        scenario_save(rw, 0x80000000);
        savedGameDumped = true;
        SDL_RWclose(rw);
    }

    if (gOpenRCT2SilentBreakpad)
    {
        return succeeded;
    }
    constexpr const wchar_t * MessageFormat = L"A crash has occurred and a dump was created at\n%s.\n\nPlease file an issue with OpenRCT2 on GitHub, and provide the dump and saved game there.\n\nVersion: %s\nCommit: %s";
    wchar_t message[MAX_PATH * 2];
    swprintf_s(message,
               MessageFormat,
               dumpFilePath,
               WSZ(OPENRCT2_VERSION),
               _wszCommitSha1Short);

    // Cannot use platform_show_messagebox here, it tries to set parent window already dead.
    MessageBoxW(NULL, message, WSZ(OPENRCT2_NAME), MB_OK | MB_ICONERROR);
    HRESULT coInitializeResult = CoInitialize(NULL);
    if (SUCCEEDED(coInitializeResult))
    {
        LPITEMIDLIST pidl = ILCreateFromPathW(dumpPath);
        LPITEMIDLIST files[2];
        uint32 numFiles = 0;

        files[numFiles++] = ILCreateFromPathW(dumpFilePath);
        if (savedGameDumped)
        {
            files[numFiles++] = ILCreateFromPathW(saveFilePath);
        }
        if (pidl != nullptr) {
            HRESULT result = SHOpenFolderAndSelectItems(pidl, numFiles, (LPCITEMIDLIST *)files, 0);
            ILFree(pidl);
            for (uint32 i = 0; i < numFiles; i++)
            {
                ILFree(files[i]);
            }
        }
        CoUninitialize();
    }

    // Return whether the dump was successful
    return succeeded;
}