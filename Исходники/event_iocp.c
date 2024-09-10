struct event_iocp_port *
event_iocp_port_launch(void)
{
	struct event_iocp_port *port;
	int i;

	if (!extension_fns_initialized)
		init_extension_functions(&the_extension_fns);

	if (!(port = mm_calloc(1, sizeof(struct event_iocp_port))))
		return NULL;
	port->n_threads = 2;
	port->threads = calloc(port->n_threads, sizeof(HANDLE));
	if (!port->threads)
		goto err;

	port->port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, port->n_threads);
	port->ms = -1;
	if (!port->port)
		goto err;

	port->shutdownSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
	if (!port->shutdownSemaphore)
		goto err;

	for (i=0; i<port->n_threads; ++i) {
		uintptr_t th = _beginthread(loop, 0, port);
		if (th == (uintptr_t)-1)
			goto err;
		port->threads[i] = (HANDLE)th;
		++port->n_live_threads;
	}

	InitializeCriticalSection(&port->lock);

	return port;
err:
	if (port->port)
		CloseHandle(port->port);
	if (port->threads)
		mm_free(port->threads);
	if (port->shutdownSemaphore)
		CloseHandle(port->shutdownSemaphore);
	mm_free(port);
	return NULL;
}