/*-----------------------------------------------------------------------------

FUNCTION: SetPortState( void )

PURPOSE: Sets port state based on settings from the user

COMMENTS: Sets up DCB structure and calls SetCommState.
          Sets up new timeouts by calling SetCommTimeouts.

HISTORY: Date:      Author:     Comment:
        1/9/96     AllenD      Wrote it
        12/06/06    DonnMo      Replaced calls to ErrorReporter() with CHECK_HR()

-----------------------------------------------------------------------------*/
HRESULT RS232Connection::SetPortState()
{
    HRESULT hr          = S_OK;
    DCB     dcb         = {0};
    DWORD   dwLastError = 0;
    
    dcb.DCBlength = sizeof(dcb);

    //
    // get current DCB settings
    //
    if (!GetCommState(m_hCommPort, &dcb))
    {  
        dwLastError = GetLastError();
        hr = HRESULT_FROM_WIN32(dwLastError);
        CHECK_HR(hr, "GetCommState() failed within SetPortState().");
        return hr;
    }

    //
    // update DCB rate, byte size, parity, and stop bits size
    //
    dcb.BaudRate = m_dwBaudRate;
    dcb.ByteSize = m_bByteSize;
    dcb.Parity   = m_bParity;
    dcb.StopBits = m_bStopBits;

    //
    // update event flags
    //
    if (m_dwEventFlags & EV_RXFLAG)
    {
        dcb.EvtChar = m_chFlag;      
    }
    else
    {
        dcb.EvtChar = '\0';
    }

    dcb.EofChar = '\n';

    //
    // update flow control settings
    //
    dcb.fDtrControl     = m_fDtrControl;
    dcb.fRtsControl     = m_fRtsControl;

    dcb.fOutxCtsFlow    = m_fCTSOutFlow;
    dcb.fOutxDsrFlow    = m_fDSROutFlow;
    dcb.fDsrSensitivity = m_fDSRInFlow;
    dcb.fOutX           = m_fXonXoffOutFlow;
    dcb.fInX            = m_fXonXoffInFlow;
    dcb.fTXContinueOnXoff = m_fTXafterXoffSent;
    dcb.XonChar         = m_chXON;
    dcb.XoffChar        = m_chXOFF;
    dcb.XonLim          = m_wXONLimit;
    dcb.XoffLim         = m_wXOFFLimit;

    //
    // DCB settings not in the user's control
    //
    dcb.fParity = TRUE;

    //
    // set new state
    //
    if (!SetCommState(m_hCommPort, &dcb))
    {  
        dwLastError = GetLastError();
        hr = HRESULT_FROM_WIN32(dwLastError);
        CHECK_HR(hr, "SetCommState() failed within SetPortState() when setting the new state.");
        return hr;
    }
        

    //
    // set new timeouts
    //
    if (!SetCommTimeouts(m_hCommPort, &m_timeoutsnew))
    {  
        dwLastError = GetLastError();
        hr = HRESULT_FROM_WIN32(dwLastError);
        CHECK_HR(hr, "SetCommTimeouts() failed within SetPortState() when setting the new timeouts.");
        return hr;
    }

    return hr;
}