void CheckReadyToRead(UART_PORT port)
{
    COMSTAT	comstat;
    DWORD	errors;
    if(ClearCommError(UARTHandle[port], &errors, &comstat))
    {
        if(comstat.cbInQue)        
        {
            UART_sendilm(port, MSG_ID_UART_READY_TO_READ_IND);
            breadytoread[port] = FALSE;
        }
    }        
}