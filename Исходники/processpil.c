int ShellRead(SHELL_PARAM* param, int timeout)
{
#ifndef WIN32
    int ret;
    fd_set fds;
    struct timeval tv;
#endif

    if (!param->buffer || param->iBufferSize <= 0)
    {
        if (param->flags & SF_ALLOC)
        {
            param->buffer=malloc(SF_BUFFER_SIZE);
            param->iBufferSize=SF_BUFFER_SIZE;
        }
        else
        {
            return -1;
        }
    }

#ifndef WIN32
    FD_ZERO(&fds);
    FD_SET(param->fdRead,&fds);
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout - tv.tv_sec * 1000) * 1000;
#endif

    if (!(param->flags & SF_READ_STDOUT_ALL)) {
#ifdef WIN32
        DWORD bytes;
        BOOL success;
        DWORD start = GetTickCount();
        do
        {
            if (!PeekNamedPipe(param->fdRead,0,0,0,&bytes,0))
                return -1;
        } while (bytes == 0
                 && WaitForSingleObject(param->piProcInfo.hProcess, 50) == WAIT_TIMEOUT && GetTickCount() - start < (DWORD)timeout);
        if (bytes == 0)
            return 0;

        param->locked++;
        success =ReadFile(param->fdRead, param->buffer, param->iBufferSize - 1, &bytes, NULL);
        param->locked--;
        if (!success)
            return -1;
        param->buffer[bytes]=0;
        return bytes;
#else
        if (select(param->fdRead+1,&fds,NULL,NULL,&tv) < 1)
            return -1;
        ret=read(param->fdRead,param->buffer, param->iBufferSize - 1);
        if (ret<1)
            return -1;
        param->buffer[ret] = 0;
        return ret;
#endif
    } else {
#ifdef WIN32
        size_t offset = 0;
        int fSuccess;
        for(;;)
        {
            DWORD bytes;
            DWORD start = GetTickCount();
            do
            {
                if (!PeekNamedPipe(param->fdRead,0,0,0,&bytes,0))
                    return -1;
            } while (bytes == 0
                     && WaitForSingleObject(param->piProcInfo.hProcess, 50) == WAIT_TIMEOUT && GetTickCount() - start < (DWORD)timeout);
            if (bytes == 0)
                return 0;

            if (offset + bytes + 1 >= (size_t)param->iBufferSize)
            {
                if (param->flags & SF_ALLOC)
                {
                    param->iBufferSize = max(param->iBufferSize * 2, (int)(offset + bytes + 1));
                    param->buffer = realloc(param->buffer, param->iBufferSize);
                }
                else
                {
                    break;
                }
            }
            param->locked++;
            fSuccess = ReadFile(param->fdRead, param->buffer + offset, param->iBufferSize - 1 - offset, &bytes, NULL);
            param->locked--;
            if (!fSuccess)
                break;
            offset += bytes;
        }
        param->buffer[offset]=0;
        return offset;
#endif
    }
}