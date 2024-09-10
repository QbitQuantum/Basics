//
// Tries to call where.exe to find the location of dotnet.exe.
// Will check that the bitness of dotnet matches the current
// worker process bitness.
// Returns true if a valid dotnet was found, else false.R
//
std::optional<fs::path>
HOSTFXR_UTILITY::InvokeWhereToFindDotnet()
{
    HRESULT             hr = S_OK;
    // Arguments to call where.exe
    STARTUPINFOW        startupInfo = { 0 };
    PROCESS_INFORMATION processInformation = { 0 };
    SECURITY_ATTRIBUTES securityAttributes;

    CHAR                pzFileContents[READ_BUFFER_SIZE];
    HandleWrapper<InvalidHandleTraits>     hStdOutReadPipe;
    HandleWrapper<InvalidHandleTraits>     hStdOutWritePipe;
    HandleWrapper<InvalidHandleTraits>     hProcess;
    HandleWrapper<InvalidHandleTraits>     hThread;
    CComBSTR            pwzDotnetName = NULL;
    DWORD               dwFilePointer;
    BOOL                fIsWow64Process;
    BOOL                fIsCurrentProcess64Bit;
    DWORD               dwExitCode;
    STRU                struDotnetSubstring;
    STRU                struDotnetLocationsString;
    DWORD               dwNumBytesRead;
    DWORD               dwBinaryType;
    INT                 index = 0;
    INT                 prevIndex = 0;
    std::optional<fs::path> result;

    // Set the security attributes for the read/write pipe
    securityAttributes.nLength = sizeof(securityAttributes);
    securityAttributes.lpSecurityDescriptor = NULL;
    securityAttributes.bInheritHandle = TRUE;

    LOG_INFO(L"Invoking where.exe to find dotnet.exe");

    // Create a read/write pipe that will be used for reading the result of where.exe
    FINISHED_LAST_ERROR_IF(!CreatePipe(&hStdOutReadPipe, &hStdOutWritePipe, &securityAttributes, 0));
    FINISHED_LAST_ERROR_IF(!SetHandleInformation(hStdOutReadPipe, HANDLE_FLAG_INHERIT, 0));

    // Set the stdout and err pipe to the write pipes.
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;
    startupInfo.hStdOutput = hStdOutWritePipe;
    startupInfo.hStdError = hStdOutWritePipe;

    // CreateProcess requires a mutable string to be passed to commandline
    // See https://blogs.msdn.microsoft.com/oldnewthing/20090601-00/?p=18083/
    pwzDotnetName = L"\"where.exe\" dotnet.exe";

    // Create a process to invoke where.exe
    FINISHED_LAST_ERROR_IF(!CreateProcessW(NULL,
        pwzDotnetName,
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &startupInfo,
        &processInformation
    ));

    // Store handles into wrapper so they get closed automatically
    hProcess = processInformation.hProcess;
    hThread = processInformation.hThread;

    // Wait for where.exe to return
    WaitForSingleObject(processInformation.hProcess, INFINITE);

    //
    // where.exe will return 0 on success, 1 if the file is not found
    // and 2 if there was an error. Check if the exit code is 1 and set
    // a new hr result saying it couldn't find dotnet.exe
    //
    FINISHED_LAST_ERROR_IF (!GetExitCodeProcess(processInformation.hProcess, &dwExitCode));

    //
    // In this block, if anything fails, we will goto our fallback of
    // looking in C:/Program Files/
    //
    if (dwExitCode != 0)
    {
        FINISHED_IF_FAILED(E_FAIL);
    }

    // Where succeeded.
    // Reset file pointer to the beginning of the file.
    dwFilePointer = SetFilePointer(hStdOutReadPipe, 0, NULL, FILE_BEGIN);
    if (dwFilePointer == INVALID_SET_FILE_POINTER)
    {
        FINISHED_IF_FAILED(E_FAIL);
    }

    //
    // As the call to where.exe succeeded (dotnet.exe was found), ReadFile should not hang.
    // TODO consider putting ReadFile in a separate thread with a timeout to guarantee it doesn't block.
    //
    FINISHED_LAST_ERROR_IF (!ReadFile(hStdOutReadPipe, pzFileContents, READ_BUFFER_SIZE, &dwNumBytesRead, NULL));

    if (dwNumBytesRead >= READ_BUFFER_SIZE)
    {
        // This shouldn't ever be this large. We could continue to call ReadFile in a loop,
        // however if someone had this many dotnet.exes on their machine.
        FINISHED_IF_FAILED(E_FAIL);
    }

    FINISHED_IF_FAILED(struDotnetLocationsString.CopyA(pzFileContents, dwNumBytesRead));

    LOG_INFOF(L"where.exe invocation returned: '%ls'", struDotnetLocationsString.QueryStr());

    // Check the bitness of the currently running process
    // matches the dotnet.exe found.
    FINISHED_LAST_ERROR_IF (!IsWow64Process(GetCurrentProcess(), &fIsWow64Process));

    if (fIsWow64Process)
    {
        // 32 bit mode
        fIsCurrentProcess64Bit = FALSE;
    }
    else
    {
        // Check the SystemInfo to see if we are currently 32 or 64 bit.
        SYSTEM_INFO systemInfo;
        GetNativeSystemInfo(&systemInfo);
        fIsCurrentProcess64Bit = systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64;
    }

    LOG_INFOF(L"Current process bitness type detected as isX64=%d", fIsCurrentProcess64Bit);

    while (TRUE)
    {
        index = struDotnetLocationsString.IndexOf(L"\r\n", prevIndex);
        if (index == -1)
        {
            break;
        }

        FINISHED_IF_FAILED(struDotnetSubstring.Copy(&struDotnetLocationsString.QueryStr()[prevIndex], index - prevIndex));
        // \r\n is two wchars, so add 2 here.
        prevIndex = index + 2;

        LOG_INFOF(L"Processing entry '%ls'", struDotnetSubstring.QueryStr());

        if (LOG_LAST_ERROR_IF(!GetBinaryTypeW(struDotnetSubstring.QueryStr(), &dwBinaryType)))
        {
            continue;
        }

        LOG_INFOF(L"Binary type %d", dwBinaryType);

        if (fIsCurrentProcess64Bit == (dwBinaryType == SCS_64BIT_BINARY))
        {
            // The bitness of dotnet matched with the current worker process bitness.
            return std::make_optional(struDotnetSubstring.QueryStr());
        }
    }

    Finished:
    return result;
}