/* begin a comms session */
ComAPIHandle ComIPMulticastOpen(int buffersize, char *gamename, int mc_scope)
{
  LPWSAPROTOCOL_INFO protocols = 0;
  LPWSAPROTOCOL_INFO mc_protocol = 0;
  int numProtocols = 0;
  ComIP *c;
  int i, err;
  int trueValue=1;
  int falseValue=0;

  c = (ComIP*)malloc(sizeof(ComIP));

  if (InitWS2(&c->wsaData) == 0 ||
      FindProtocols(&protocols, &numProtocols) == 0) {
    free(c);
    return 0;
  }

  /* verify that we have a multi-cast protocol */
/*   for (i = 0; i < numProtocols && mc_protocol == 0; i++) { */
  for (i = 0; i < numProtocols; i++) {
    if (!mc_protocol &&
	protocols[i].dwServiceFlags1 & XP1_SUPPORT_MULTIPOINT &&
	!(protocols[i].dwServiceFlags1 & XP1_MULTIPOINT_CONTROL_PLANE) &&
	!(protocols[i].dwServiceFlags1 & XP1_MULTIPOINT_DATA_PLANE)) {
      mc_protocol = &protocols[i];
#ifdef DEBUG_COMMS
      printf("Found a suitable protocol:\n");
      printf("  iProtocol = %d\n", mc_protocol->iProtocol);
      printf("  iSocketType = %d\n", mc_protocol->iSocketType);
      printf("  iAddressFamily = %d\n", mc_protocol->iAddressFamily);
      printf("  flags = 0x%x\n", mc_protocol->dwServiceFlags1);
      printf("  msgsize = %d\n", mc_protocol->dwMessageSize);
      printf("  name = '%s'\n", mc_protocol->szProtocol);
    } else {
      printf("Unsuitable protocol:\n");
      printf("  iProtocol = %d\n", protocols[i].iProtocol);
      printf("  flags = 0x%x\n", protocols[i].dwServiceFlags1);
      printf("  msgsize = %d\n", protocols[i].dwMessageSize);
      printf("  name = '%s'\n", protocols[i].szProtocol);
#endif
    }
  }

  if (mc_protocol == 0) {
#ifdef DEBUG_COMMS
    printf("ComMulticastOpen: Found no suitable protocols\n");
#endif
    free(protocols);
    free(c);
    return 0;
  }

  /* initialize header data */
  c->apiheader.protocol = CAPI_IP_MULTICAST_PROTOCOL;
  c->apiheader.send_func = ComIPMulticastSend;
  c->apiheader.recv_func = ComIPMulticastGet;
  c->apiheader.send_buf_func = ComIPSendBufferGet;
  c->apiheader.recv_buf_func = ComIPRecvBufferGet;
  c->apiheader.addr_func = ComIPHostIDGet;
  c->apiheader.close_func = ComIPMulticastClose;

  c->buffer_size = sizeof(ComAPIHeader) + buffersize;

  c->send_buffer.buf = (char *)malloc(c->buffer_size);
  ComIPHostIDGet(&c->apiheader, c->send_buffer.buf);
#ifdef DEBUG_COMMS
  printf("ComAPIOpen -- got id 0x%x\n", 
	    ((ComAPIHeader *)c->send_buffer.buf)->sender);
#endif
  strncpy(((ComAPIHeader *)c->send_buffer.buf)->gamename, gamename,
		GAME_NAME_LENGTH);
  c->recv_buffer.buf = (char *)malloc(c->buffer_size);

  /* Incoming... */
#if 1
  c->recv_sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0,
#else
  c->recv_sock = WSASocket(FROM_PROTOCOL_INFO,
      			   FROM_PROTOCOL_INFO,
			   FROM_PROTOCOL_INFO,
                           mc_protocol, 0,
#endif
			WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF);

  if(c->recv_sock == INVALID_SOCKET)
    {
      err = WSAGetLastError();
      free(protocols);
      free(c);
      return 0;
    }

  memset ((char*)&comRecvAddr, 0, sizeof(comRecvAddr));
/*   comRecvAddr.sin_family       = mc_protocol->iAddressFamily; */
  comRecvAddr.sin_family       = AF_INET;
  comRecvAddr.sin_addr.s_addr  = htonl(0x9d000001);
  comRecvAddr.sin_addr.s_addr  = htonl(0x0);
  comRecvAddr.sin_port         = htons(CAPI_UDP_PORT);

#ifdef DEBUG_COMMS
  printf("binding (recv) socket #%d\n", c->recv_sock);
#endif
  if(err=bind(c->recv_sock, (struct sockaddr*)&comRecvAddr,sizeof(comRecvAddr)))
    {
      err = WSAGetLastError();
#ifdef DEBUG_COMMS
      printf("bind (recv) error #%d\n", err);
#endif
      free(protocols);
      free(c);
      return 0;
    }

/*   WSAIoctl(c->recv_sock, FIONBIO, &trueValue, sizeof(trueValue), 0, 0, 0, 0, 0); */
  WSAIoctl(c->recv_sock, SIO_MULTIPOINT_LOOPBACK, &falseValue, sizeof(falseValue),
      	0, 0, 0, 0, 0);
  WSAIoctl(c->recv_sock, SIO_MULTICAST_SCOPE, &mc_scope, sizeof(mc_scope),
      	0, 0, 0, 0, 0);

  c->send_sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0,
			WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF);
  if(c->send_sock == INVALID_SOCKET)
    {
      err = WSAGetLastError();
      free(protocols);
      free(c);
      return 0;
    }

  /* Outgoing... */
  memset ((char*)&comSendAddr, 0, sizeof(comSendAddr));
  comSendAddr.sin_family       = AF_INET;
/*   comSendAddr.sin_addr.s_addr  = htonl(INADDR_ANY); */
  comSendAddr.sin_addr.s_addr  = htonl(0xe0000001);
  comSendAddr.sin_port         = htons(CAPI_UDP_PORT);

/*   setsockopt(c->send_sock, SOL_SOCKET, SO_BROADCAST, */
/* 	    	(char *)&trueValue, sizeof(int) );   */

  c->recv_sock = WSAJoinLeaf(c->recv_sock,
      (struct sockaddr *)&comRecvAddr, sizeof(comRecvAddr),
      0, 0, 0, 0, JL_BOTH);
/*       0, 0, 0, 0, JL_RECEIVER_ONLY); */

  if (c->recv_sock == INVALID_SOCKET)
    {
      err = WSAGetLastError();
#ifdef DEBUG_COMMS
      printf("WSAJoinLeaf (recv) error #%d\n", err);
#endif
      free(protocols);
      free(c);
      return 0;
    }
  WSAIoctl(c->recv_sock, FIONBIO, &trueValue, sizeof(trueValue), 0, 0, 0, 0, 0);

  free(protocols);
  return (ComAPIHandle)c;
}