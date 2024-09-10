int main(int ac, char *av[])
{
	//initialize a lot of struct and data points needed
    struct addrinfo *in, *pin;
    struct addrinfo start;
    int sockets[10], socket_num = 0;	
	allocatedMemory[0] = 0;
	myStruct *arg;
	pthread_t dthread;
	pthread_mutex_t *mutex;
	//clear the struct data values
	memset(&start, 0, sizeof start);//clear the object and then check for the right number of arguments passed
	
    if (ac < 3) 
	{
		printf("Usage: %s -p <port>\n", av[0]), exit(0);
	}
	if (ac == 4)
	{
		printf("Usage: %s -p <port> -R <path>\n", av[0]), exit(0);
	}
	else if (ac == 5) 
	{
		path = av[4];
	}
	//set the flags for the correct type of server
    start.ai_flags = AI_PASSIVE | AI_NUMERICSERV | AI_ADDRCONFIG;
    start.ai_protocol = IPPROTO_TCP; // only interested in TCP
    start.ai_family = AF_INET6;
	
	if (strcmp(av[1],"-p"))
		return -1;
	//gets the port number
    char *nport = av[2];

    int gai = getaddrinfo(NULL, nport, &start, &in);
	
    if (gai != 0)
	{
        gai_strerror(gai);
		exit(-1);
	}

    char printed_addr[1024];
    for (pin = in; pin; pin = pin->ai_next) {
        assert (pin->ai_protocol == IPPROTO_TCP);
        int gai = getnameinfo(pin->ai_addr, pin->ai_addrlen,
                             printed_addr, sizeof printed_addr, NULL, 0,
                             NI_NUMERICHOST);
		
        if (gai != 0)
            gai_strerror(gai), exit(-1);

        printf("%s: %s\n", pin->ai_family == AF_INET ? "AF_INET" :
                           pin->ai_family == AF_INET6 ? "AF_INET6" : "?", 
                           printed_addr);

        int s = socket(pin->ai_family, pin->ai_socktype, pin->ai_protocol);
        if (s == -1)
            perror("socket"), exit(-1);

        int opt = 1;
        setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));

        gai = bind(s, pin->ai_addr, pin->ai_addrlen);
        if (gai == -1 && errno == EADDRINUSE) {
            // ignore Linux limitation
            close(s);
            continue;
        }

        if (gai == -1)
            perror("bind"), exit(-1);
		//begin listening on the socket
        gai = listen(s, 10);
        if (gai == -1)
            perror("listen"), exit(-1);

        assert(socket_num < sizeof(sockets)/sizeof(sockets[0]));
        sockets[socket_num++] = s;
    }
	freeaddrinfo(in);
    assert(socket_num == 1);
	//initialize mutex before accepting
    struct sockaddr_storage rem;
    socklen_t remlen = sizeof (rem);
	
	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	while(1){
		//accept a connection
		arg = malloc(sizeof(myStruct));
		arg->mutex = mutex;
		//accept the connection
        arg->s = accept (sockets[0], (struct sockaddr *) &rem, &remlen);
		
		//if the connection works
        if (arg->s == -1)
		{
			pthread_mutex_lock(mutex);
            perror ("accept");
			pthread_mutex_unlock(mutex);
			free(arg);
			pthread_mutex_destroy(mutex);
			exit(-1);			
		}
		pthread_mutex_lock(mutex);

        char buffer[200];

		//get information about the connection
        if (getnameinfo ((struct sockaddr *) &rem, remlen, buffer, sizeof (buffer), NULL, 0, 0))
            strcpy (buffer, "???");   // hostname unknown

        char buf2[100];
        (void) getnameinfo ((struct sockaddr *) &rem, remlen, 
                buf2, sizeof (buf2), NULL, 0, NI_NUMERICHOST);
        printf ("connection from %s (%s)\n", buffer, buf2);
		
		
		//create the thread and call the echo functions
		//makes sure to lock and unlock and set the stack size
		pthread_mutex_unlock(mutex);
		arg->attribute = malloc(sizeof(pthread_attr_t));
		pthread_attr_init(arg->attribute);
		pthread_attr_setstacksize(arg->attribute, PTHREAD_STACK_MIN+8192);
		pthread_attr_setdetachstate(arg->attribute, PTHREAD_CREATE_DETACHED);
		pthread_create(&dthread, arg->attribute, echo, arg);
		
    }

    return 0;
}