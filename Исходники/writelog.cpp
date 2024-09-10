int console_get (TCHAR *out, int maxlen)
{
    *out = 0;

    set_console_input_mode(1);
    if (consoleopen > 0) {
        return console_get_gui (out, maxlen);
    } else if (realconsole) {
        DWORD totallen;

        *out = 0;
        totallen = 0;
        while (maxlen > 0) {
            *out = getwc (stdin);
            if (*out == 13)
                break;
            out++;
            maxlen--;
            totallen++;
        }
        *out = 0;
        return totallen;
    } else if (consoleopen < 0) {
        DWORD len, totallen;

        *out = 0;
        totallen = 0;
        while(maxlen > 0) {
            ReadConsole (stdinput, out, 1, &len, 0);
            if(*out == 13)
                break;
            out++;
            maxlen--;
            totallen++;
        }
        *out = 0;
        return totallen;
    }
    return 0;
}