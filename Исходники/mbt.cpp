static int execute_reset(char *szPort)
{
    ComHelper SerialPort;

    if (!SerialPort.OpenPort(szPort))
	{
        printf("Open %s port Failed\n", szPort);
		return 0;
	}

    UINT8 hci_reset[] = {0x01, 0x03, 0x0c, 0x00};
    UINT8 hci_reset_cmd_complete_event[] = {0x04, 0x0e, 0x04, 0x01, 0x03, 0x0c, 0x00};

    printf ("Sending HCI Command:\n");
    HexDump(hci_reset, sizeof(hci_reset));

    // write HCI reset
    SerialPort.Write(hci_reset, sizeof(hci_reset));

    // read HCI response header
    DWORD dwRead = SerialPort.Read((LPBYTE)&in_buffer[0], 3);

    // read HCI response payload
    if (dwRead == 3 && in_buffer[2] > 0)
        dwRead += SerialPort.Read((LPBYTE)&in_buffer[3], in_buffer[2]);

    printf ("Received HCI Event:\n");
    HexDump(in_buffer, dwRead);
    if (dwRead == sizeof(hci_reset_cmd_complete_event))
    {
        if (memcmp(in_buffer, hci_reset_cmd_complete_event, dwRead) == 0)
        {
            printf ("Success\n");
            return 1;
        }
    }
    return 0;
}