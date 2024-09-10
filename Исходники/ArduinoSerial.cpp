    int ArduinoSerial::openPort(const char *portName)
    {


        _portName = std::string(portName);
        _portOpened = false;
        triedToConfigureAgain = false;
        closeSerial();
        fd = 0;
        _numberOfChannels = 1;
#if defined(__APPLE__) || defined(__linux__)
        struct termios options;

        fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);//O_SHLOCK
        sleep(2);
        int bits;
#endif
#ifdef __APPLE__
        std::stringstream sstm;

        if (fd < 0) {
            sstm << "Unable to open " << portName << ", " << strerror(errno);
            errorString = sstm.str();
            std::cout<<"Unable to open "<<portName<<", "<<strerror(errno)<<"\n";
            return -1;
        }
        if (ioctl(fd, TIOCEXCL) == -1) {
            close(fd);
            sstm << "Unable to get exclussive access to port " << portName;;
            errorString = sstm.str();
            std::cout<<"Unable to get exclussive access to port "<<portName<<"\n";
            return -1;
        }
        if (ioctl(fd, TIOCMGET, &bits) < 0) {
            close(fd);
            sstm <<"Unable to query serial port signals on " << portName;
            errorString = sstm.str();
            std::cout<<"Unable to query serial port signals on "<<portName<<"\n";
            return -1;
        }
        bits &= ~(TIOCM_DTR | TIOCM_RTS);
        if (ioctl(fd, TIOCMSET, &bits) < 0) {
            close(fd);
            sstm <<"Unable to control serial port signals on " << portName;
            errorString = sstm.str();
            std::cout<<"Unable to control serial port signals on "<<portName<<"\n";
            return -1;
        }
        struct termios settings_orig;
        if (tcgetattr(fd, &settings_orig) < 0) {
            close(fd);
            sstm <<"Unable to access baud rate on port " << portName;
            errorString = sstm.str();
            std::cout<<"Unable to access baud rate on port "<<portName<<"\n";
            return -1;
        }
#endif
#ifdef __linux__
 // struct serial_struct kernel_serial_settings;
    struct termios settings_orig;
    //struct termios settings;
    if (fd < 0)
    {
        if (errno == EACCES)
        {
            std::cout<<"Unable to access "<< portName<< ", insufficient permission";
            // TODO: we could look at the permission bits and owner
            // to make a better message here
        }
        else if (errno == EISDIR)
        {
            std::cout<< "Unable to open " << portName <<
                     ", Object is a directory, not a serial port";
        }
        else if (errno == ENODEV || errno == ENXIO)
        {
            std::cout<< "Unable to open " << portName <<
                     ", Serial port hardware not installed";
        }
        else if (errno == ENOENT)
        {
            std::cout<< "Unable to open " << portName <<
                     ", Device name does not exist";
        }
        else
        {
            std::cout<< "Unable to open " << portName; //<<

        }
        return -1;
    }
    if (ioctl(fd, TIOCMGET, &bits) < 0)
    {
        close(fd);
        std::cout<< "Unable to query serial port signals";
        return -1;
    }
    bits &= ~(TIOCM_DTR | TIOCM_RTS);
    if (ioctl(fd, TIOCMSET, &bits) < 0)
    {
        close(fd);
        std::cout<< "Unable to control serial port signals";
        return -1;
    }
    if (tcgetattr(fd, &settings_orig) != 0)
    {
        close(fd);
        std::cout<< "Unable to query serial port settings (perhaps not a serial port)";
        return -1;
    }
    /*memset(&settings, 0, sizeof(settings));
    settings.c_iflag = IGNBRK | IGNPAR;
    settings.c_cflag = CS8 | CREAD | HUPCL | CLOCAL;
    Set_baud(baud_rate);
    if (ioctl(port_fd, TIOCGSERIAL, &kernel_serial_settings) == 0) {
    	kernel_serial_settings.flags |= ASYNC_LOW_LATENCY;
    	ioctl(port_fd, TIOCSSERIAL, &kernel_serial_settings);
    }
    tcflush(port_fd, TCIFLUSH);*/
#endif
#if defined(__APPLE__) || defined(__linux__)
        if (fd == -1)
        {
            std::cout<<"Can't open serial port\n";
            return -1;
        }
        fcntl(fd, F_SETFL, 0);    // clear all flags on descriptor, enable direct I/O
        tcgetattr(fd, &options);   // read serial port options
        // enable receiver, set 8 bit data, ignore control lines
        options.c_cflag |= (CLOCAL | CREAD | CS8);
        // disable parity generation and 2 stop bits
        options.c_cflag &= ~(PARENB | CSTOPB);

        //cfsetispeed(&options, B9600);
        //cfsetospeed(&options, B9600);

        cfsetispeed(&options, B230400);
        cfsetospeed(&options, B230400);

        // set the new port options
        tcsetattr(fd, TCSANOW, &options);
