int InitPort(int port_num, int baudrate,
             int databits, int stopbits, int parity)
{
	int fd;

	fd = OpenPort(port_num);

	if(fd == -1) {
		return -1;
	}

	SetSpeed(fd, baudrate);

	if(SetParity(fd, databits, stopbits, parity) == FALSE) {
		DEBUG(DL_ERROR, "Set Parity Error!\n");
		ClosePort(fd);
		return -1;
	}

	return fd;
}