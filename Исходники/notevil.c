VOID
WriteStringAt(LPWSTR lpString,
              COORD  xy,
              WORD   wColor)
{
    DWORD cWritten = 0;
    WORD  wLen;

    if (!lpString || *lpString == 0) return;

    wLen = wcslen(lpString);

    /* Don't bother writing text when erasing */
    if (wColor)
    {
        WriteConsoleOutputCharacterW(ScreenBuffer,
                                     lpString,
                                     wLen,
                                     xy,
                                     &cWritten);
    }

    FillConsoleOutputAttribute(ScreenBuffer,
                               wColor,
                               wLen,
                               xy,
                               &cWritten);
}