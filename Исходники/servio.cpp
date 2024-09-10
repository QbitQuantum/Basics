int sio_open(int &argc, char ** &argv, const char*g_appname, const char*ver, const char*client) {
  
  char * port_str = getenv("SODACTRL_PORT");
  if (port_str) {
	// connect socket
	int port = atoi(port_str);
	if (port <= 0) {
	  fprintf(stderr, "Invalid port number (SODACTRL_PORT): %s\n", port_str);
	  return -1;
	};
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
	  perror("Cannot create socket"); return -1;
	};
	struct linger ling;
	ling.l_onoff = 1;
	ling.l_linger = 10; // try to send data for up to 10 seconds...
	if (setsockopt(fd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling)) < 0) {
	  perror("setsockopt(linger) failed");
	};

	struct sockaddr_in servaddr;
	struct hostent *host;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	const char * ip =  getenv("SODACTRL_IP");
	if (!ip) ip = "127.0.0.1";
	servaddr.sin_addr.s_addr =inet_addr(ip);

	if (connect(fd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0){
	  char bf[512];
	  snprintf(bf, sizeof(bf), "Cannot connect to %s:%d", ip, port);
	  perror(bf);
	  return -1;
	}
	ser_fd_read = ser_fd_write = fd;

  } else {
	// use STDIN/STDOUT
	ser_fd_read = 0;
	ser_fd_write = 1;
  };

  fcntl(ser_fd_read, F_SETFL, O_NONBLOCK);
  fcntl(ser_fd_write, F_SETFL, O_NONBLOCK);
  
  char * dbgc = getenv("SERVIO_DEBUG");
  sio_dbglevel = dbgc ? atoi(dbgc) : 50;

  char * commd = getenv("SERVIO_COMMDUMP");
  sio_commdump = commd ? atoi(commd) : 0;

  const char* proto = "106";

  if (g_appname[0] == '+') {
	proto = "101";
	g_appname++;
  };

  appname = strdup(g_appname);
  if (sio_write(SIO_DATA, "SYS-INIT\t%s\t%s\t%s\t%d\t%s",
				proto, appname, ver, getpid(), (client?client:"")) == -1) {
	perror("Cannot write to server");
	return -1;
  };

  
  noserv_mode = 0; 
  // no need for 'SYS_WELCOME' when debug env is set - thus can run from console easliy
  if (isatty(ser_fd_read) && (ser_fd_read != ser_fd_write)) {
	noserv_mode = 1;
	printf("Using NO-SERVER mode - taking data, commands from tty, disabling GET\n");
	return 0;
  };

  // the only possible response to SYS-INIT with version 101 is SYS-WELCOME
  // wait 10 seconds for it...
  std::string resp;
  if (sio_read(resp, 10*1000) <= 0)  { 
	fprintf(stderr, "Server initial response timed out\n");
	return -1; // no reponse
  };
  if (resp.substr(0, 12)!="SYS-WELCOME\t") {
	for (int i=0; i<resp.length(); i++) 
	  if (resp[i]<32) resp[i]='#';
	fprintf(stderr, "Server initial response is junk: %s\n", resp.c_str());
	return -1;
  };
  return 0;
};