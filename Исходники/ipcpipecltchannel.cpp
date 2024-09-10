BOOL ipcPipeCltChannel::Connect()
{
    BOOL bReturn = FALSE;

    if (m_hPipe)
    {
        bReturn = TRUE;
        goto Exit0;
    }
    
    do
    { 
        m_hPipe = CreateFile( 
            m_strPipeName.c_str(),
            GENERIC_READ | GENERIC_WRITE, 
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
        if (m_hPipe != INVALID_HANDLE_VALUE) 
            break; 

        DWORD dwError = GetLastError();
        //LOGA("ipcPipeCltChannel::Connect CreateFile error:%d", dwError);
        if (dwError != ERROR_PIPE_BUSY) 
        {
            goto Exit0;
        }

        // All pipe instances are busy, so wait for 1 second. 
        if (!WaitNamedPipe(m_strPipeName.c_str(), 1000)) 
        { 
            goto Exit0;
        }
    } while (true);

    // The pipe connected; change to message-read mode. 
    DWORD dwMode = PIPE_READMODE_BYTE; 
    BOOL bSuccess;
    bSuccess = SetNamedPipeHandleState( 
        m_hPipe,    // pipe handle 
        &dwMode,  // new pipe mode 
        NULL,     // don't set maximum bytes 
        NULL);    // don't set maximum time 
    if (!bSuccess) 
    {
        goto Exit0;
    }

    bReturn = TRUE;
    
Exit0:
    if (!bReturn) m_hPipe = NULL;
    
    return bReturn;
}