BOOL WINAPI MyTextOutA(HDC hDC, int nXStart, int nYStart, LPCTSTR lpString, int cbCount)
{
    BOOL    r;
    WCHAR   c, ch[0x100];
    ULONG   CodePage;

    CodePage = CP_GB2312;
    if (cbCount > 2 && IsShiftJISString((PCHAR)lpString, cbCount))
    {
        CodePage = CP_SHIFTJIS;
    }
    else if (cbCount == 2)
    {
        c = *(PWCHAR)lpString;
        switch (c)
        {
            case SWAPCHAR('‘Ρ'):
                ch[0] = 0x266A;
                goto SKIP_CONV;

            default:
                if (IsShiftJISChar(SWAPCHAR(c)))
                    CodePage = CP_SHIFTJIS;
                goto NOT_CHANGE_CHAR;
        }
    }

NOT_CHANGE_CHAR:
    CodePage = MultiByteToWideChar(CodePage, 0, lpString, cbCount, ch, countof(ch));

SKIP_CONV:

    r = TextOutW(hDC, nXStart, nYStart, ch, CodePage);

    return r;
}