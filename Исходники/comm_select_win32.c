static int
do_comm_select(int msec)
{
    int num, saved_errno;
    struct timeval tv;
    fd_set readfds;
    fd_set writefds;
    fd_set errfds;
    int fd;

    if (nreadfds + nwritefds == 0) {
	assert(shutting_down);
	return COMM_SHUTDOWN;
    }
    memcpy(&readfds, &global_readfds, sizeof(fd_set));
    memcpy(&writefds, &global_writefds, sizeof(fd_set));
    memcpy(&errfds, &global_writefds, sizeof(fd_set));
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    statCounter.syscalls.selects++;
    num = select(Biggest_FD + 1, &readfds, &writefds, &errfds, &tv);
    saved_errno = errno;
    getCurrentTime();
    debug(5, 5) ("do_comm_select: %d fds ready\n", num);
    if (num < 0) {
	if (ignoreErrno(saved_errno))
	    return COMM_OK;

	debug(5, 1) ("comm_select: select failure: %s\n", xstrerror());
	return COMM_ERROR;
    }
    statHistCount(&statCounter.select_fds_hist, num);

    if (num == 0)
	return COMM_TIMEOUT;

    for (fd = 0; fd <= Biggest_FD; fd++) {
	int read_event = __WSAFDIsSet(fd_table[fd].win32.handle, &readfds);
	int write_event = __WSAFDIsSet(fd_table[fd].win32.handle, &writefds) || __WSAFDIsSet(fd_table[fd].win32.handle, &errfds);
	if (read_event || write_event)
	    comm_call_handlers(fd, read_event, write_event);
    }
    return COMM_OK;
}