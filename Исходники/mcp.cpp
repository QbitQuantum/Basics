void main(int argc, char **argv)
{
	char *server_name = "mayaCommand";
	int  opt;

	char *program = new char[strlen(argv[0]) + 1];
	char *cptr;
	/*
	 * Grab a copy of the program name
	 */
#ifdef _WIN32
		_splitpath (argv[0], NULL, NULL, program, NULL);
#else
	cptr = strrchr(argv[0], '/');
	if (cptr)
	{
		strcpy(program, (cptr + 1));
	}
	else
	{
		strcpy(program, argv[0]);
	}
#endif

#ifdef DEVEL
	while ((opt = getopt(argc, argv, "Dhvi1w:n:")) != -1)
#else /* DEVEL */
	while ((opt = getopt(argc, argv, "hi1w:n:")) != -1)
#endif /* DEVEL */
	{	  
		switch (opt)
		{
		case 'h':
			show_usage++;
			break;

		case 'D':
			debug_mode++;
			break;

		case 'n':
			server_name = optarg;
			break;

		case 'v':
			verbose++;
			break;

		case '1':
			perLine++;
			numPerLine = 1;
			break;

		case 'i':
			interactive++;
			break;

		case 'w':
			perLine++;
			numPerLine = atoi(optarg);
			break;

		case GETOPTHUH:
			show_usage++;
		}
	}

	if (show_usage)
	{
		fprintf(stderr, "Usage:\n");
#ifdef DEVEL
		fprintf(stderr, "    %s [-Dvhi1] [-w num ] [-n name]\n", argv[0]);
#else /* DEVEL */
		fprintf(stderr, "    %s [-hi1] [-w num ] [-n name]\n", argv[0]);
#endif /* DEVEL */
		fprintf(stderr, "\n");
		fprintf(stderr, "        -h        Print this help message\n");
#ifdef DEVEL
		fprintf(stderr, "        -D        Set the debug flag\n");
		fprintf(stderr, "        -v        Set the vebose flag\n");
#endif /* DEVEL */
		fprintf(stderr, "        -n name   The server's UNIX socket name\n");
		fprintf(stderr, "        -1 	   Format the results one field per line\n");
		fprintf(stderr, "        -w num	   Format the results num fields per line\n");
		fprintf(stderr, "        -i 	   Interactive. Prompt each line with the server name.\n");

		fprintf(stderr, "\n");

		exit(1);
	}

	char command[5000] = {'\0' };

	int i;

    for ( i = optind ; i < argc; i++) {
		strcat(command,argv[i]);
		strcat(command," ");
	}
	if ( strlen(command) == 0 )
		readStdIn = 1;

	if ( verbose ) {
		fprintf(stderr,"// debug_mode  = %d\n", debug_mode);
		fprintf(stderr,"// readStdIn   = %d\n", readStdIn);
		fprintf(stderr,"// perLine     = %d\n", perLine);
		fprintf(stderr,"// numPerLine  = %d\n", numPerLine);
		fprintf(stderr,"// interactive = %d\n", interactive);
		fprintf(stderr,"// verbose     = %d\n", verbose);
	}

	if ( verbose ) {
		fprintf(stderr,"// %s: contacting server %s\n",program, server_name);
		fflush(stderr);
	}


	
	// Connect to the new server
	int fd = CapTcpOpen(server_name);

	if ( fd < 0 ) {
		fprintf(stderr,"// %s: couldn't connect to server %s\n"
				,program, server_name);
		exit(-1);
	} else if ( verbose ) {
		fprintf(stderr,"// %s: connected to server %s\n",program, server_name);
	}
		

	do {
		if ( readStdIn ) {
			if ( interactive ) {
				printf("%s %% ", server_name);
				fflush(stdout);
			}

			if ( NULL == fgets (command, 5000, stdin) ) 
				break;
		}

		if ( verbose )
			fprintf(stderr,"// %s: sending command %s\n",program, command);

		send(fd,command,strlen(command),0);

		if ( verbose )
			fprintf(stderr,"// %s: awaiting reply...",program);

		char reply[5000];
		int red = recv(fd,reply,4096,0);

		if ( verbose )
			fprintf(stderr,"// %s: recieved %d bytes\n",program,red);

		if ( red > 0)
		{
			if ( perLine ) {
				char *tabby = reply;
				int   count = 0;
				// replace \t with \n in reply
				while ( tabby = strchr ( tabby, '\t' ) ) {
					if ( (++count % numPerLine) == 0 )
						*tabby = '\n';
					tabby++;
				}
			}


			printf("%s",reply);
		}
		else {
			if ( verbose )
				printf("READ FAILED\n");
			break;
		}
	} while (readStdIn);

	if ( verbose )
		fprintf(stderr,"// %s: closing connection.\n",program);

	closesocket(fd);
}