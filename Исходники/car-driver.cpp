int main(int argc, char** argv)
{
	FILE* fp = NULL;
    int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     portno = atoi(argv[1]);

     if (portno <= 0)
       return record(argv[2]);

     if (argc > 2)
     {
    	 fp = fopen(argv[2], "wb");
    	 if (fp == NULL)
    		 fprintf(stderr, "\nFile for command log has not been open.\n");
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
	
	 int flag = 1;
         int result = setsockopt(sockfd,            /* socket affected */
                                 IPPROTO_TCP,     /* set option at TCP level */
                                 TCP_NODELAY,     /* name of option */
                                 (char *) &flag,  /* the cast is historical
                                                         craft */
                                 sizeof(int));    /* length of option value */
         if (result < 0)
		error("ERROR on setting TCP_NODELAY option");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,256);

	  int fd = serialPort::open_port(PORT_NAME);
	  if (fd == -1)
	    return 1;
	  serialPort::configure_port(fd);

	  setPWM(fd, B_NTR, A_NTR);

	struct timeval tv;

	while (true)
	{
		 n = read(newsockfd, buffer, sizeof(WORD));
		 if (n < 0)
		 {
			 if (fp != NULL) fclose(fp);
			 error("ERROR reading from socket");
		 }
		 if (buffer[0] & XINPUT_GAMEPAD_START)
		 {
			if (fp != NULL) fclose(fp);
			puts("Received START. Exiting.");
			break;
		 }
		 printf("Here is the message: %04x\n", (buffer[1] << 8) | buffer[0]);
		 gettimeofday(&tv, NULL);

		 if ( buffer[0] & XINPUT_GAMEPAD_DPAD_DOWN)
		 {
				printf("DOWN Key pressed\n");
				renewB(&tv, false);
				printf("Now B is %d\n", channelB);
		 }
		 if ( buffer[0] & XINPUT_GAMEPAD_DPAD_UP)
		 {
				printf("UP Key pressed\n");
				renewB(&tv, true);
				printf("Now B is %d\n", channelB);
		 }
		 if ( buffer[0] & XINPUT_GAMEPAD_DPAD_LEFT)
		 {
				printf("LEFT Key pressed\n");
				renewA(&tv, false);
				printf("Now A is %d\n", channelA);
		 }
		 if ( buffer[0] & XINPUT_GAMEPAD_DPAD_RIGHT)
		 {
				printf("RIGHT Key pressed\n");
				renewA(&tv, true);
				printf("Now A is %d\n", channelA);
		 }
		 
		 if ( buffer[0] & ROBOT_STRAIGHT)
		 {
		 	printf("STRAIGHT is received\n");
		 	channelA = A_NTR;
		 	printf("Now A is %d\n", channelA);
		 }
		 if ( buffer[0] & ROBOT_CONTINUE)
		 {
		 	printf("CONTINUE is received\n");
		 }

		 setPWM(fd, channelB, channelA);

		 if (fp != NULL)
		 {
			 fwrite(&(tv.tv_sec), sizeof(tv.tv_sec), 1, fp);
		 	 fwrite(&(tv.tv_usec), sizeof(tv.tv_usec), 1, fp);
		 	 fwrite(buffer, sizeof(WORD), 1, fp);

		 	 double distance;
		 	 getDistanceFromSonar(fd, distance);
		   fwrite(&distance, sizeof(double), 1, fp);
		 }
	}


    n = write(newsockfd,"I got your message", 18);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);

	  // set defaults
	  setPWM(fd, B_NTR, A_NTR);

	  serialPort::close_port(fd);

	return 0;
}