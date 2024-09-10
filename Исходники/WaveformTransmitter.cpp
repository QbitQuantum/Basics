/******************************************************************************
Function Name   : TransmissionThreadProc
Input(s)        : pVoid -
Output          :
Functionality   : Transmit thread for the sending waveform messages.
Member of       : Global
Friend of       : -
Author(s)       : Arunkumar K.
Date Created    : 26.08.2010
Modification    :
******************************************************************************/
DWORD WINAPI TransmissionThreadProc(LPVOID pVoid)
{
    pThreadParam = (CPARAM_THREADPROC*) pVoid;
    ASSERT(NULL != pThreadParam);

    CWaveformTransmitter* pCurrObj = static_cast<CWaveformTransmitter*> (pThreadParam->m_pBuffer);
    ASSERT(NULL != pCurrObj);

    UINT SamplingRate = pCurrObj->shGetSamplingTimePeriod();
    int nIterLimit = pCurrObj->nGetIterationLimit();

    TIMECAPS time;
    if (timeGetDevCaps(&time, sizeof(TIMECAPS)) == TIMERR_NOERROR)
    {
        if (time.wPeriodMin <= SamplingRate)
        {
            MMRESULT mmResult = timeBeginPeriod(time.wPeriodMin);
            if (TIMERR_NOCANDO == mmResult)
            {
                // TBD
            }
        }
        else
        {
            ASSERT(FALSE); // Unexpected situation.
        }
    }

    // As thread parameter we need an auto-reset event.
    pThreadParam->m_unActionCode = INVOKE_FUNCTION;
    pThreadParam->m_hActionEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    MMRESULT Result = timeSetEvent(SamplingRate, SamplingRate /*time.wPeriodMin*/,
                                   (LPTIMECALLBACK) pThreadParam->m_hActionEvent, NULL,
                                   TIME_CALLBACK_EVENT_SET | TIME_PERIODIC);
    ASSERT(NULL != Result);

    bool bLoopON = true;
    int i = 0;

    while (bLoopON)
    {
        WaitForSingleObject(pThreadParam->m_hActionEvent, INFINITE);

        switch (pThreadParam->m_unActionCode)
        {
            case INVOKE_FUNCTION:
            {
                // Calculate signal values at the curent iteration and transmit
                // the message(s).
                pCurrObj->vProcessWaveForm(i);
            }
            break;
            case EXIT_THREAD:
            {
                bLoopON = false;
            }
            break;
            default:
            case INACTION:
            {
                // nothing right at this moment
            }
            break;
        }
        i = (i < nIterLimit) ? ++i : 0;
    }
    SetEvent(pThreadParam->hGetExitNotifyEvent());

    if(Result != 0)
    {
        Result = timeKillEvent(Result);
    }

    pThreadParam = NULL; //thread terminated

    return 0;
}