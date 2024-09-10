    /**
        Log format method.

        \param[in]  item An SCXLogItem to format.
        \returns    A formatted message:
                    "<time> <SEVERITY> [<module>:<linenumber>:<processid>:<threadid>] <message>"
    */
    const std::wstring SCXLogStdoutBackend::Format(const SCXLogItem& item) const
    {
        static const wchar_t* severityStrings[] = {
            L"NotSet    ",
            L"Hysterical",
            L"Trace     ",
            L"Info      ",
            L"Warning   ",
            L"Error     "
        };

        std::wstringstream ss;

        ss << item.GetTimestamp().ToExtendedISO8601() << L" ";

        if (item.GetSeverity() > eError)
        {
            ss << L"Unknown " << item.GetSeverity();
        }
        else
        {
            ss << severityStrings[item.GetSeverity()];
        }

        ss << L" [" << item.GetModule() << L":" << item.GetLocation().WhichLine() << L":" << SCXProcess::GetCurrentProcessID() << L":" << item.GetThreadId() << L"] " << item.GetMessage();

        return ss.str();
    }