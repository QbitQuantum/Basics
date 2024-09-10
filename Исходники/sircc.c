/*
 * main function of the simple client
 */
int main(int argc, char *argv[])
{
	char  sendbuf[MAX_MSG_LEN+1], recvbuf[MAX_MSG_LEN+1];
	int   server_sock, max_fd, ready, byte_read;
	int   stdineof = 0;
	char  *end;
	fd_set read_fds;

	/* display usage information */
	if (argc > 1){
		if ((strcmp(argv[1], "--help") == 0) || 
		    (strcmp(argv[1], "-h") == 0)){
			usage(argv[0]);
			return -1;
		}

		if (argc == 2){
			/* parse options if there are */
			if (strchr(argv[1], '.')){
				/* consider it to be an IP with ".", 
				   buggy with no further checking though */
				strcpy(server_ip, argv[1]);
			}else{
				server_port = atoi(argv[1]);
			}
		}else{
			strcpy(server_ip, argv[1]);
			server_port = atoi(argv[2]);
		}
	}

	printf("Connecting to server %s at port %d ...\n", server_ip, server_port);

	// connect to the server
	server_sock = socket_connect();

	printf("Connected, ready for commands:\n");

	// init read_fds
	FD_ZERO(&read_fds);

	while (1){

		// check which is ready, stdin or server_sock
		FD_SET(server_sock, &read_fds);
		FD_SET(fileno(stdin), &read_fds);
		max_fd = MAX(server_sock, fileno(stdin)) + 1;
		ready = Select(max_fd, &read_fds, 0, 0, 0);
		if (ready == 0)
			continue;

		// display server message first 
		if (FD_ISSET(server_sock, &read_fds)){
			do {
				bzero(recvbuf, MAX_MSG_LEN+1);
				byte_read = read(server_sock, recvbuf, MAX_MSG_LEN);
				if (byte_read > 0){
					recvbuf[byte_read] = '\0';
					printf("%s", recvbuf);

				}else if (byte_read == 0){

					// server send EOF
					if (stdineof == 1)
						return 0;
					printf("Server EOF, exit\n");
					exit(0);
				}else{
					if ((errno == EAGAIN) || (errno == EINTR))
						break;

					// error read
					printf("Error read, exit\n");
					close(server_sock);
					exit(0);
				}
			}while (byte_read > 0);
		}
	    
		// get a line from screen
		if (FD_ISSET(fileno(stdin), &read_fds)){
			if (!fgets(sendbuf, MAX_MSG_LEN, stdin)){
				// stdin EOF
				stdineof = 1;
				shutdown(server_sock, SHUT_WR);
				FD_CLR(fileno(stdin), &read_fds);
				continue;
			}

			// add \r\n if not
			if (!(end = strstr(sendbuf, "\r\n"))){
				end = strchr(sendbuf, '\n');
			}
			if (!end){
				printf("Error finding \\n\n");
				close(server_sock);
				exit(1);
			}
			strcpy(end, "\r\n");
			
			// send the line to the server
			Rio_writen(server_sock, sendbuf, strlen(sendbuf));
		}
	}

	close(server_sock);
	return 0;
}