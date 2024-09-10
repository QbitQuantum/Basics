int main(int argc, char *argv[]) {
	int i,j,k,portFD;
	unsigned char data[1024];

	gettimeofday(&tStart,NULL);

	output(1,"HP iPAQ 214 BT chip GPIO twiddling util v1.1\n----------------------------------\n");

#ifndef NOIO
	gpioInit(1);
#else
	output(1,"TESTING MODE - NOT USING IO\n");
#endif
	
	if(argc > 1 && strcmp(argv[1],"on")==0){
		portFD=openPort();
		if(portFD == -1){ return 0; }

		output(1,"Shutting down chip first...\n");
#ifndef NOIO
		shutdownChip();
		tcflush(portFD, TCIOFLUSH); //flush buffers again
#endif
		output(1,"Waiting 2 secs.\n");
		sleep(2);

		output(1,"Bringing up chip...\n");
		bringUpChip();

		output(1,"Resetting chip...\n");
#ifndef NOIO
		sendReset(portFD);	
#endif

		output(1,"Turning LED on.\n");
#ifndef NOIO
		gpioSet(3,1);
#endif
	
		output(1,"closing port...");	fflush(stdout);
		close(portFD);
		output(1,"done\n");

	}else if(argc > 1 && strcmp(argv[1],"off")==0){
		output(1,"Shutting down chip...\n");
#ifndef NOIO
		shutdownChip();
		gpioSet(3,0);	//turn LED off
#endif
	
	}else
		printf("usage %s on/off\n",argv[0]);
	
	
#ifndef NOIO
	gpioCleanup();
#endif
	
	return 0;
}