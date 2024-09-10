int connect_with_timeout(char *host, int port, int timeout_sec,
		int timeout_usec, char *account)
{
	  int res, valopt;
	  struct sockaddr_in addr;
	  long arg;
	  fd_set myset;
	  struct timeval tv;
	  socklen_t lon;
	  char buffer[181] = {0};

	  /* Base64 */
	  char sender[181] = {0};
	  char receiver[181] = {0};
	  int rc;

	  // Create socket
	  int soc = socket(AF_INET, SOCK_STREAM, 0);

	  // Set non-blocking
	  arg = fcntl(soc, F_GETFL, NULL);
	  arg |= O_NONBLOCK;
	  fcntl(soc, F_SETFL, arg);

	  // Trying to connect with timeout
	  addr.sin_family = AF_INET;
	  addr.sin_port = htons(port);
	  addr.sin_addr.s_addr = inet_addr(host);
	  res = connect(soc, (struct sockaddr *)&addr, sizeof(addr));

	  if (res < 0) {
	     if (errno == EINPROGRESS) {
	        tv.tv_sec = timeout_sec;
	        tv.tv_usec = timeout_usec;
	        FD_ZERO(&myset);
	        FD_SET(soc, &myset);
	        if (select(soc+1, NULL, &myset, NULL, &tv) > 0) {
	           lon = sizeof(int);
	           getsockopt(soc, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
	           if (valopt) {
	              return -2;
	           }
	        }
	        else {
	           return -3;
	        }
	     }
	     else {
	        return -4;
	     }
	  }

	  // Set to blocking mode again...
	  arg = fcntl(soc, F_GETFL, NULL);
	  arg &= (~O_NONBLOCK);
	  fcntl(soc, F_SETFL, arg);

	  rc = Base64Encode(account, sender, BUFFFERLEN);
	  send(soc,sender,181,NULL);
	  recv(soc, buffer, 181, NULL);
	  rc = Base64Decode(buffer, receiver, BUFFFERLEN);

	  printf ("Connect to server: account= %s, buffer = %s\n", account, buffer);
	  if (strcmp(buffer,"Failed"))
	  {
		  return soc;
	  }
	  else
	  {
		shutdown(soc,2);
		return -5;
	  }
}