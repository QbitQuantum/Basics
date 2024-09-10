serial_t* serial_open(const char *device) 
{
	serial_t *h = calloc(sizeof(serial_t), 1);

	//COMMTIMEOUTS timeouts = {MAXDWORD, MAXDWORD, 3000, 0, 0};
    // shorter timeout
	COMMTIMEOUTS timeouts = {MAXDWORD, MAXDWORD, 500, 0, 0};

	/* Fix the device name if required */
	char *devName;
	if (strlen(device) > 4 && device[0] != '\\') {
		devName = calloc(1, strlen(device) + 5);
		sprintf(devName, "\\\\.\\%s", device);
	} else {
		devName = device;
	}

	/* Create file handle for port */
	h->fd = CreateFile(devName, GENERIC_READ | GENERIC_WRITE, 
			0, /* Exclusive access */
			NULL, /* No security */
			OPEN_EXISTING,
			0, //FILE_FLAG_OVERLAPPED,
			NULL);

	if (devName != device)
		free(devName);
	
	if(h->fd == INVALID_HANDLE_VALUE) 
		return NULL;

	SetupComm(h->fd, 4096, 4096); /* Set input and output buffer size */

	SetCommTimeouts(h->fd, &timeouts);

	SetCommMask(h->fd, EV_ERR); /* Notify us of error events */

	GetCommState(h->fd, &h->oldtio); /* Retrieve port parameters */
	GetCommState(h->fd, &h->newtio); /* Retrieve port parameters */

	PurgeComm(h->fd, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

	return h;
}