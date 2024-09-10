/* get the display metrics */
void ossgmx(int *max_linep, int *max_columnp)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    /* get the console handle */
    G_out_bufhdl = GetStdHandle(STD_OUTPUT_HANDLE);

    /* get the size of the screen and return it to the caller's variables */
    if (GetConsoleScreenBufferInfo(G_out_bufhdl, &info))
    {
        /* 
         *   If it's scrolled down, scroll it to the top.  If the screen
         *   buffer size is larger than the window size, reduce the buffer
         *   size to match the window size: we do all of the scrolling
         *   ourselves, so we don't want to do that on top of a separate
         *   scrolling canvas managed by the system. 
         */
        if (!os_f_plain
            && (info.srWindow.Top != 0 || info.srWindow.Left != 0
                || info.dwSize.X > info.srWindow.Right + 1
                || info.dwSize.Y > info.srWindow.Bottom + 1))
        {
            COORD buf_size;
            
            /* scroll it to the top left */
            info.srWindow.Bottom -= info.srWindow.Top;
            info.srWindow.Top = 0;
            info.srWindow.Right -= info.srWindow.Left;
            info.srWindow.Left = 0;
            SetConsoleWindowInfo(G_out_bufhdl, TRUE, &info.srWindow);

            /* remember the original buffer size */
            S_orig_buffer_size = info.dwSize;

            /* set the window buffer size to equal the window size */
            buf_size.X = info.srWindow.Right + 1;
            buf_size.Y = info.srWindow.Bottom + 1;
            SetConsoleScreenBufferSize(G_out_bufhdl, buf_size);
        }
        
        /* got the information - use the current window size */
        *max_columnp = info.srWindow.Right - info.srWindow.Left;
        *max_linep = info.srWindow.Bottom - info.srWindow.Top;
    }
    else
    {
        /* failed to get info - use default sizes */
        *max_columnp = 79;
        *max_linep = 24;
    }

    /* note the screen width for our own use */
    S_scrwid = info.dwMaximumWindowSize.X;
}