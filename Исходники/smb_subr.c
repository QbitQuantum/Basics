/*
 * Create a kernel process/thread/whatever.  It shares it's address space
 * with proc0 - ie: kernel only.
 *
 * XXX only the SMB protocol uses this, we should convert this mess to a
 * pure thread when possible.
 */
int
smb_kthread_create(void (*func)(void *), void *arg,
		   struct proc **newpp, int flags, const char *fmt, ...)
{
	int error;
	__va_list ap;
	struct proc *p2;
	struct lwp *lp2;

	error = fork1(&lwp0, RFMEM | RFFDG | RFPROC | flags, &p2);
	if (error)
		return error;

	/* save a global descriptor, if desired */
	if (newpp != NULL)
		*newpp = p2;

	/* this is a non-swapped system process */
	p2->p_flags |= P_SYSTEM;
	p2->p_sigacts->ps_flag |= PS_NOCLDWAIT;

	lp2 = ONLY_LWP_IN_PROC(p2);

	/* set up arg0 for 'ps', et al */
	__va_start(ap, fmt);
	kvsnprintf(p2->p_comm, sizeof(p2->p_comm), fmt, ap);
	__va_end(ap);

	lp2->lwp_thread->td_ucred = crhold(proc0.p_ucred);

	/* call the processes' main()... */
	cpu_set_fork_handler(lp2,
			     (void (*)(void *, struct trapframe *))func, arg);
	start_forked_proc(&lwp0, p2);

	return 0;
}