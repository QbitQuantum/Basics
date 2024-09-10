static os_status_t OS_THREAD_CALLING_CONVENTION
_thread_create(os_thread_function_t func, void *data, os_size_t stack_size, uint8_t detached, os_thread_t **newthread)
{
	os_thread_t *thread = NULL;
	os_status_t status = OS_FAIL;

	if (*newthread) {
		*newthread = NULL;
	}

	if (!func || !(thread = (os_thread_t *)os_calloc(1, sizeof(os_thread_t)))) {
		goto done;
	}

	thread->private_data = data;
	thread->function = func;
	thread->stack_size = stack_size;
	thread->detached = detached;

#if defined(WIN32)
	thread->handle = (void *)_beginthreadex(NULL, (unsigned)thread->stack_size, (unsigned int (__stdcall *)(void *))thread_launch, thread, 0, NULL);
	if (!thread->handle) {
		goto fail;
	}
	if (detached) {
		CloseHandle(thread->handle);
	}

	status = OS_SUCCESS;
	goto done;
#else
	
	if (pthread_attr_init(&thread->attribute) != 0) {
		goto fail;
	}

	if (detached) {
		if (pthread_attr_setdetachstate(&thread->attribute, PTHREAD_CREATE_DETACHED) != 0) {
			goto failpthread;
		}
	}

	if (thread->stack_size && pthread_attr_setstacksize(&thread->attribute, thread->stack_size) != 0) {
		goto failpthread;
	}

	if (pthread_create(&thread->handle, &thread->attribute, thread_launch, thread) != 0) {
		goto failpthread;
	}

	if (newthread) {
		*newthread = thread;
	}
	status = OS_SUCCESS;
	goto done;
 failpthread:
	pthread_attr_destroy(&thread->attribute);
#endif

 fail:
	if (thread) {
		os_safe_free(thread);
	}
 done:
	return status;
}