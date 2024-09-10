int ty_terminal_setup(int flags)
{
    HANDLE handle;
    DWORD mode;
    BOOL r;

    handle = GetStdHandle(STD_INPUT_HANDLE);
    if (handle == INVALID_HANDLE_VALUE)
        return ty_error(TY_ERROR_SYSTEM, "GetStdHandle(STD_INPUT_HANDLE) failed");

    r = GetConsoleMode(handle, &mode);
    if (!r) {
        if (GetLastError() == ERROR_INVALID_HANDLE)
            return ty_error(TY_ERROR_UNSUPPORTED, "Not a terminal");
        return ty_error(TY_ERROR_SYSTEM, "GetConsoleMode(STD_INPUT_HANDLE) failed: %s",
                        ty_win32_strerror(0));
    }

    if (!saved_console_mode) {
        orig_console_mode = mode;
        saved_console_mode = true;

        atexit(ty_terminal_restore);
    }

    mode |= ENABLE_PROCESSED_INPUT;

    mode &= (DWORD)~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    if (!(flags & TY_TERMINAL_RAW))
        mode |= ENABLE_LINE_INPUT;
    if (!(flags & TY_TERMINAL_SILENT))
        mode |= ENABLE_ECHO_INPUT;

    r = SetConsoleMode(handle, mode);
    if (!r)
        return ty_error(TY_ERROR_SYSTEM, "SetConsoleMode(STD_INPUT_HANDLE) failed: %s",
                        ty_win32_strerror(0));

    return 0;
}