BOOL IME_SetCompositionString(DWORD dwIndex, LPCVOID lpComp, DWORD dwCompLen,
                              LPCVOID lpRead, DWORD dwReadLen)
{
    return ImeSetCompositionString(FROM_X11, dwIndex, lpComp, dwCompLen,
                                    lpRead, dwReadLen);
}