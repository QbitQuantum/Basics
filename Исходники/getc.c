//------------------------------------------------------------------------------
static void simulate_sigwinch()
{
    // In the land of POSIX a terminal would raise a SIGWINCH signal when it is
    // resized. See rl_sigwinch_handler() in readline/signal.c.

    extern int _rl_vis_botlin;
    extern int _rl_last_c_pos;
    extern int _rl_last_v_pos;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD cursor_pos;
    HANDLE handle;
    int cell_count;
    DWORD written;

    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &csbi);

    // If the cursor was outside of the new buffer size, conhost will move it
    // down one line. This needs to be accounted for to prevent artefacts.
    if (_rl_last_c_pos >= csbi.dwSize.X)
        ++_rl_last_v_pos;

    // Move the cursor to the prompt line
    cursor_pos = csbi.dwCursorPosition;
    cursor_pos.Y -= _rl_last_v_pos;
    cursor_pos.X = 0;
    SetConsoleCursorPosition(handle, cursor_pos);

    // Clear the buffer used by the line previously.
    cell_count = csbi.dwSize.X * (_rl_vis_botlin + 1);
    FillConsoleOutputCharacterW(handle, ' ', cell_count, cursor_pos, &written);
    FillConsoleOutputAttribute(handle, csbi.wAttributes, cell_count, cursor_pos,
        &written);

    // Tell Readline the buffer's resized.
    rl_resize_terminal();
}