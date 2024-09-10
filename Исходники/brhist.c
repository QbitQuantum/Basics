void
brhist_jump_back(void)
{
#if defined(_WIN32)  &&  !defined(__CYGWIN__)
    if (GetFileType(Console_IO.Console_Handle) != FILE_TYPE_PIPE) {
        COORD   Pos;
        CONSOLE_SCREEN_BUFFER_INFO CSBI;

        GetConsoleScreenBufferInfo(Console_IO.Console_Handle, &CSBI);
        Pos.Y = CSBI.dwCursorPosition.Y - brhist.hist_printed_lines;
        Pos.X = 0;
        SetConsoleCursorPosition(Console_IO.Console_Handle, Pos);
    }
#else
    while (brhist.hist_printed_lines-- > 0)
        fputs(Console_IO.str_up, Console_IO.Console_fp);
#endif
}