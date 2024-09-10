int tube_wait(struct tube* tube)
{
	/* block on eventhandle */
	DWORD res = WSAWaitForMultipleEvents(
		1 /* one event in array */, 
		&tube->event /* the event to wait for, our pipe signal */, 
		0 /* wait for all events is false */, 
		WSA_INFINITE /* wait, no timeout */,
		0 /* we are not alertable for IO completion routines */
		);
	if(res == WSA_WAIT_TIMEOUT) {
		return 0;
	}
	if(res == WSA_WAIT_IO_COMPLETION) {
		/* a bit unexpected, since we were not alertable */
		return 0;
	}
	return 1;
}