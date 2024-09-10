/*
 *  ======== UARTUtils_deviceclose ========
 */
int UARTUtils_deviceclose(int fd)
{
    /* Return if a UART other than UART 0 was specified. */
    if (fd != 0) {
        return (-1);
    }

    closeHandle(fd);

    return (0);
}