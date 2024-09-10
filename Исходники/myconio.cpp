void clreol()
{
  COORD coord = {wherex() - 1 , wherey() - 1};
  DWORD dwWritten;
  HANDLE hScreen=GetStdHandle(STD_OUTPUT_HANDLE) ;
  CONSOLE_SCREEN_BUFFER_INFO Info;

    if(GetConsoleScreenBufferInfo(hScreen, &Info))
    {
        FillConsoleOutputCharacter (hScreen, ' ', Info.dwSize.X-coord.X, coord, 
                        &dwWritten);
        FillConsoleOutputAttribute (hScreen, Info.wAttributes, 
                        Info.dwSize.X-coord.X, coord, &dwWritten);
        gotoxy (coord.X, coord.Y) ;
    }  
}