    /**
        Log format method.

        \param[in]  item An SCXLogItem to format.
        \returns    A formatted message:
                    "<time> <SEVERITY> [<module>:<linenumber>:<processid>:<threadid>] <message>"
    */
    const std::wstring SCXLogFileBackend::Format(const SCXLogItem& item) const
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

        // JWF -- Try and convert the string.  If this call fails, then we cannot print the string
        const std::wstring in_message(item.GetMessage());
        std::wstring message(in_message);

        bool messageHadUnprintable = false;
        const wchar_t replacementSymbol(L'?');
        for (size_t i = 0; i < in_message.size(); i++)
        {
            wchar_t currentChar = in_message[i];

            if (currentChar < 32 || currentChar > 126)
            {
                message[i] = replacementSymbol;
                messageHadUnprintable = true;
            }
        }
        if (messageHadUnprintable)
        {
            message += L" (* Message contained unprintable (?) characters *)";
        }

        ss << L" [" << item.GetModule() << L":" << item.GetLocation().WhichLine() << L":" << SCXProcess::GetCurrentProcessID() << L":" << item.GetThreadId() << L"] " 
         << message;
         // << item.GetMessage();

        return ss.str();
    }