#endif

#ifdef _WIN32

	COMMCONFIG cfg;
	COMMTIMEOUTS timeouts;
	int got_default_cfg=0, port_num;
	char buf[1024], name_createfile[64], name_commconfig[64], *p;
	DWORD len;

	snprintf(buf, sizeof(buf), "%s", _portName.c_str());
	p = strstr(buf, "COM");
	if (p && sscanf(p + 3, "%d", &port_num) == 1) {
		printf("port_num = %d\n", port_num);
		snprintf(name_createfile, sizeof(name_createfile), "\\\\.\\COM%d", port_num);
		snprintf(name_commconfig, sizeof(name_commconfig), "COM%d", port_num);
	} else {
		snprintf(name_createfile, sizeof(name_createfile), "%s", _portName.c_str());
		snprintf(name_commconfig, sizeof(name_commconfig), "%s", _portName.c_str());
	}
	len = sizeof(COMMCONFIG);
	if (GetDefaultCommConfig(name_commconfig, &cfg, &len)) {
		// this prevents unintentionally raising DTR when opening
		// might only work on COM1 to COM9
		got_default_cfg = 1;
		memcpy(&port_cfg_orig, &cfg, sizeof(COMMCONFIG));
		cfg.dcb.fDtrControl = DTR_CONTROL_DISABLE;
		cfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;
		SetDefaultCommConfig(name_commconfig, &cfg, sizeof(COMMCONFIG));
	} else {
		printf("error with GetDefaultCommConfig\n");
	}
	port_handle = CreateFile(name_createfile, GENERIC_READ | GENERIC_WRITE,
	   0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (port_handle == INVALID_HANDLE_VALUE) {
		win32_err(buf);
		//error_msg =  "Unable to open " + _portName + ", " + buf;
		return -1;
	}
	len = sizeof(COMMCONFIG);
	if (!GetCommConfig(port_handle, &port_cfg, &len)) {
		CloseHandle(port_handle);
		win32_err(buf);
		//error_msg = "Unable to read communication config on " + _portName + ", " + buf;
		return -1;
	}
	if (!got_default_cfg) {
		memcpy(&port_cfg_orig, &port_cfg, sizeof(COMMCONFIG));
	}
	// http://msdn2.microsoft.com/en-us/library/aa363188(VS.85).aspx
	port_cfg.dcb.BaudRate = 230400;
	port_cfg.dcb.fBinary = TRUE;
	port_cfg.dcb.fParity = FALSE;
	port_cfg.dcb.fOutxCtsFlow = FALSE;
	port_cfg.dcb.fOutxDsrFlow = FALSE;
	port_cfg.dcb.fDtrControl = DTR_CONTROL_DISABLE;
	port_cfg.dcb.fDsrSensitivity = FALSE;
	port_cfg.dcb.fTXContinueOnXoff = TRUE;	// ???
	port_cfg.dcb.fOutX = FALSE;
	port_cfg.dcb.fInX = FALSE;
	port_cfg.dcb.fErrorChar = FALSE;
	port_cfg.dcb.fNull = FALSE;
	port_cfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;
	port_cfg.dcb.fAbortOnError = FALSE;
	port_cfg.dcb.ByteSize = 8;
	port_cfg.dcb.Parity = NOPARITY;
	port_cfg.dcb.StopBits = ONESTOPBIT;
	if (!SetCommConfig(port_handle, &port_cfg, sizeof(COMMCONFIG))) {
		CloseHandle(port_handle);
		win32_err(buf);
		//error_msg = "Unable to write communication config to " + name + ", " + buf;
		return -1;
	}
	if (!EscapeCommFunction(port_handle, CLRDTR | CLRRTS)) {
		CloseHandle(port_handle);
		win32_err(buf);
		//error_msg = "Unable to control serial port signals on " + name + ", " + buf;
		return -1;
	}
	// http://msdn2.microsoft.com/en-us/library/aa363190(VS.85).aspx
	// setting to all zeros means timeouts are not used
	//timeouts.ReadIntervalTimeout		= 0;
	timeouts.ReadIntervalTimeout		= MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier	= 0;
	timeouts.ReadTotalTimeoutConstant	= 0;
	timeouts.WriteTotalTimeoutMultiplier	= 0;
	timeouts.WriteTotalTimeoutConstant	= 0;
	if (!SetCommTimeouts(port_handle, &timeouts)) {
		CloseHandle(port_handle);
		win32_err(buf);
		//error_msg = "Unable to write timeout settings to " + name + ", " + buf;
		return -1;
	}

#endif // _WIN32

        circularBuffer[0] = '\n';

        cBufHead = 0;
        cBufTail = 0;

        serialCounter = 0;

        _portOpened = true;


        setNumberOfChannelsAndSamplingRate(1, maxSamplingRate());


        return fd;
    }