/// doesn't work on Win7 :(
void Apep::fullscreen(bool full)
{
    SetConsoleDisplayMode(tout, full? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE, nullptr);
}