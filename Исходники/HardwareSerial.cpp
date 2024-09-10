void
HardwareSerial::begin(unsigned long baud)
{
	baudRate = baud;
    //
    // Initialize the UART.
    //
    ROM_SysCtlPeripheralEnable(g_ulUARTPeriph[uartModule]);

    //TODO:Add functionality for PinConfigure with variable uartModule
    ROM_GPIOPinConfigure(g_ulUARTConfig[uartModule][0]);
    ROM_GPIOPinConfigure(g_ulUARTConfig[uartModule][1]);

    ROM_GPIOPinTypeUART(g_ulUARTPort[uartModule], g_ulUARTPins[uartModule]);

    ROM_UARTConfigSetExpClk(UART_BASE, F_CPU, baudRate,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));
    //
    // Set the UART to interrupt whenever the TX FIFO is almost empty or
    // when any character is received.
    //
    ROM_UARTFIFOLevelSet(UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    flushAll();
    ROM_UARTIntDisable(UART_BASE, 0xFFFFFFFF);
    ROM_UARTIntEnable(UART_BASE, UART_INT_RX | UART_INT_RT);
    ROM_IntEnable(g_ulUARTInt[uartModule]);

    //
    // Enable the UART operation.
    //
    ROM_UARTEnable(UART_BASE);

    // Allocate TX & RX buffers
    if (txBuffer != (unsigned char *)0xFFFFFFFF)  // Catch attempts to re-init this Serial instance by freeing old buffer first
        free(txBuffer);
    if (rxBuffer != (unsigned char *)0xFFFFFFFF)  // Catch attempts to re-init this Serial instance by freeing old buffer first
        free(rxBuffer);
    txBuffer = (unsigned char *) malloc(txBufferSize);
    rxBuffer = (unsigned char *) malloc(rxBufferSize);

    SysCtlDelay(100);
}