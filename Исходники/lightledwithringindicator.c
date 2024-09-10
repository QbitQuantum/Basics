int main() {
	int serial, control, fd, timel, timeu, ticks, bitset;
	bitset = TIOCM_DTR;	//Mask For the DTR Pin bit
	setupPort43();		//Sets up Port43
	settimer();		//Sets up Timer(port42) and starts it
	fd = open("/dev/ttyUSB0", O_RDWR);	//Opens the Serial port
	if(fd == -1){		//Error Checking
   	 	printf("Could Not Open Serial Port");
		exit(1);
  	}
	while(1){
		ioctl(fd, TIOCMGET, &serial);	//Ioctl using TIOCMGET
								//Reads from the serial 
//port and places in serial
		if((serial & TIOCM_RI) == TIOCM_RI) control = 3750;
		else control = 256;
		timel = inb(0x42);
		timeu = inb(0x42);
		ticks = (timeu << 8) + timel;
		if(ticks >= control) ioctl(fd, TIOCMSET, &bitset);
		else ioctl(fd, TIOCMSET, &bitset);
		//Turns LED on and off
		printf("%d\n", control);
		
	}
	close(fd);
	return 0;
}