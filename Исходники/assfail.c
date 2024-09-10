/*
 * Report a thread usage error.
 * Not called if _THREAD_ERROR_DETECTION=0.
 * Writes message and continues execution if _THREAD_ERROR_DETECTION=1.
 * Writes message and dumps core if _THREAD_ERROR_DETECTION=2.
 */
void
thread_error(const char *msg)
{
	char buf[800];
	uberdata_t *udp;
	ulwp_t *self;
	lwpid_t lwpid;

	/* avoid recursion deadlock */
	if ((self = __curthread()) != NULL) {
		if (assert_thread == self)
			_exit(127);
		enter_critical(self);
		(void) _lwp_mutex_lock(&assert_lock);
		assert_thread = self;
		lwpid = self->ul_lwpid;
		udp = self->ul_uberdata;
	} else {
		self = NULL;
		(void) _lwp_mutex_lock(&assert_lock);
		lwpid = _lwp_self();
		udp = &__uberdata;
	}

	(void) strcpy(buf, "\n*** _THREAD_ERROR_DETECTION: "
	    "thread usage error detected ***\n*** ");
	(void) strcat(buf, msg);

	(void) strcat(buf, "\n*** calling thread is ");
	ultos((uint64_t)(uintptr_t)self, 16, buf + strlen(buf));
	(void) strcat(buf, " thread-id ");
	ultos((uint64_t)lwpid, 10, buf + strlen(buf));
	(void) strcat(buf, "\n\n");
	(void) __write(2, buf, strlen(buf));
	if (udp->uberflags.uf_thread_error_detection >= 2)
		Abort(buf);
	assert_thread = NULL;
	(void) _lwp_mutex_unlock(&assert_lock);
	if (self != NULL)
		exit_critical(self);
}