int main(int argc, char const * const argv[])
{
	if (2 >= argc) {
		fprintf(stderr,
			"Usage: %s device baud "
				"[databits=8 [parity=N [stopbits=1]]]\n",
			argv[0]);
		return -1;
	}
        char const *const deviceName = argv[1];
        int const fdSerial = open(deviceName, O_RDWR);
        if (0 > fdSerial) {
		perror(deviceName);
		return -1;
	}
	fcntl(fdSerial, F_SETFD, FD_CLOEXEC);
	fcntl(fdSerial, F_SETFL, O_NONBLOCK);

	int baud = strtoul(argv[2], 0, 0);
	int databits = ((3 < argc) && (7 == strtoul(argv[3], 0, 0)))
		       ? 7
		       : 8 ;
	char parity = (4 < argc)
		      ? toupper(*argv[4])
		      : 'N' ;
	unsigned stopBits = ((5 < argc) && ('2' == *argv[5]))
			    ? 2
			    : 1 ;

	printf("device %s opened: %u baud, %d bits, parity %c\n", deviceName, baud, databits, parity);
	struct termios oldSerialState;
	setRaw(fdSerial, baud, databits, parity, stopBits, oldSerialState);

	struct termios oldStdinState;
	tcgetattr(0,&oldStdinState);
	/* set raw mode for keyboard input */
	struct termios newState = oldStdinState;
	newState.c_cc[VMIN] = 1;


	newState.c_lflag &= ~(ICANON | ECHO);				 // set raw mode for input
	newState.c_iflag &= ~(IXON | IXOFF | IXANY|INLCR|ICRNL|IUCLC);	 //no software flow control
	newState.c_oflag &= ~OPOST;			 //raw output
	tcsetattr(0, TCSANOW, &newState);

	signal(SIGINT, ctrlcHandler);
	pollfd fds[2];
	fds[0].fd = fdSerial ;
	fds[0].events = POLLIN | POLLERR ;
	fds[1].fd = fileno(stdin);
	fds[1].events = POLLIN | POLLERR ;

	while (!doExit) {
		::poll(fds, 2, 1000);
		for (unsigned i = 0 ; i < 2 ; i++) {
                        if (fds[i].revents & POLLIN) {
				char inBuf[80];
				int numRead = read(fds[i].fd, inBuf, sizeof(inBuf));
				if (0 < numRead) {
					int fdout = i ? fdSerial : 1;
					write(fdout,inBuf,numRead);
				}
			}
		}
	}

	tcsetattr(fdSerial, TCSANOW, &oldSerialState);
	tcsetattr(0, TCSANOW, &oldStdinState);

	close(fdSerial);
	return 0 ;
}