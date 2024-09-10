DWORD CNHSQLServerDBO::ExecuteCount(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnCountNum)
{
    assert(NULL != pConnection);
    assert(NULL != pwchSQL);
    assert(NULL != pnCountNum);

    DWORD dwReturn(0x00);

    try
    {
        _RecordsetPtr pRecordset(NULL);
        if (0x00 == OpenQuery(pConnection, pRecordset, pwchSQL))
        {
            _variant_t v;
            v.ChangeType(VT_NULL);
            CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"CountNum");
            if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
            {
                (*pnCountNum) = static_cast<int>(v);
            }

            CNHSQLServerDBO::CloseQuery(pRecordset);
        }
        else
        {
            dwReturn = 0x01;
        }
    }
    catch (_com_error &e)
    {
//#ifdef _DEBUG
        const int nErrMsgLength(MAX_PATH);
        wchar_t *pwchErrMsg = new wchar_t[nErrMsgLength]();
        _snwprintf_s(pwchErrMsg, nErrMsgLength, _TRUNCATE, L"CNHSQLServerDBO::ExecuteCount发生错误（执行%s）。", pwchSQL);
        // 输出错误信息到输出窗口
        OutputDebugStringW(L"\t");
        OutputDebugStringW(pwchErrMsg);
        OutputDebugStringW(L"\n");
        // 输出错误信息到日志文件
        if (0 != wcscmp(m_wchLogFilePath, L""))
        {
            // 当日志文件路径不为空时，写日志
            CNHLogAPI::WriteLogEx(m_wchLogFilePath, LOG_ERR, L"NHSQLServerDBO", pwchErrMsg);
        }
        if (NULL != pwchErrMsg)
        {
            delete[] pwchErrMsg;
            pwchErrMsg = NULL;
        }
        OutputDBErrMsg(e);
//#endif
        dwReturn = 0xff;
    }

    return dwReturn;
}