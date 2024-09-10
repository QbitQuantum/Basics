int main(int argc, char *argv[])
{
	state_t s;
	struct sockaddr_in6 addr;
	int optval;
	int i;
	
	s.port = DEFAULT_PORT;
	s.max_clients = DEFAULT_MAX_CLIENTS;
	
	opterr = 0;
	while((i = getopt(argc, argv, "p:m:")) != -1)
	{
		switch(i)
		{
		case 'p': s.port = atoi(optarg); break;
		case 'm': s.max_clients = atoi(optarg); break;
		case '?': exit_usage();
		}
	}
	
	if(optind < argc) exit_usage();
	if(s.max_clients <= 0)
	{
		fprintf(stderr, "Maximum clients is invalid\n");
		exit_usage();
	}
	
	/* Ignore annoying signal */
	signal(SIGPIPE, SIG_IGN);
	
	s.fin = stdin;
	
	/* Allocate memory for the frame in buffer */
	s.in = malloc(IN_SIZE);
	if(!s.in)
	{
		perror("malloc");
		return(-1);
	}
	s.in_len = 0;
	
	/* Same for output frame buffer */
	s.out = malloc(OUT_SIZE);
	if(!s.out)
	{
		perror("malloc");
		return(-1);
	}
	s.out_len = 0;
	s.out_key_frame_offset = 0;
	
	/* Create the listener sockets */
	s.in_sock = socket(AF_INET6, SOCK_STREAM, 0);
	if(s.in_sock < 0)
	{
		perror("socket");
		return(-1);
	}
	
	optval = 1;
	if(setsockopt(s.in_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		perror("setsockopt");
		return(-1);
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_addr = in6addr_any;
	addr.sin6_port = htons(s.port);
	
	if(bind(s.in_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		perror("bind");
		return(-1);
	}
	
	if(listen(s.in_sock, 10) < 0)
	{
		perror("listen");
		return(-1);
	}
	
	/* Allocate an empty client list */
	s.in_client = calloc(s.max_clients, sizeof(int));
	if(!s.in_client)
	{
		perror("calloc");
		return(-1);
	}
	
	/* Read the next frame */
	while(1)
	{
		fd_set rd;
		int maxfd, r;
		
		/* Check for incoming socket or H.264 data */
		FD_ZERO(&rd);
		FD_SET(fileno(s.fin), &rd);
		FD_SET(s.in_sock, &rd);
		maxfd = (fileno(s.fin) > s.in_sock ? fileno(s.fin) : s.in_sock) + 1;
		
		select(maxfd, &rd, NULL, NULL, NULL);
		
		if(FD_ISSET(s.in_sock, &rd))
		{
			struct sockaddr_in6 raddr;
			socklen_t raddrlen;
			char host[INET6_ADDRSTRLEN];
			
			/* Find a clear client slot */
			for(i = 0; i < s.max_clients; i++)
				if(s.in_client[i] == 0) break;
			
			/* No space? */
			if(i == s.max_clients)
			{
				/* Accept and close the socket */
				int sock = accept(s.in_sock, NULL, NULL);
				if(sock >= 0) close(sock);
				continue;
			}
			
			/* Get the socket */
			if((s.in_client[i] = accept(s.in_sock, NULL, NULL)) < 0)
			{
				perror("accept");
				s.in_client[i] = 0;
				continue;
			}
			
			raddrlen = sizeof(raddr);
			getpeername(s.in_client[i], (struct sockaddr *) &raddr, &raddrlen);
			if(inet_ntop(AF_INET6, &raddr.sin6_addr, host, sizeof(host)))
				fprintf(stderr, "Connection from %s\n", host);
			
			/* Write the buffered frames */
			r = send_block(s.in_client[i], s.out, s.out_len);
			if(r < 0)
			{
				/* Failed to send all data */
				close(s.in_client[i]);
				s.in_client[i] = 0;
			}
		}
		
		if(FD_ISSET(fileno(s.fin), &rd))
		{
			if(read_to_marker(&s) == EOF) break;
			
			if(s.in_len == 0) continue;
			
			switch(s.in[0])
			{
			case 0x27: /* Header frames? */
			case 0x28:
				s.out_len = s.out_key_frame_offset;
				write_frame(&s);
				s.out_key_frame_offset = s.out_len;
				break;
			
			case 0x25: /* Key frame */
				s.out_len = s.out_key_frame_offset;
				write_frame(&s);
				break;
			
			case 0x21: /* I frame */
				write_frame(&s);
				break;
			
			default:
				fprintf(stderr, "Unknown frame type 0x%02X\n", s.in[0]);
				break;
			}
			
			for(i = 0; i < s.max_clients; i++)
			{
				if(s.in_client[i] == 0) continue;
				
				/* Write the frame */
				r = send_frame(&s, s.in_client[i]);
				if(r < 0)
				{
					/* Failed to send all data */
					close(s.in_client[i]);
					s.in_client[i] = 0;
				}
			}
		}
	}
	
	close(s.in_sock);
	for(i = 0; i < s.max_clients; i++)
			if(s.in_client[i] != 0) close(s.in_client[i]);
	free(s.in_client);
	fclose(s.fin);
	free(s.in);
	
	fprintf(stderr, "EOF\n");
	
	return(0);
}