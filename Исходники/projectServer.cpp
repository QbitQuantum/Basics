int
main( int argc, char ** argv )
{

 	if ( argc == 2 && strcmp(argv[1],"help\0") == 0) {
 		fprintf( stderr, "%s", usage );
 	   	exit( -1 );
  	}
	else if(argc == 2 && (defaultPORT = isNumericAndValid(argv[1])) == -1)
	{
		fprintf( stderr, "%s", badInput );
 	   	exit( -1 );
	}

	
	struct sigaction signalAction;
	signalAction.sa_handler = child;

	
  	// Set the IP address and port for this server
 	struct sockaddr_in serverIPAddress; 
 	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
  	serverIPAddress.sin_family = AF_INET;
  	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
  	serverIPAddress.sin_port = htons((u_short) defaultPORT);
  
	
  	// Allocate a socket
  	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
  	if( masterSocket < 0) 
	{
  		perror("socket");
    		exit( -1 );
  	}

	
	// Set socket options to reuse port. Otherwise we will
  	// have to wait about 2 minutes before reusing the sae port number
  	int optval = 1; 
  	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,(char *) &optval, sizeof( int ) );
   
	
  	// Bind the socket to the IP address and port
  	int error = bind( masterSocket,(struct sockaddr *)&serverIPAddress,sizeof(serverIPAddress) );
  	if( error )
	{
   		perror("bind");
    		exit( -1 );
  	}
  
  	// Put socket in listening mode and set the 
  	// size of the queue of unprocessed connections
  	error = listen( masterSocket, QueueLength);
  	if( error ) 
	{
    		perror("listen");
    		exit( -1 );
  	}
	

	//Enter into infinate loop, wait till death.
	createThreadForEachRequest( masterSocket );
}