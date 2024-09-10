//	*************************
//  Open Socket
//
int openSocket(char* interface)
{
  struct sockaddr_in multicastAddress;
  struct ip_mreqn mreqn;
  struct ip_mreq mreq;
	int multiSocket;
	int opt;
	char address[20];

  bzero(&multicastAddress, sizeof(struct sockaddr_in));
  multicastAddress.sin_family = AF_INET;
  multicastAddress.sin_port = htons(MULTICAST_PORT);
  multicastAddress.sin_addr.s_addr = INADDR_ANY;

	bzero(&destAddress, sizeof(struct sockaddr_in));
	destAddress.sin_family = AF_INET;
	destAddress.sin_port = htons(MULTICAST_PORT);
	destAddress.sin_addr.s_addr = inet_addr(MULTICAST_IP);

	if((multiSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		PERRNO("socket");
		return (-1);
	}

	memset((void *) &mreqn, 0, sizeof(mreqn));
	mreqn.imr_ifindex=if_NameToIndex(interface, address);
	if((setsockopt(multiSocket, SOL_IP, IP_MULTICAST_IF, &mreqn, sizeof(mreqn))) == -1)
	{
	  PERRNO("setsockopt");
		return (-1);
	}

	opt = 1;
	if((setsockopt(multiSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) == -1)
  {
    PERRNO("setsockopt");
		return (-1);
  }
 
	memset((void *) &mreq, 0, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
	mreq.imr_interface.s_addr = inet_addr(address);

	if((setsockopt(multiSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) == -1)
	{
	  PERRNO("setsockopt");
		return (-1);
	}
						
	/* Disable reception of our own multicast */
	opt = RECEIVE_OUR_DATA;
	if((setsockopt(multiSocket, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt))) == -1)
	{
		PERRNO("setsockopt");
		return (-1);
	}

	if(bind(multiSocket, (struct sockaddr *) &multicastAddress, sizeof(struct sockaddr_in)) == -1)
	{
		PERRNO("bind");
		return (-1);
	}

	return (multiSocket);
}