bool Port::OpenPort(const char* name){

	struct termios newtio;
    struct serial_struct serinfo;
	double baudrate = 1000000.0; //bps (1Mbps)
    
    ClosePort();

    if((m_Socket_fd = open(name, O_RDWR|O_NOCTTY|O_NONBLOCK)) < 0){
        printf("failed!/n");
        ClosePort();
        return false;
    }

	// You must set 38400bps!
	memset(&newtio, 0, sizeof(newtio));
    newtio.c_cflag      = B38400|CS8|CLOCAL|CREAD;
    newtio.c_iflag      = IGNPAR;
    newtio.c_oflag      = 0;
    newtio.c_lflag      = 0;
    newtio.c_cc[VTIME]  = 0;
    newtio.c_cc[VMIN]   = 0;
    tcsetattr(m_Socket_fd, TCSANOW, &newtio);


	printf("Set %.1fbps ", baudrate);

	// Set non-standard baudrate
    if(ioctl(m_Socket_fd, TIOCGSERIAL, &serinfo) < 0){
        printf("failed!/n");
        ClosePort();
        return false;
    }

    serinfo.flags &= ~ASYNC_SPD_MASK;
    serinfo.flags |= ASYNC_SPD_CUST;
    serinfo.custom_divisor = serinfo.baud_base / baudrate;
	
    if(ioctl(m_Socket_fd, TIOCSSERIAL, &serinfo) < 0)
	{
		printf("failed!/n");
        ClosePort();
        return false;
	}

	tcflush(m_Socket_fd, TCIFLUSH);

    m_ByteTransferTime = (1000.0 / baudrate) * 12.0;
	
    printf("Open port success!\n");

    return true;

}