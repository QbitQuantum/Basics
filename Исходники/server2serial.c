int init_serial(void){
	serial_fd = openPort(0);
	if(serial_fd < 0)
	{
		printf("serial open error.\n");
		exit(0);
	}
	//fd，115200， 
	setPara(serial_fd,6,8,1,0);
}