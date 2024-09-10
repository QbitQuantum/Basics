/*
 * Main application routine. 
 *
 * Nut/OS automatically calls this entry after initialization.
 */
int main(void)
{
    TCPSOCKET *sock;
    CHANNEL cd;
    uint32_t baud = 9600;

    /*
     * Register our devices.
     */
    NutRegisterDevice(&DEV_UART, 0, 0);
#ifndef DEV_ETHER
    for (;;);
#else
    NutRegisterDevice(&DEV_ETHER, 0x8300, 5);

    /*
     * Setup the uart device.
     */
    cd.cd_rs232 = fopen(DEV_UART_NAME, "r+b");
    _ioctl(_fileno(cd.cd_rs232), UART_SETSPEED, &baud);

    /*
     * Setup the ethernet device. Try DHCP first. If this is
     * the first time boot with empty EEPROM and no DHCP server
     * was found, use hardcoded values.
     */
    if (NutDhcpIfConfig(DEV_ETHER_NAME, 0, 60000)) {
        /* No valid EEPROM contents, use hard coded MAC. */
        uint8_t my_mac[] = { 0x00, 0x06, 0x98, 0x20, 0x00, 0x00 };

        if (NutDhcpIfConfig("eth0", my_mac, 60000)) {
            /* No DHCP server found, use hard coded IP address. */
            uint32_t ip_addr = inet_addr("192.168.192.100");
            uint32_t ip_mask = inet_addr("255.255.255.0");

            NutNetIfConfig("eth0", my_mac, ip_addr, ip_mask);
            /* If not in a local network, we must also call 
               NutIpRouteAdd() to configure the routing. */
        }
    }

    /*
     * Start a RS232 receiver thread.
     */
    NutThreadCreate("xmit", Receiver, &cd, 512);

    /*
     * Now loop endless for connections.
     */
    cd.cd_connected = 0;
    for (;;) {
        /*
         * Create a socket and listen for a client.
         */
        sock = NutTcpCreateSocket();
        NutTcpAccept(sock, TCPPORT);

        /*
         * Open a stdio stream assigned to the connected socket.
         */
        cd.cd_tcpip = _fdopen((int) sock, "r+b");
        cd.cd_connected = 1;

        /*
         * Call RS232 transmit routine. On return we will be
         * disconnected again.
         */
        StreamCopy(cd.cd_tcpip, cd.cd_rs232, &cd.cd_connected);

        /*
         * Close the stream.
         */
        fclose(cd.cd_tcpip);

        /*
         * Close our socket.
         */
        NutTcpCloseSocket(sock);
    }
#endif
    return 0;
}