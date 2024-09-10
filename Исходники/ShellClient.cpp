// Clean up the used resources
VOID CShellClient::Cleanup()
{
    if (NULL != m_command)
    {
        WSManCloseCommand(m_command,
                          0,
                          &m_async);
        WaitForSingleObject(m_event, INFINITE);
        if (NO_ERROR != m_errorCode) 
        {
            wprintf(L"WSManCloseCommand failed: %d\n", m_errorCode);
        }
        else
        {
            m_command = NULL;
        }
    }

    if (NULL != m_shell)
    {
        WSManCloseShell(m_shell,
                        0,
                        &m_async);
        WaitForSingleObject(m_event, INFINITE);
        if (NO_ERROR != m_errorCode) 
        {
            wprintf(L"WSManCloseShell failed: %d\n", m_errorCode);
        }
        else
        {
            m_shell = NULL;
        }
    }

    // Frees memory of session and closes all related operations before returning
    m_errorCode = WSManCloseSession(m_session, 0);
    if (NO_ERROR != m_errorCode)
    {
        wprintf(L"WSManCloseSession failed: %d\n", m_errorCode);
    }

    // deinitializes the Winrm client stack; all operations will 
    // finish before this API will return
    m_errorCode = WSManDeinitialize(m_apiHandle, 0);
    if (NO_ERROR != m_errorCode)
    {
        wprintf(L"WSManDeinitialize failed: %d\n", m_errorCode);
    }

    if (NULL != m_event)
    {
        CloseHandle(m_event);
        m_event = NULL;
    }
    if (NULL != m_ReceiveEvent)
    {
        CloseHandle(m_ReceiveEvent);
        m_ReceiveEvent = NULL;
    }

    m_bSetup = FALSE;
    m_bExecute = FALSE;
}