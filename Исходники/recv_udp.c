int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  
	struct sockaddr_in  s_in, from;

	struct { 
		char head; 
		u_long  body; 
		char tail;
	} msg;

  // This creates a socket and assigns is to socket_fd
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  // Writes zeros to s_in for s_in length
  bzero((char *) &s_in, sizeof(s_in));

  // Assigns a protocal to the socket. AF_INET refers to addresses from the internet, specifically IP addresses
  s_in.sin_family = (short)AF_INET;

  // INADDR_ANY is the IPv4 wildcard address. It is usefor for applications that bind Internet domain sockets on mulihomed hosts
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);

  // htons converts MYPORT between host and network byte order
  s_in.sin_port = htons((u_short) MYPORT);

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);

  // bind assigns a name to an unnamed address. It assigns socket_fd to the socket address
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  for(;;) {
		fsize = sizeof(from);
    cc = Recvfrom(socket_fd, &msg, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
    printsin( &from, "recv_udp: ", "Packet from:");

    // Converts between host and network byte order so msg.body can be printed
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body),
    msg.tail); 
    fflush(stdout);
  }
  
  return 0;
}