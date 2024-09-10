    void OmnikeyXX21ReaderUnit::getT_CL_ISOType(bool& isTypeA, bool& isTypeB)
    {
        unsigned char outBuffer[64];
        DWORD dwOutBufferSize;
        unsigned char inBuffer[2];
        DWORD dwInBufferSize;
        DWORD dwBytesReturned;
        DWORD dwControlCode = CM_IOCTL_GET_SET_RFID_BAUDRATE;
        DWORD dwStatus;

        memset(outBuffer, 0x00, sizeof(outBuffer));
        dwOutBufferSize = sizeof(outBuffer);
        dwInBufferSize = sizeof(inBuffer);
        dwBytesReturned = 0;

        inBuffer[0] = 0x01;	// Version of command
        inBuffer[1] = 0x00; // Get asymmetric baud rate information

        isTypeA = false;
        isTypeB = false;

        dwStatus = SCardControl(getHandle(), dwControlCode, (LPVOID)inBuffer, dwInBufferSize, (LPVOID)outBuffer, dwOutBufferSize, &dwBytesReturned);
        if (dwStatus == SCARD_S_SUCCESS && dwBytesReturned >= 10)
        {
            switch (outBuffer[9])
            {
            case 0x04:
                isTypeA = true;
                break;

            case 0x08:
                isTypeB = true;
                break;
            }
        }
    }