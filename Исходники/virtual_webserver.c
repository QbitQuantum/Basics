main ( ) 
{
	int sfd, cfd ;
	struct sockaddr_in serveraddr, clientaddr ;
	struct protoent *proto ;
	long int optval =  1;
	time_t ticks ;
	char buf[MAXLINE] ;
	u_int16_t port = 54321 ;
	socklen_t length ;
	
	proto = getprotobyname ( "tcp" ) ;
	sfd = Socket( AF_INET, SOCK_STREAM, proto->p_proto ) ;
	SetSockOpt ( sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof ( optval ) ) ;

	bzero ( &serveraddr, sizeof ( serveraddr ) ) ;
	serveraddr.sin_family = AF_INET ;
	serveraddr.sin_addr.s_addr = htonl ( INADDR_ANY ) ;
	serveraddr.sin_port = htons ( port ) ;

	Bind ( sfd, ( struct sockaddr *) &serveraddr, sizeof ( serveraddr ) ) ;
	Listen ( sfd, LISTENQ ) ;
	
	length = sizeof ( clientaddr ) ;
	for ( ; ; )  { 
		cfd = Accept ( sfd, (struct sockaddr *) &clientaddr, &length ) ;
		printf ( "Get Client" ) ;
		ticks = time ( NULL ) ;
		snprintf ( buf, sizeof ( buf ), "<html><body bgcolor=gray><h3>%.24s<//h3><//body><//html>\r\n", \
				ctime(&ticks) ) ;
		//snprintf ( buf, sizeof ( buf ), "%.24s\r\n", ctime(&ticks) ) ;
		writen ( cfd, buf, strlen(buf) ) ;
		close ( cfd ) ;

		printf ( "Connection Close\n" ) ;
	}
}