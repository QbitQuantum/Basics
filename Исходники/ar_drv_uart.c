void os_com_close() { 

    // reset error byte

    if (!EscapeCommFunction((HANDLE) hSerial, CLRDTR)) {

    }
    if (!PurgeComm((HANDLE) hSerial, PURGE_RXABORT | PURGE_RXCLEAR |
                       PURGE_TXABORT | PURGE_TXCLEAR)) {
    }

    // device handle
    CloseHandle((HANDLE) hSerial);
	
}