/* Function: rtIOStreamOpen =================================================
 * Abstract:
 *  Open the connection with the target.
 */
int rtIOStreamOpen(int argc, void * argv[])
{
    unsigned int        comNum     = 0;
    int result = RTIOSTREAM_NO_ERROR;
    int streamID;
    HANDLE serialHandle;
    int closeFile = false;
    SerialCommsData *sd;

    initSerialCommsDataStructure();

    for (streamID = 0; streamID < N_SERIAL_PORTS; streamID++) {
        if (SerialData[streamID].port[0] == 0) {
            break;
        }
    }
    if (streamID == N_SERIAL_PORTS) {
        printf( "All %d elements of the SerialCommsData structure are already in use.",  N_SERIAL_PORTS );
        return RTIOSTREAM_ERROR;
    }

    sd = &SerialData[streamID];

    sd->baud = BAUD_UNINITIALIZED;

    processArgs(argc, argv, sd);

    if (sd->baud == BAUD_UNINITIALIZED) {
        printf( "A valid bit rate must be specified via the -baud option.");
        sd->port[0] = 0;
        return RTIOSTREAM_ERROR;
    }

    initDCB( sd->baud );

    serialHandle = (void *) CreateFile( sd->port, 
                                        GENERIC_READ | GENERIC_WRITE,
                                        0, NULL, OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL, NULL);

    if (serialHandle == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError( );
        printf( "CreateFile failed, error %d or 0x%08x. One possible "
                "cause is that COM ports COM10 or greater must be "
                "identified by a fully qualified name, e.g. "
                "\\\\.\\COM10.\n", err, err);
        sd->port[0] = 0;
        streamID = RTIOSTREAM_ERROR;
        goto EXIT_POINT;
    }
    sd->serialHandle = serialHandle;

    if (!SetCommTimeouts(serialHandle, &cto_blocking)) {
        printf( "SetCommTimeouts failed\n");
        streamID = RTIOSTREAM_ERROR;
        closeFile = true;
        goto EXIT_POINT;
    }

    if (!SetCommState(serialHandle, &dcb)) {
        printf( "SetCommState failed\n");
        streamID = RTIOSTREAM_ERROR;
        closeFile = true;
	goto EXIT_POINT;
    }

    result = serialDataFlush( sd);      /* clear out old data on the port */
    if (result == RTIOSTREAM_ERROR) {
        printf( "serialDataFlush failed\n");
        streamID = RTIOSTREAM_ERROR;
        closeFile = true;
	goto EXIT_POINT;
    }

  EXIT_POINT:
    if (closeFile) {
        CloseHandle(serialHandle);
        sd->port[0] = 0;
    }
    return streamID;
}