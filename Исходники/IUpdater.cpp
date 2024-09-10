int main(int argc, char *argv[])
{
    KLUPD::CoreError result = KLUPD::CORE_ADMKIT_FAILURE;

    IniConfiguration iniConfiguration;
    if(iniConfiguration.parse(argc, argv))
    {
        if(iniConfiguration.writeDump())
        {
            MiniDumper::enable();
            if(iniConfiguration.suppressErrorDialog())
                MiniDumper::suppressErrorDialog();
        }

        // protection against multiple instances
        #if defined(UNICODE) || defined(_UNICODE)
            #ifdef WSTRING_SUPPORTED
                HANDLE h = CreateMutex(0, FALSE, KLUPD::asciiToWideChar(iniConfiguration.applicaitonInstanceMutexName()).c_str());
            #else
                HANDLE h = CreateMutexA(0, FALSE, iniConfiguration.applicaitonInstanceMutexName().c_str());
            #endif
        #else
                HANDLE h = CreateMutex(0, FALSE, iniConfiguration.applicaitonInstanceMutexName().c_str());
        #endif

        // there is already an instance of this application running, or failed to create mutex
        if(!h || (GetLastError() == ERROR_ALREADY_EXISTS))
        {
            // TODO: change to code: failed to run several updater instances
        }
        else
            result = mainLoop(iniConfiguration);

        if(h)
            CloseHandle(h);
    }

    // writing single line result report to file
    KLUPD::AutoStream resultFile(0);
    const KLUPD::CoreError openResultFileResult = resultFile.open(iniConfiguration.updateReadableResultFileName(), L"w");
    if(isSuccess(openResultFileResult))
    {
        #ifdef WSTRING_SUPPORTED
            fwprintf(resultFile.stream(), L"%d\n%s", result, KLUPD::toString(result).toWideChar());
        #else
            fprintf(resultFile.stream(), "%d\n%s", result, KLUPD::toString(result).toAscii());
        #endif
    }
    else
    {
        std::cerr << "Failed to open trace file '" << iniConfiguration.updateReadableResultFileName().toAscii()
            << "', result " << KLUPD::toString(openResultFileResult).toAscii();
    }

    return result;
}