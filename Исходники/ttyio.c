/*
 * Initialization.
 * Set up the video system, and set the keyboard to binary mode.
 * Apparently, OS/2 doesn't allow control-BREAK to be disabled
 * when the keyboard is in binary mode, using signal.
 */
void ttopen()
{
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    CONSOLE_CURSOR_INFO cinfo;

    /* Get handles for console output and input
     */
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    hin =  GetStdHandle(STD_INPUT_HANDLE);

    /* Save current keyboard mode, then disable line editing.
     */
    GetConsoleMode(hin, &conmode);
    SetConsoleMode(hin, 0);         /* disable line mode */

    /* Get screen size.
     */
    if (GetConsoleScreenBufferInfo(hout, &binfo) == TRUE)
    {
	windowrow = binfo.srWindow.Top;
	windowcol = binfo.srWindow.Left;
        nrow = binfo.srWindow.Bottom - windowrow + 1;
        ncol = binfo.srWindow.Right  - windowcol + 1;
    }

    /* Set block cursor
     */
    cinfo.dwSize = 100;     /* make it 100% visible */
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hout, &cinfo);
}