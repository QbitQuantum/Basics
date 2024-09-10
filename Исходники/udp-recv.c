int
main(int argc, char **argv)
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	int msgcnt = 0;			/* count # of messages we received */
	unsigned char buf[BUFSIZE];	/* receive buffer */


	/* create a UDP socket */

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	/* now loop, receiving data and printing what we received */
        int count = 0;
        int flag = 1;
        int i;
    	struct timeval start, end;
	printf("waiting on port %d\n", SERVICE_PORT);
	for (i = 0; i < 50000; i++) {
		//printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
                        if (flag){
 				flag = 0;
				gettimeofday(&start, NULL);
   			}
			buf[recvlen] = 0;
                        count+=recvlen;
			//printf("received message: \"%s\" (%d bytes) from %s\n", buf, recvlen, inet_ntoa(remaddr.sin_addr));
		}
		else
			printf("uh oh - something went wrong!\n");
		/*sprintf(buf, "ack %d", msgcnt++);
		printf("sending response \"%s\"\n", buf);
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");*/
	}
	gettimeofday(&end, NULL);
	double startm = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ; 
	double endm = (end.tv_sec) * 1000 + (end.tv_usec) / 1000 ; 
        double diff = endm - startm;
        printf("size: %d\ntime: %lf\nspeed: %lf KBps\n", count, diff, (count/1024)/(diff/1000));
        printf("speed: %lf Mbps\n", ((count*8)/(1024*1024))/(diff/1000));
	/* never exits */
}