BOOLEAN
NTAPI
KdPortInitializeEx(
    IN PCPPORT PortInformation,
    IN ULONG ComPortNumber)
{
    NTSTATUS Status;
    CHAR buffer[80];

#if 0 // Deactivated because never used in fact (was in KdPortInitialize but we use KdPortInitializeEx)
    /*
     * Find the port if needed
     */
    SIZE_T i;

    if (!PortInitialized)
    {
        DefaultPort.BaudRate = PortInformation->BaudRate;

        if (ComPortNumber == 0)
        {
            /*
             * Start enumerating COM ports from the last one to the first one,
             * and break when we find a valid port.
             * If we reach the first element of the list, the invalid COM port,
             * then it means that no valid port was found.
             */
            for (i = sizeof(BaseArray) / sizeof(BaseArray[0]) - 1; i > 0; i--)
            {
                if (CpDoesPortExist(UlongToPtr(BaseArray[i])))
                {
                    PortInformation->Address = DefaultPort.Address = BaseArray[i];
                    ComPortNumber = (ULONG)i;
                    break;
                }
            }
            if (ComPortNumber == 0)
            {
                sprintf(buffer,
                        "\nKernel Debugger: No COM port found!\n\n");
                HalDisplayString(buffer);
                return FALSE;
            }
        }

        PortInitialized = TRUE;
    }
#endif

    /*
     * Initialize the port
     */
    Status = CpInitialize(PortInformation,
                          (ComPortNumber == 0 ? PortInformation->Address
                                              : UlongToPtr(BaseArray[ComPortNumber])),
                          (PortInformation->BaudRate == 0 ? DEFAULT_BAUD_RATE
                                                          : PortInformation->BaudRate));
    if (!NT_SUCCESS(Status))
    {
        sprintf(buffer,
                "\nKernel Debugger: Serial port not found!\n\n");
        HalDisplayString(buffer);
        return FALSE;
    }
    else
    {
#ifndef NDEBUG
        /* Print message to blue screen */
        sprintf(buffer,
                "\nKernel Debugger: Serial port found: COM%ld (Port 0x%lx) BaudRate %ld\n\n",
                ComPortNumber,
                PortInformation->Address,
                PortInformation->BaudRate);
        HalDisplayString(buffer);
#endif /* NDEBUG */

#if 0
        /* Set global info */
        KdComPortInUse = DefaultPort.Address;
#endif
        return TRUE;
    }
}