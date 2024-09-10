int WINAPI D3DXDebugAssert(LPCSTR szFile, int nLine, LPCSTR szCondition)
{
    char str[512];

    // Print message to debug console
    StringCchPrintfA(str, sizeof(str), "Assertion failure! (%s %d): %s\r\n", szFile, nLine, szCondition);
    str[511] = 0;
    OutputDebugStringA(str);

    return 0;
}