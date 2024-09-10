static unsigned __stdcall thread_proc(void* arg) {
	thread_params* proxy = (thread_params* )arg;
	proxy->func(proxy->arg);

	free(proxy);

	_endthreadex(0);

	return 0;
}