void hideConsoleCursor()
{
   HANDLE hOuput = GetStdHandle( STD_OUTPUT_HANDLE );
   CONSOLE_CURSOR_INFO cInfo;
   GetConsoleCursorInfo( hOuput, &cInfo );
   cInfo.bVisible = false;
   SetConsoleCursorInfo( hOuput, &cInfo );
}