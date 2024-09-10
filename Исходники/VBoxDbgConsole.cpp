VBoxDbgConsole::~VBoxDbgConsole()
{
    Assert(isGUIThread());

    /*
     * Wait for the thread.
     */
    ASMAtomicWriteBool(&m_fTerminate, true);
    RTSemEventSignal(m_EventSem);
    if (m_Thread != NIL_RTTHREAD)
    {
        int rc = RTThreadWait(m_Thread, 15000, NULL);
        AssertRC(rc);
        m_Thread = NIL_RTTHREAD;
    }

    /*
     * Free resources.
     */
    delete m_pTimer;
    m_pTimer = NULL;
    RTCritSectDelete(&m_Lock);
    RTSemEventDestroy(m_EventSem);
    m_EventSem = 0;
    m_pOutput = NULL;
    m_pInput = NULL;
    if (m_pszInputBuf)
    {
        RTMemFree(m_pszInputBuf);
        m_pszInputBuf = NULL;
    }
    m_cbInputBuf = 0;
    m_cbInputBufAlloc = 0;

    delete m_pFocusToInput;
    m_pFocusToInput = NULL;
    delete m_pFocusToOutput;
    m_pFocusToOutput = NULL;
}