void removeCursor(void)
{
    CONSOLE_CURSOR_INFO cur;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
    cur.bVisible=0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
}