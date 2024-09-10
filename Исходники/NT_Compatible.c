void _setcursortype(int cur_t)
{
    CONSOLE_CURSOR_INFO  ConsoleCursorInfo;

    if (!StdHandle)
    {
        StdHandle = TRUE;
        hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
    } /* endif */

    switch (cur_t)
    {
    case _NORMALCURSOR:
    case _SOLIDCURSOR:
        GetConsoleCursorInfo (hStdout, &ConsoleCursorInfo);
        ConsoleCursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo (hStdout, &ConsoleCursorInfo);
        break;

    case _NOCURSOR:
        GetConsoleCursorInfo (hStdout, &ConsoleCursorInfo);
        ConsoleCursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo (hStdout, &ConsoleCursorInfo);
        break;

    } /* endswitch */
}