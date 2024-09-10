void serial_loop()
{
    char buff[SERIAL_BUFFER];
    int pos = 0;
#ifdef __WIN32__
    DWORD state, len_in = 0;
    BOOL fWaitingOnRead = FALSE;
    OVERLAPPED osReader = {0};
    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if(osReader.hEvent == NULL)
    {
        server_log(LOG_ERR, "serial_loop: CreateEvent");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        if(!fWaitingOnRead)
        {
            if(!ReadFile(server.serialfd, &buff[pos], 1, &len_in, &osReader))
            {
                if(GetLastError() != ERROR_IO_PENDING)
                {
                    CloseHandle(osReader.hEvent);
                    break;
                }
                else
                    fWaitingOnRead = TRUE;
            }
        }
        if(fWaitingOnRead)
        {
            state = WaitForSingleObject(osReader.hEvent, 200);
            if(state == WAIT_TIMEOUT)
                continue;
            if(state != WAIT_OBJECT_0 ||
               !GetOverlappedResult(server.serialfd, &osReader, &len_in, FALSE))
            {
                CloseHandle(osReader.hEvent);
                break;
            }
            fWaitingOnRead = FALSE;
        }
        if(len_in != 1)
            continue;
#else
    fd_set input;
    FD_ZERO(&input);
    FD_SET(server.serialfd, &input);
    while(select(server.serialfd+1, &input, NULL, NULL, NULL) > 0)
    {
        if(read(server.serialfd, &buff[pos], 1) <= 0)
            break;
#endif
        if(buff[pos] != '\n') /* If this command is too long to fit into a buffer, clip it */
        {
            if(pos != SERIAL_BUFFER-1)
                pos++;
            continue;
        }
        buff[pos] = 0;
        if(pos)
            msg_parse_serial(buff[0], buff+1);
        buff[pos] = '\n';
        msg_send(buff, pos+1);
        pos = 0;
    }
#ifdef __WIN32__
    CloseHandle(server.serialfd);
#else
    close(server.serialfd);
#endif
}

void serial_write(char* msg, int len)
{
    pthread_mutex_lock(&server.mutex_s);
#ifdef __WIN32__
    OVERLAPPED osWrite = {0};
    DWORD dwWritten;

    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if(osWrite.hEvent == NULL)
    {
        server_log(LOG_ERR, "server_conn: CreateEvent");
        exit(EXIT_FAILURE);
    }

    if(!WriteFile(server.serialfd, msg, len, &dwWritten, &osWrite))
        if(GetLastError() == ERROR_IO_PENDING)
            if(WaitForSingleObject(osWrite.hEvent, INFINITE) == WAIT_OBJECT_0)
                GetOverlappedResult(server.serialfd, &osWrite, &dwWritten, FALSE);
    CloseHandle(osWrite.hEvent);
#else
    write(server.serialfd, msg, len);
#endif
    pthread_mutex_unlock(&server.mutex_s);
}