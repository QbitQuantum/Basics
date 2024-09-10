    void PCSCDataTransport::send(const std::vector<unsigned char>& data)
    {
        d_response.clear();

        EXCEPTION_ASSERT_WITH_LOG(getPCSCReaderUnit(), LibLogicalAccessException, "The PCSC reader unit object"
                "is null. We cannot send.");
        if (data.size() > 0)
        {
            unsigned char returnedData[255];
            ULONG ulNoOfDataReceived = sizeof(returnedData);
            LPCSCARD_IO_REQUEST ior = NULL;
            switch (getPCSCReaderUnit()->getActiveProtocol())
            {
            case SCARD_PROTOCOL_T0:
                ior = SCARD_PCI_T0;
                break;

            case SCARD_PROTOCOL_T1:
                ior = SCARD_PCI_T1;
                break;

            case SCARD_PROTOCOL_RAW:
                ior = SCARD_PCI_RAW;
                break;
            }

            LOG(LogLevel::COMS) << "APDU command: " << BufferHelper::getHex(data);

            unsigned int errorFlag = SCardTransmit(getPCSCReaderUnit()->getHandle(), ior, &data[0], static_cast<DWORD>(data.size()), NULL, returnedData, &ulNoOfDataReceived);

            CheckCardError(errorFlag);
            d_response = std::vector<unsigned char>(returnedData, returnedData + ulNoOfDataReceived);
        }
    }