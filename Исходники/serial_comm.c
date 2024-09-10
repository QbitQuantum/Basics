EXPORT int serial_comm_set_settings(void *handle, SERIAL_COM_SETTINGS * settings)
{
    BOOL port_ready;
    DCB comm_state;
    COMMTIMEOUTS timeouts;

    if(handle == NULL)
        return RESULT_FAILURE;

    port_ready = SetupComm(handle, settings->InputBufferSize, settings->OutputBufferSize);

    if(!port_ready)
        return RESULT_FAILURE;

    port_ready = GetCommState(handle, &comm_state);

    if(!port_ready)
        return RESULT_FAILURE;

    comm_state.BaudRate = settings->Baud;
    comm_state.ByteSize = settings->ByteSize;
    comm_state.Parity = settings->Parity;
    comm_state.StopBits = settings->StopBits;
    comm_state.fAbortOnError = settings->AbortOnError;

    port_ready = SetCommState(handle, &comm_state);

    if(!port_ready)
        return RESULT_FAILURE;

    port_ready = GetCommTimeouts (handle, &timeouts);

    if(!port_ready)
        return RESULT_FAILURE;

    timeouts.ReadIntervalTimeout = settings->ReadIntervalTimeout;
    timeouts.ReadTotalTimeoutConstant = settings->ReadTotalTimeoutConstant;
    timeouts.ReadTotalTimeoutMultiplier = settings->ReadTotalTimeoutMultiplier;
    timeouts.WriteTotalTimeoutConstant = settings->WriteTotalTimeoutConstant;
    timeouts.WriteTotalTimeoutMultiplier = settings->WriteTotalTimeoutMulitplier;

    port_ready = SetCommTimeouts (handle, &timeouts);

    if(!port_ready)
        return RESULT_FAILURE;


    return RESULT_SUCCESS;
}