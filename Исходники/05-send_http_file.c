int main(int argc, char *argv[])
{
    int connection_file_descriptor; 
    char temp_line[BUFFER];
    char temp_char1, temp_char2;
    struct sockaddr_in server_address;
    struct sigaction act1;
    int characters_read;
    struct stat file_status;
    int data_file_descriptor;

    check_argument(argc,argv);

    act1.sa_handler = close_properly;
    sigemptyset(&act1.sa_mask);
    act1.sa_flags=0;
    sigaction(SIGINT, &act1, 0);
    
    listen_file_descriptor = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr  = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[1]));
    Bind(listen_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address));
    Listen(listen_file_descriptor, 5);
    
    while(1)
    {
	data_file_descriptor = Open(filename, O_RDONLY);
	Fstat(data_file_descriptor, &file_status);
	connection_file_descriptor = Accept(listen_file_descriptor, (struct sockaddr *) NULL, NULL);

	characters_read = Read(connection_file_descriptor, &temp_char1, 1);
	while(characters_read > 0)
	{
	    //printf("%c",temp_char1);
	    characters_read = Read(connection_file_descriptor, &temp_char2, 1);
	    if(temp_char2=='\n' && temp_char1=='\r')
	    {
	        temp_char1=temp_char2;
		//printf("%c",temp_char1);
		characters_read = Read(connection_file_descriptor, &temp_char2, 1);
		if(temp_char2=='\r')
		{
		    printf("Received request\n");
		    printf("Sending HTTP response\n");
		    break;
		}
	    }
	    temp_char1=temp_char2;
	}

	strcpy(temp_line, "HTTP/1.1 200 OK\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));
	strcpy(temp_line, "Server: Barjatiya\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));
	strcpy(temp_line, "Last-Modified: Fri, 29 Sep 2006 10:40:55 GMT\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));
	strcpy(temp_line, "Accept-Ranges: bytes\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));
	sprintf(temp_line, "Content-Length: %d\n", (int)file_status.st_size);
	Write(connection_file_descriptor, temp_line, strlen(temp_line));
	strcpy(temp_line, "Content-Type: text/html\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));
	strcpy(temp_line, "\n");
        Write(connection_file_descriptor, temp_line, strlen(temp_line));

	printf("Sending file\n");
	
	characters_read = Read(data_file_descriptor, temp_line, BUFFER -1);
	while(characters_read > 0)
	{
	    Write(connection_file_descriptor, temp_line, characters_read);
	    characters_read = Read(data_file_descriptor, temp_line, BUFFER -1);
	}

	Close(data_file_descriptor);
	printf("File send complete\n");
	Close(connection_file_descriptor);
	printf("Connection closed\n\n");
    }
        
    return 0;
}