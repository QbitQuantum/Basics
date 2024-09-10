void TimedUserMsg(
    HWND        hwnd,   // in
    const char* format, // in: args like printf
                ...)    // in
{
    va_list args;
    va_start(args, format);
    VSPRINTF(msg_g, format, args);
    va_end(args);
    msg_g[0] = char(toupper(msg_g[0]));
    TimedUserMsg1(hwnd, 3000); // 3000 ms
}