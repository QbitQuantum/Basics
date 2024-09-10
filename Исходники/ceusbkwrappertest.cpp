static BOOL handleCommand(char line[])
{
    BOOL ret = TRUE;
    if (strcmp(line, "q") == 0)
        ret = FALSE;
    else if (strcmp(line, "o") == 0 &&
             gDeviceHandle == INVALID_HANDLE_VALUE)
        openDriver();
    else if (strcmp(line, "c") == 0 &&
             gDeviceHandle != INVALID_HANDLE_VALUE)
        closeDriver();
    else if (strcmp(line, "g") == 0 &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize == 0)
        getDeviceList();
    else if (strcmp(line, "p") == 0 &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        printDeviceList();
    else if (strcmp(line, "r") == 0 &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        releaseDeviceList();
    else if (line[0] == 'm' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        sendControlRequest(line + 1);
    else if (line[0] == 'a' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        sendAapRequest(line + 1);
    else if (line[0] == 'c' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        requestConfigurationDescriptor(line + 1);
    else if (line[0] == 'o' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        getActiveConfigValue(line + 1);
    else if (line[0] == 's' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        setActiveConfigValue(line + 1);
    else if (line[0] == 'i' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        performInterfaceOperation(line + 1);
    else if (line[0] == 'r' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        resetDevice(line + 1);
    else if (line[0] == 'k' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        performKernelAttachOperation(line + 1);
    else if (line[0] == 'b' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        startAAPBulkTransfer(line + 1);
    else if (line[0] == 'h' &&
             gDeviceHandle != INVALID_HANDLE_VALUE &&
             gDeviceListSize > 0)
        performHaltOperation(line + 1);
    else
        printf("Unknown command '%s'\n", line);
    return ret;
}