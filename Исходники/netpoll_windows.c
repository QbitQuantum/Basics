runtime·netpoll(bool block)
{
	OverlappedEntry entries[64];
	uint32 wait, qty, key, flags, n, i;
	int32 errno;
	net_op *op;
	G *gp;

	if(iocphandle == INVALID_HANDLE_VALUE)
		return nil;
	gp = nil;
	wait = 0;
	if(block)
		wait = INFINITE;
retry:
	if(runtime·GetQueuedCompletionStatusEx != nil) {
		n = nelem(entries) / runtime·gomaxprocs;
		if(n < 8)
			n = 8;
		if(block)
			m->blocked = true;
		if(runtime·stdcall(runtime·GetQueuedCompletionStatusEx, 6, iocphandle, entries, (uintptr)n, &n, (uintptr)wait, (uintptr)0) == 0) {
			m->blocked = false;
			errno = runtime·getlasterror();
			if(!block && errno == WAIT_TIMEOUT)
				return nil;
			runtime·printf("netpoll: GetQueuedCompletionStatusEx failed (errno=%d)\n", errno);
			runtime·throw("netpoll: GetQueuedCompletionStatusEx failed");
		}
		m->blocked = false;
		for(i = 0; i < n; i++) {
			op = entries[i].op;
			errno = 0;
			qty = 0;
			if(runtime·stdcall(runtime·WSAGetOverlappedResult, 5, runtime·netpollfd(op->pd), op, &qty, (uintptr)0, (uintptr)&flags) == 0)
				errno = runtime·getlasterror();
			handlecompletion(&gp, op, errno, qty);
		}
	} else {
		op = nil;
		errno = 0;
		qty = 0;
		if(block)
			m->blocked = true;
		if(runtime·stdcall(runtime·GetQueuedCompletionStatus, 5, iocphandle, &qty, &key, &op, (uintptr)wait) == 0) {
			m->blocked = false;
			errno = runtime·getlasterror();
			if(!block && errno == WAIT_TIMEOUT)
				return nil;
			if(op == nil) {
				runtime·printf("netpoll: GetQueuedCompletionStatus failed (errno=%d)\n", errno);
				runtime·throw("netpoll: GetQueuedCompletionStatus failed");
			}
			// dequeued failed IO packet, so report that
		}
		m->blocked = false;
		handlecompletion(&gp, op, errno, qty);
	}
	if(block && gp == nil)
		goto retry;
	return gp;
}