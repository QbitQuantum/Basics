        void AddLog(const wchar_t* lpFormat, ...)
        {
            const int nBufLen = MAX_PATH * 2;
            wchar_t szBuf[nBufLen + 1] = {0};
            va_list ap;
            va_start(ap, lpFormat);
            StringCchVPrintfW(szBuf, nBufLen, lpFormat, ap);
            va_end(ap);
            OutputDebugStringW(szBuf);

            std::wstring sLine = GetTimeHeader();
            sLine.append(szBuf);
            std::string sLineA = CW2A(sLine.c_str(), CP_UTF8).m_psz;
            AddMsgToList(sLineA);
        }