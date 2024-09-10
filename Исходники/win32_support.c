ssize_t win32_fifo_read(void *buf, size_t nbyte)
{
	int check;
	DWORD readbuff;
	DWORD available;
	debug1("Reading pipe handle %p", fifohandle);
	if (!fifohandle) return 0;

	available = win32_fifo_read_peek(NULL);
	if (!available) return 0;

	/* This looks more like a hack than a proper check */
	readbuff = (nbyte > available) ? available : nbyte;
	debug("Starting ReadFileEx");
	check = ReadFileEx(fifohandle,buf,readbuff,&ov1,&ReadComplete);
	WaitForSingleObjectEx(fifohandle,INFINITE,TRUE);
	debug1("Read %ld bytes from pipe", readbuff);
	return (!check) ? 0 : readbuff;
}