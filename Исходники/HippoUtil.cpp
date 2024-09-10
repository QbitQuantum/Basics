void 
hippoDebugLastErr(WCHAR *fmt, ...) 
{
    HippoBSTR str;
    HippoBSTR errstr;
    WCHAR buf[1024];
    HRESULT res = GetLastError();
    va_list vap;
    va_start(vap, fmt);
    StringCchVPrintfW(buf, sizeof(buf) / sizeof(buf[0]), fmt, vap);
    va_end(vap);
    str.Append(buf);
    hippoHresultToString(res, errstr);
    str.Append(errstr);
    MessageBoxW(NULL, str, L"Hippo Debug", MB_OK);
}