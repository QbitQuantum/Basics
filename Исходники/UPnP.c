/**
 * @brief	This function processes the add port to IGD(Internet Gateway Device).
 * @return	0: success, -2: Invalid UPnP Step, -1: reply packet timeout, 1: received xml parse error, other: UPnP error code
 */
signed short AddPortProcess(
  SOCKET sockfd,	/**< a socket number. */
  const char* protocol,	/**< a procotol name. "TCP" or "UDP" */
  const unsigned int extertnal_port,	/**< an external port number. */
  const char* internal_ip,	/**< an internal ip address. */
  const unsigned int internal_port,	/**< an internal port number. */
  const char* description	/**< a description of this portforward. */
  )
{
	short len=0;
        long endTime=0;
        uint32 ipaddr;
        uint16 port;

	// Check UPnP Step
	if(UPnP_Step < 2) return -2;

	// Make "Add Port" XML(SOAP)
	memset(content, '\0', MAX_BUFFER);
	MakeSOAPAddControl(content, protocol, extertnal_port, internal_ip, internal_port, description);

	// Make HTTP POST Header
	memset(send_buffer, '\0', MAX_BUFFER);
	len = strlen(content);
	MakePOSTHeader(send_buffer, len, ADD_PORT);
	strcat(send_buffer, content);

#ifdef UPNP_DEBUG
	printf("%s\r\n", send_buffer);
#endif

	ipaddr = inet_addr((uint8*)descIP);
	ipaddr = swapl(ipaddr);
	port = ATOI(descPORT, 10);

	// Connect to IGD(Internet Gateway Device)
	if(TCPClientOpen(sockfd, PORT_UPNP, (uint8*)&ipaddr, port) == FAIL) printf("TCP Socket Error!!\r\n");

	// Send "Add Port" Message
	while(GetTCPSocketStatus(sockfd) != STATUS_ESTABLISHED);
	TCPSend(sockfd, (void *)send_buffer, strlen(send_buffer));

	// Receive Reply
	memset(recv_buffer, '\0', MAX_BUFFER);
	Delay_ms(500);
	endTime = my_time + 3;
	while (TCPRecv(sockfd, (void *)recv_buffer, MAX_BUFFER) <= 0 && my_time < endTime);	// Check Receive Buffer of W5200
	if(my_time >= endTime){	// Check Timeout
		TCPClose(sockfd);
		return -1;
	}

	// TCP Socket Close
	TCPClose(sockfd);

#ifdef UPNP_DEBUG
	printf("\r\nReceiveData\r\n%s\r\n", recv_buffer);
#endif

	// Parse Replied Message
	return parseAddPort(recv_buffer);
}