int gotoxy(int x, int y)
{
    COORD cd;
    cd.X = x;cd.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);
}