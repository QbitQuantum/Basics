VOID DXUTOutputDebugStringW(LPCWSTR strMsg, ...)
{
#if defined(DEBUG) || defined(_DEBUG)
    WCHAR strBuffer[512];

    va_list args;
    va_start(args, strMsg);
    StringCchVPrintfW(strBuffer, 512, strMsg, args);
    strBuffer[511] = L'\0';
    va_end(args);

    OutputDebugString(strBuffer);
#else
    UNREFERENCED_PARAMETER(strMsg);
#endif
}