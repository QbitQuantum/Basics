UT_UTF8String AP_Win32Dialog_GenericInput::_getText(HWND hWnd, int nID)
{
    UT_return_val_if_fail(hWnd, UT_UTF8String());

    const int buflen = 4096;
    char szBuff[buflen];
    *szBuff=0;
    GetDlgItemTextA(hWnd, nID, szBuff, buflen);
    szBuff[buflen-1] = '\0';
    return AP_Win32App::s_fromWinLocaleToUTF8(szBuff);
}