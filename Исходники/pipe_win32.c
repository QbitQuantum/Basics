char *pipe_win32_poll(int *error)
{
    *error = 0;

    /* Repeat until no more data is available, or a full message has been
    ** received.
    */
    while (1)
    {
        DWORD bytes;
        char *msg;
        int len;

        if ((msg = msgbuf_process(buf)))
            return msg;

        len = strlen(buf);

        /* Check whether data is available. */
        if (console_mode)
        {
            if (!GetNumberOfConsoleInputEvents(h_in, &bytes))
            {
                /* Error reading console input. */
                fprintf(stderr, "%s, L%d: Error reading console input.\n", __FILE__, __LINE__);
                *error = 1;
                return NULL;
            }
        } else if (!PeekNamedPipe(h_in, NULL, 0, NULL, &bytes, NULL))
        {
            /* Error reading pipe. */
            fprintf(stderr, "%s, L%d: Broken pipe.\n", __FILE__, __LINE__);
            *error = 1;
            return NULL;
        }

        if (bytes > 0)
        {
            /* Read data. */
            if (!ReadFile(h_in, buf + len, BUF_LEN - len - 1, &bytes, NULL))
            {
                /* Error reading pipe. */
                fprintf(stderr, "%s, L%d: Broken pipe.\n", __FILE__, __LINE__);
                *error = 1;
                return NULL;
            }

            if (!console_mode && bytes == 0)
            {
                /* Received EOF. */
                fprintf(stderr, "%s, L%d: Broken pipe.\n", __FILE__, __LINE__);
                *error = 1;
                return NULL;
            }

            buf[len + bytes] = '\0';
        }
        else
            /* No data available. */
            break;
    }
    return NULL;
}