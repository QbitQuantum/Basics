/*------------------------------------------------------------------------------
-- FUNCTION:    PortIOThreadProc
--
-- DATE:        Oct 13, 2010
--
-- REVISIONS:   Nov 05, 2010
--              Modified the function to also listen for a "disconnect" event,
--              and to break in that case. ProcessRead() is now called once a 
--				complete packet is confirmed (as opposed to sending the 
--				contents of the buffer to ProcessRead() as soon as they arrive).
--
--				Nov 29, 2010
--				Renamed function from ReadThreadProc(). The event handling is
--				from the original function, but the response to each event has
--				changed.
--
-- DESIGNER:    Dean Morin
--
-- PROGRAMMER:  Dean Morin, Daniel Wright
--
-- INTERFACE:   DWORD WINAPI PortIOThreadProc(HWND hWnd)
--                      hWnd - the handle to the window
--
-- RETURNS:     0 because threads are required to return a DWORD.
--
-- NOTES:
--              While connected, this thread will loop and wait for characters
--              to arrive at the port, or for a timeout to occur, then call the
--				appropriate function. This function uses overlapped I/O.
------------------------------------------------------------------------------*/
DWORD WINAPI PortIOThreadProc(HWND hWnd) {
    OVERLAPPED  ol		= {0};
    DWORD       dwEvent = 0;
    DWORD       dwError = 0;
    COMSTAT     cs      = {0};
    HANDLE*     hEvents = NULL;
    PSTATEINFO  psi     = NULL;
    PWNDDATA	pwd		= (PWNDDATA) GetWindowLongPtr(hWnd, 0);
    

    if ((ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL) {
        DISPLAY_ERROR("Error creating event in read thread");
    }
    hEvents     = (HANDLE*) malloc(sizeof(HANDLE) * PORT_IO_EVENTS);
    hEvents[0]  = CreateEvent(NULL, FALSE, FALSE, TEXT("disconnected"));
    hEvents[1]  = ol.hEvent;
    
    psi = (PSTATEINFO) malloc(sizeof(STATEINFO));
    InitStateInfo(psi);
    DL_STATE = psi->iState;


    while (pwd->bConnected) {
        
        SetCommMask(pwd->hPort, EV_RXCHAR);      
        if (!WaitCommEvent(pwd->hPort, &dwEvent, &ol)) {
            ProcessCommError(pwd->hPort);
        }
        dwEvent = WaitForMultipleObjects(PORT_IO_EVENTS, hEvents, FALSE, 
                                         psi->dwTimeout);
        ClearCommError(pwd->hPort, &dwError, &cs);
 
        if (dwEvent == WAIT_OBJECT_0) {
            // the connection was severed
            break;
        }
        else if (dwEvent == WAIT_OBJECT_0 + 1  &&  cs.cbInQue) {
            // data arrived at the port
            ReadFromPort(hWnd, psi, ol, cs.cbInQue);
        }
        else if (dwEvent == WAIT_TIMEOUT) {
            // a timeout occured
            ProcessTimeout(hWnd, psi);
        }
        else if (dwEvent == WAIT_FAILED) {
            DISPLAY_ERROR("Invalid event occured in the Port I/O thread");
        }
        ResetEvent(ol.hEvent);
    }

    if (!PurgeComm(pwd->hPort, PURGE_RXCLEAR)) {
        DISPLAY_ERROR("Error purging read buffer");
    }
    CloseHandle(ol.hEvent);
    CloseHandle(hEvents[0]);
    free(hEvents);
    return 0;
}