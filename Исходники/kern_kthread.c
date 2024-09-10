/*
 * Same as kthread_create() but you can specify a custom stack size.
 */
int
kthread_create_stk(void (*func)(void *), void *arg,
		   struct thread **tdp, int stksize, const char *fmt, ...)
{
    thread_t td;
    __va_list ap;

    td = lwkt_alloc_thread(NULL, stksize, -1, TDF_VERBOSE);
    if (tdp)
	*tdp = td;
    cpu_set_thread_handler(td, kthread_exit, func, arg);

    __va_start(ap, fmt);
    kvsnprintf(td->td_comm, sizeof(td->td_comm), fmt, ap);
    __va_end(ap);

    lwkt_schedule(td);
    return 0;
}