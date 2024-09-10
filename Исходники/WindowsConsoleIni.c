/**
* @brief (Only for Windows and for newer WINAPI) Sets the Console font size to the defined FontSize_X and FontSize_Y
* @param [in] FontSize defined font size informations
*/
void SetConsoleFont(SIZES FontSize) {
#if !defined(WINXP) && !defined(BASIGMINGW) /* Minimum supported client: Windows Vista */
    HANDLE outcon;
    CONSOLE_FONT_INFOEX font;

    outcon = GetStdHandle(STD_OUTPUT_HANDLE);      /* Getting windows console standard handler */
    font = {sizeof(CONSOLE_FONT_INFOEX)};          /* CONSOLE_FONT_INFOEX is defined in some windows header */
    GetCurrentConsoleFontEx(outcon, false, &font); /* Getting current font settings */
    font.FontFamily = 54;       /* Lucida console font */
    font.dwFontSize.X = FontSize.X;
    font.dwFontSize.Y = FontSize.Y;
    SetCurrentConsoleFontEx(outcon, false, &font); /* Setting font settings */
#endif /* WINXP, BASIGMINGW */
}