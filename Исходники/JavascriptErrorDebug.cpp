    void JavascriptErrorDebug::SetErrorInfo()
    {
        IErrorInfo * pErrorInfo = GetRestrictedErrorInfo();

        if (!pErrorInfo)
        {
            return;
        }

        ::SetErrorInfo(0L, pErrorInfo);
    }