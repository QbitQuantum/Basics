static size_t try_getline(char *buf, size_t count)
{
// This function makes some pretty big sacrifices on performance and clarity to
// be able to
// query the console without blocking.  This involves a lot of syscalls, but as
// it is intended for debug a repl, it won't affect the general performance of
// the
// lib too much.  win32 doesn't provide a way to query if the console has a line
// available
// without bringing in a lot of crud, so we use the most basic of state machines
// and ignore
// non-ascii scripts.
#ifdef __unix__
    ssize_t len;
    int oldflags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK | O_NDELAY);
    len = read(STDIN_FILENO, buf, count);
    fcntl(STDIN_FILENO, F_SETFL, oldflags);
    if (len < 0) {
        return 0;
    }
    count = len;
    return count;
#elif _WIN32
#define UTF8CP 65001 // UTF-8
    static wint_t line_buf[BMO_TEXT_BUF];
    static int n_read;
    while (_kbhit()) {
        wint_t ch = _getwch();
        // avoid control sequences ending up in the buffer
        if (ch == 0 || ch == 0xe0) {
            // above indicates first half of a FN/arrow key escape sequence
            // http://msdn.microsoft.com/en-us/library/078sfkak.aspx
            (void)_getwch();
            goto fail;
        }
        _putwch(ch);
        if (n_read >= count || n_read >= BMO_TEXT_BUF) {
            printf("line too long for buffer."
                   "Input line ignored.count:%d, n_read:%d, BMO_TEXT_BUF:%d\n",
                   n_read, count, BMO_TEXT_BUF);
            goto fail;
        }
        if (ch == L'\b') {
            // backspace key was pressed
            if (n_read) {
                line_buf[--n_read] = L'\0';
                wprintf(L" \b \b");
            }
            return 0;
        }
        line_buf[n_read] = ch;
        n_read++;
        if (ch == L'\n' || ch == L'\r') {
            // for some reason _newlines aren't properly echoed by _putwch()
            _putwch(L'\n');
            // get required length for UTF-8 string.
            int required = WideCharToMultiByte(
                UTF8CP,   // code page
                0,        // flags
                line_buf, // input string
                n_read,   // input length
                NULL,     // output string (optional)
                0,        // when zero return the resultant length with no-op
                NULL,     // unrepresentable placeholder
                NULL      // pointer to bool indicating default happened
            );
            if (required >= count - 1) {
                puts("UTF-8 string conversion failed;line too long...");
                goto fail;
            }
            if (required == 0) {
                // empty line
                goto fail;
            }
            WideCharToMultiByte(
                UTF8CP, 0, line_buf, n_read, buf, count, NULL, NULL
            );
            wmemset(line_buf, 0, BMO_TEXT_BUF);
            n_read = 0;
            assert(required >= 0);
            return required;
        }
    }
    return 0;
fail:
    wmemset(line_buf, 0, BMO_TEXT_BUF);
    n_read = 0;
    return 0;
// end win32
#else
    (void)buf;
    (void)count;
    BMO_NOT_IMPLEMENTED;
#endif

    return 0;
}