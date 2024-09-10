void thread_create(thread_t *thread)
{
#ifdef ACE_WINDOWS
	thread->thread = (HANDLE)-1;
	_ReadWriteBarrier();
	
	thread->thread = (HANDLE)_beginthreadex(NULL, 0,
		&internal_win32_callback_wrapper, NULL, 0, &thread->thread_id);
#else
	pthread_attr_init(&thread->thread_attr);
	if (thread->flags & ACE_THREAD_JOINABLE) {
		pthread_attr_setdetachstate(&thread->thread_attr,
			PTHREAD_CREATE_JOINABLE);
	}
	
	if (pthread_create(&thread->thread, &thread->thread_attr,
		&internal_linux_callback_wrapper, (void *)thread)) {
		
		exit(ENOMEM);
	}
	
	pthread_attr_destroy(&thread->thread_attr);
#endif

	if (thread->flags & ACE_THREAD_DETACHED) {
		thread_detach(thread);
	}
}