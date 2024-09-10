void SetLogPathName()
{
    // NOTE: under PAL, we don't get the comand line, so we depend on the random number generator to give us a unique
    // filename.
    WCHAR* OriginalExecutableName =
        GetCommandLineW(); // TODO-Cleanup: not cool to write to the process view of commandline....
    size_t len            = wcslen(OriginalExecutableName);
    WCHAR* ExecutableName = new WCHAR[len + 1];
    wcscpy_s(ExecutableName, len + 1, OriginalExecutableName);
    ExecutableName[len] = W('\0');
    WCHAR* quote1       = NULL;

    // if there are any quotes in filename convert them to spaces.
    while ((quote1 = wcsstr(ExecutableName, W("\""))) != NULL)
        *quote1 = W(' ');

    // remove any illegal or annoying characters from file name by converting them to underscores
    while ((quote1 = wcspbrk(ExecutableName, W("=<>:\"/\\|?! *.,"))) != NULL)
        *quote1 = W('_');

    const WCHAR* DataFileExtension       = W(".mc");
    size_t       ExecutableNameLength    = wcslen(ExecutableName);
    size_t       DataFileExtensionLength = wcslen(DataFileExtension);
    size_t       logPathLength           = wcslen(g_logPath);

    size_t dataFileNameLength = logPathLength + 1 + ExecutableNameLength + 1 + DataFileExtensionLength + 1;

    const size_t MaxAcceptablePathLength =
        MAX_PATH - 20; // subtract 20 to leave buffer, for possible random number addition
    if (dataFileNameLength >= MaxAcceptablePathLength)
    {
        // The path name is too long; creating the file will fail. This can happen because we use the command line,
        // which for ngen includes lots of environment variables, for example.

        // Assume (!) the extra space is all in the ExecutableName, so shorten that.
        ExecutableNameLength -= dataFileNameLength - MaxAcceptablePathLength;

        dataFileNameLength = MaxAcceptablePathLength;
    }

// Always add a random number, just in case the above doesn't give us a unique filename.
#ifdef FEATURE_PAL
    unsigned __int64 randNumber       = 0;
    const size_t     RandNumberLength = sizeof(randNumber) * 2 + 1; // 16 hex digits + null
    WCHAR            RandNumberString[RandNumberLength];
    PAL_Random(&randNumber, sizeof(randNumber));
    swprintf_s(RandNumberString, RandNumberLength, W("%016llX"), randNumber);
#else  // !FEATURE_PAL
    unsigned int randNumber       = 0;
    const size_t RandNumberLength = sizeof(randNumber) * 2 + 1; // 8 hex digits + null
    WCHAR        RandNumberString[RandNumberLength];
    rand_s(&randNumber);
    swprintf_s(RandNumberString, RandNumberLength, W("%08X"), randNumber);
#endif // !FEATURE_PAL

    dataFileNameLength += RandNumberLength - 1;

    // Construct the full pathname we're going to use.
    g_dataFileName    = new WCHAR[dataFileNameLength];
    g_dataFileName[0] = 0;
    wcsncat_s(g_dataFileName, dataFileNameLength, g_logPath, logPathLength);
    wcsncat_s(g_dataFileName, dataFileNameLength, DIRECTORY_SEPARATOR_STR_W, 1);
    wcsncat_s(g_dataFileName, dataFileNameLength, ExecutableName, ExecutableNameLength);

    if (RandNumberLength > 0)
    {
        wcsncat_s(g_dataFileName, dataFileNameLength, RandNumberString, RandNumberLength);
    }

    wcsncat_s(g_dataFileName, dataFileNameLength, DataFileExtension, DataFileExtensionLength);
}