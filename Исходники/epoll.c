void client_recv(int event_fd, Peer *peer)
{

  unsigned char headerBuf[HEADERSIZE]; 
  unsigned char dataBuf[DATASIZE];
  int len;

  memset(headerBuf, 0x00, HEADERSIZE);
  memset(dataBuf,   0x00, DATASIZE);

  Peer t_peer;
  t_peer.socket = event_fd;

  printf("recv start \n");
  len =  recvFrom(&t_peer, headerBuf, dataBuf);  
  

  int type = byteToInt(headerBuf, 0);

  printf("read end type : %d\n", type);

  if( len < 0 || len == 0 )
  {
      userpool_delete(event_fd, peer);
      close(event_fd);
      return;
  }
  
  printf("start type classify\n");
  switch(type)
  {
	case 0 : 
	{

		//userpool_send(headerBuf, peer);
		//userpool_send(dataBuf, peer);

		break;
	}

        case 1 :
	{
		Peer auth;
		auth.socket = g_epoll_auth;
		
		if(g_epoll_auth == 0)
		{
			//Exception
			printf("auth server not running \n");
			break;
		}	

		printf("login request to : %d, %d, %s \n", auth.socket, strlen(dataBuf), dataBuf);
		sendTo(&auth, 1, event_fd, strlen(dataBuf), dataBuf);

		break;
	}

	case 101 :
	{
		printf("Auth Serv Binding \n");
		
		g_epoll_auth = event_fd;

		printf("Auth Serv fd is : %d \n", event_fd);

		sendTo(g_epoll_auth, 102, event_fd , strlen(dataBuf), dataBuf);

		printf("Auth Serv Binding End \n");
 		break;
	}
	case 102 : 
	{
		printf("Dir Serv Binding \n");
	}
 
	default :
	{
		printf("default\n");
	}
  }

}