void lConsole::ChangeWindowsize(uint16_t Width, uint16_t Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get handle.
    SetConsoleScreenBufferSize(Handle, coord);            // Set buffer size.
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set window size.
}