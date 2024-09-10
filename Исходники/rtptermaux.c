/* SPR - was RTP_HANDLE but didn't build */
long rtp_term_aux_open(void)
{
    HANDLE hComm;
    DCB dcb;

    /* JRT */
    COMMTIMEOUTS comm_timeouts;

    hComm = CreateFile( RTP_TERM_AUX_COMM_PORT,  
                    GENERIC_READ | GENERIC_WRITE, 
                    0, 
                    0, 
                    OPEN_EXISTING,
                    FILE_FLAG_OVERLAPPED,
                    0);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        rtp_term_puts("Error in opening serial comm\n");
        return -1;
    }
    if (!GetCommState(hComm, &dcb))     // get current DCB
          // Error in GetCommState
          return FALSE;

    FillMemory(&dcb, sizeof(dcb), 0);
    dcb.DCBlength = sizeof(dcb);
    if (!BuildCommDCB("baud=9600 parity=n data=8 stop=1 dtr=on rts=on", &dcb)) {   
          // Couldn't build the DCB. Usually a problem
          // with the communications specification string.
          return FALSE;
    }

    // Update DCB rate.
    //dcb.BaudRate =  RTP_TERM_AUX_BAUD_RATE;

    // Set new state.
    if (!SetCommState(hComm, &dcb))
    {
      // Error in SetCommState. Possibly a problem with the communications 
      // port handle or a problem with the DCB structure itself.
    } 

    /* JRT - Get the timeout and set it appropriately */
    rtp_memset(&comm_timeouts, 0x0, sizeof(comm_timeouts));

#define GET_COMM_TIMEOUTS 0
#if GET_COMM_TIMEOUTS
    GetCommTimeouts(hComm, &comm_timeouts);
#endif

    if (!SetCommTimeouts(hComm, &comm_timeouts))
    {
        char err_string[100];
        int error;
        
        error = GetLastError();
        rtp_sprintf(err_string,
                    "rtp_term_aux_open: SetCommTimeouts failed, error = %d\n",
                    error);
        rtp_term_puts(err_string);
        return (-1);
    }

    auxComm = (RTP_HANDLE) hComm;
    
    return (auxComm);
 
}