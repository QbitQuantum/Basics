void update_cursor(void)
{
    SetCaretPos(last_col * char_width, last_line * char_height);
    ShowCaret(hwnd);
}