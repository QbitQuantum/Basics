void OsmAnd::DefaultLogSink::log(const LogSeverityLevel level, const char* format, va_list args)
{
    if (IsDebuggerPresent())
    {
        switch (level)
        {
            case LogSeverityLevel::Verbose:
                OutputDebugStringA("VERBOSE: ");
                break;
            case LogSeverityLevel::Debug:
                OutputDebugStringA("DEBUG: ");
                break;
            case LogSeverityLevel::Info:
                OutputDebugStringA("INFO: ");
                break;
            case LogSeverityLevel::Warning:
                OutputDebugStringA("WARN: ");
                break;
            case LogSeverityLevel::Error:
                OutputDebugStringA("ERROR: ");
                break;
        }

        int len = vsnprintf(nullptr, 0, format, args);
        char* buffer = new char[len + 1];
        vsnprintf(buffer, len, format, args);
        buffer[len] = 0;
        OutputDebugStringA(buffer);
        delete[] buffer;

        OutputDebugStringA("\n");
    }
    else
    {
        //NOTE: This ugly stuff is needed just because Win32 has no _getmode or fcntl API.
        const auto currentMode = _setmode(_fileno(stdout), _O_TEXT);
        if (currentMode != -1)
            _setmode(_fileno(stdout), currentMode);

        if (currentMode == -1 || (currentMode & (_O_U16TEXT | _O_U8TEXT | _O_WTEXT)) == 0)
        {
            switch (level)
            {
                case LogSeverityLevel::Verbose:
                    printf("VERBOSE: ");
                    break;
                case LogSeverityLevel::Debug:
                    printf("DEBUG: ");
                    break;
                case LogSeverityLevel::Info:
                    printf("INFO: ");
                    break;
                case LogSeverityLevel::Warning:
                    printf("WARN: ");
                    break;
                case LogSeverityLevel::Error:
                    printf("ERROR: ");
                    break;
            }

            vprintf(format, args);

            printf("\n");
        }
        else
        {
            switch (level)
            {
                case LogSeverityLevel::Verbose:
                    wprintf(L"VERBOSE: ");
                    break;
                case LogSeverityLevel::Debug:
                    wprintf(L"DEBUG: ");
                    break;
                case LogSeverityLevel::Info:
                    wprintf(L"INFO: ");
                    break;
                case LogSeverityLevel::Warning:
                    wprintf(L"WARN: ");
                    break;
                case LogSeverityLevel::Error:
                    wprintf(L"ERROR: ");
                    break;
            }

            int len = vsnprintf(nullptr, 0, format, args);
            char* buffer = new char[len + 1];
            vsnprintf(buffer, len, format, args);
            buffer[len] = 0;
            wprintf(L"%hs", buffer);

            wprintf(L"\n");
        }
    }
}