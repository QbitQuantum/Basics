int set_serial (struct serial *s, struct serial_mode *serial_mode)

{

#ifdef WIN32

	COMMTIMEOUTS timeouts;
	DCB dcbSerial;
	memset (&dcbSerial, 0, sizeof (dcbSerial));
	dcbSerial.DCBlength = sizeof (dcbSerial);
	if (!GetCommState (s->h, &dcbSerial))
	{
		return (-1);
	}
	dcbSerial.BaudRate = serial_mode->baud_rate;
	dcbSerial.ByteSize = serial_mode->data_bits;
	switch (serial_mode->stop_bits)
	{
	case 1:
		dcbSerial.StopBits = ONESTOPBIT;
		break;
	case 2:
		dcbSerial.StopBits = TWOSTOPBITS;
		break;
	default:
		error (1, 0, "invalid stop bit setting");
	}
	switch (serial_mode->parity)
	{
	case UART_ODDPARITY:
		dcbSerial.Parity = ODDPARITY;
		dcbSerial.fParity = TRUE;
		break;
	case UART_EVENPARITY:
		dcbSerial.Parity = EVENPARITY;
		dcbSerial.fParity = TRUE;
		break;
	case UART_NOPARITY:
		dcbSerial.Parity = NOPARITY;
		dcbSerial.fParity = FALSE;
		break;
	default:
		error (1, 0, "invalid parity serial_mode");
	}
	if (!SetCommState (s->h, &dcbSerial))
	{
		error (0, 0, "could not set serial port settings");
		return (-1);
	}
	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts (s->h, &timeouts))
	{
		return (-1);
	}

#else

	struct termios termios;
	speed_t speed;
	tcgetattr (s->fd, &termios);
	cfmakeraw (&termios);
	termios.c_cflag &= ~CSIZE;
	switch (serial_mode->data_bits)
	{
	case 8:
		termios.c_cflag |= CS8;
		break;
	case 7:
		termios.c_cflag |= CS7;
		break;
	case 6:
		termios.c_cflag |= CS6;
		break;
	case 5:
		termios.c_cflag |= CS5;
		break;
	default:
		error (1, 0, "invalid serial byte size");
	}
	switch (serial_mode->stop_bits)
	{
	case 2:
		termios.c_cflag |= CSTOPB;
		break;
	case 1:
		termios.c_cflag &= ~CSTOPB;
		break;
	default:
		error (1, 0, "invalid number of stop bits");
	}
	switch (serial_mode->parity)
	{
	case UART_ODDPARITY:
		termios.c_cflag |= PARENB;
		termios.c_cflag |= PARODD;
		break;
	case UART_EVENPARITY:
		termios.c_cflag |= PARENB;
		termios.c_cflag &= ~PARODD;
		break;
	case UART_NOPARITY:
		termios.c_cflag &= ~PARENB;
		break;
	default:
		error (1, 0, "invalid parity serial_mode");
	}
	if (baudrate (serial_mode->baud_rate, &speed) == -1)
	{
		error (0, 0, "warning: unsupported baud rate: %d", serial_mode->baud_rate);
		return (-1);
	}
	if (cfsetspeed (&termios, speed) == -1) error (1, 0, "could not set serial baud rate");
	termios.c_cc [VTIME] = 1;
	termios.c_cc [VMIN] = 0;
	if (tcsetattr (s->fd, TCSANOW, &termios) == -1) error (1, 0, "could not set serial attributes");

#endif

	return (0);
}