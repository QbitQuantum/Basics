int main(void)
{
	unsigned int sockaddr;
	unsigned char mysocket;
	unsigned int rsize;

	/* Initialize the UART for ATmega168 96008N1    */
	uart_init();

	stdout = &uart_stdout;	//Required for printf init

	mysocket = 0;		// magic number! declare the socket number we will us
	sockaddr = W5100_SKT_BASE(mysocket);	// calc address of W5100 register set for this socket

	puts("AVR Ethernet\r\n");
/*
 *  Initialize the ATmega168 SPI subsystem
 */
	CS_PORT |= (1 << CS_BIT);	// pull CS pin high
	CS_DDR |= (1 << CS_BIT);	// now make it an output

	SPI_PORT = SPI_PORT | (1 << PORTB2);	// make sure SS is high
	SPI_DDR = (1 << PORTB3) | (1 << PORTB5) | (1 << PORTB2);	// set MOSI, SCK and SS as output, others as input
	SPCR = (1 << SPE) | (1 << MSTR);	// enable SPI, master mode 0
	SPSR |= (1 << SPI2X);	// set the clock rate fck/2

/*
 *  Load up the callback block, then initialize the Wiznet W5100
 */
	my_callbacks._select = &my_select;	// callback for selecting the W5100
	my_callbacks._xchg = &my_xchg;	// callback for exchanging data
	my_callbacks._deselect = &my_deselect;	// callback for deselecting the W5100
	my_callbacks._reset = &my_reset;	// callback for hardware-reset of the W5100

	W51_register(&my_callbacks);	// register our target-specific W5100 routines with the W5100 library
	W51_init();		// now initialize the W5100

/*
 *  Configure the W5100 device to handle PING requests.
 *  This requires configuring the chip, not a specific socket.
 */
	W51_config(&my_cfg);	// config the W5100 (MAC, TCP address, subnet, etc

	puts("Debug: AVR Ethernet after W5100 config\r\n");

/*
 *  The main loop.  Control stays in this loop forever, processing any received packets
 *  and sending any requested data.
 */
	while (1) {
		switch (W51_read(sockaddr + W5100_SR_OFFSET))	// based on current status of socket...
		{
		case W5100_SKT_SR_CLOSED:	// if socket is closed...
			if (OpenSocket(mysocket, W5100_SKT_MR_TCP, HTTP_PORT) == mysocket)	// if successful opening a socket...
			{
				Listen(mysocket);
				_delay_ms(1);
			}
			break;

		case W5100_SKT_SR_ESTABLISHED:	// if socket connection is established...
			rsize = ReceivedSize(mysocket);	// find out how many bytes
			if (rsize > 0) {
				if (Receive(mysocket, buf, rsize) != W5100_OK)
					break;	// if we had problems, all done
/*
 *  Add code here to process the payload from the packet.
 *
 *  For now, we just ignore the payload and send a canned HTML page so the client at least
 *  knows we are alive.
 */
				strcpy_P((char *)buf,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
				strcat_P((char *)buf,PSTR("<html>\r\n<body>\r\n"));
				strcat_P((char *)buf,PSTR("<title>Title</title>\r\n"));
				strcat_P((char *)buf,PSTR("<p>Hello world</p>\r\n"));
				strcat_P((char *)buf,PSTR("</body>\r\n</html>\r\n"));
				if (Send(mysocket, buf, strlen((char *)buf)) == W5100_FAIL) break;	// just throw out the packet for now

				DisconnectSocket(mysocket);
			} else	// no data yet...
			{
				_delay_us(10);
			}
			break;

		case W5100_SKT_SR_FIN_WAIT:
		case W5100_SKT_SR_CLOSING:
		case W5100_SKT_SR_TIME_WAIT:
		case W5100_SKT_SR_CLOSE_WAIT:
		case W5100_SKT_SR_LAST_ACK:
			CloseSocket(mysocket);
			break;
		}
	}

	return 0;
}