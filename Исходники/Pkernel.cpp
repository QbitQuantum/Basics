void System::assert(int Window, char expr, char *error_msg) /*Different levels of kernel errors, only one so far.*/
{
    video.setcolour(Window, TRED | BBLUE | BLINK); /*print error in red*/
    video.prints(Window, "\n  Error: ");
    video.setcolour(Window, TRED | BBLUE);
    video.prints(Window, error_msg);
    video.putc(Window, '\n');

    switch (expr)
    {
    case 1:			/*level one. No need to restart*/
        video.setcolour(Window, TCYAN | BBLUE);
        return;
    default:		/*level zero. restart required.*/
        video.prints(Window, "  System halted.");
        video.hidecursor(true);
        break;
    }
    restart(0);
}