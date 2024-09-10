 void clrscr ( void ) // efface l'écran
 {
 HANDLE hstdout = STDOUT;
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 if (GetConsoleScreenBufferInfo (hstdout, &csbi))
 {
     COORD coordScreen = { 0, 0 };
     DWORD cCharsWritten;
     DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
     FillConsoleOutputCharacter (hstdout, ' ', dwConSize, coordScreen, &cCharsWritten);
     FillConsoleOutputAttribute (hstdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
     SetConsoleCursorPosition    (hstdout, coordScreen);
 }
 }