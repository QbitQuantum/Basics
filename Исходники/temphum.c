int main(int argc, char *argv[]) {
	fd = open("/dev/i2c-1", O_RDWR);


	int sockfd, portno, n, n2;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	char buffer2[256];
    
	portno= 8124;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("localhost");
	if (server == NULL){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
		
	float currentTemp = i2c_read(0x40, 0, 20000) * (165.0/65536.0) -40;
 	float currentHum =  i2c_read(0x40, 1, 20000) * (100.0/65536.0);


	while(1){
		float temp = i2c_read(0x40, 0, 20000) * (165.0/65536.0)-40;
		float hum  = i2c_read(0x40, 1, 20000) * (100.0/65536.0);

		//Check the discrepancy betwen the previous reading with the actual reading
		if((currentTemp - temp > 1 || currentTemp - temp < -1) || (currentHum-hum > 1 || currentHum-hum < -1)) {		
			//Redo reading. Discrepancy too big. Probably wrong
			currentTemp = temp;
			currentHum = hum;
			printf("Discrepancy too big. Reading again to make sure\n");
			continue;
		}
		
		currentTemp = temp;
		currentHum = hum;
		

		time_t current_time;
		char* c_time_string;

		current_time  = time(NULL);
		c_time_string = ctime(&current_time);

		if (temp != 0xffff && hum != 0xffff) {
			
			sprintf(buffer, "I2C-1 Temp/Hum %.2f %.2f Time %s", temp, hum, c_time_string);
			n = write(sockfd,buffer,strlen(buffer));
            
			if (n < 0)
				error("ERROR writing to socket");
		}

		sleep(2);
	}
	close(sockfd);
	return 0;
}