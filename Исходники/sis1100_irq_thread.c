int
#else
void
#endif
sis1100_irq_thread(void* data)
{
    struct sis1100_softc* sc=(struct sis1100_softc*)data;
    enum handlercomm command;
    DECLARE_SPINLOCKFLAGS(flags);

#ifdef __linux__
#if LINUX_VERSION_CODE < 0x20600
    daemonize();
    snprintf(current->comm, sizeof(current->comm), "sis1100_%02d", sc->unit);
    SPIN_LOCK_IRQSAVE(current->sigmask_lock, flags);
    sigemptyset(&current->blocked);
    recalc_sigpending(current);
    SPIN_UNLOCK_IRQRESTORE(current->sigmask_lock, flags);
#endif
#endif /*__linux__*/

    while (1) {
#ifdef __NetBSD__
        tsleep(&sc->handler_wait, PCATCH, "thread_vmeirq", 0);
#elif __linux__
        /* prepare to sleep */
	__set_current_state(TASK_INTERRUPTIBLE);
        /* don't sleep if command!=0 */
        if (sc->handlercommand.command)
	    __set_current_state(TASK_RUNNING);
        else
            schedule();
#endif

        if (kthread_should_stop())
            return 0;

        SPIN_LOCK_IRQSAVE(sc->handlercommand.lock, flags);
        command=sc->handlercommand.command;
        sc->handlercommand.command=0;
        SPIN_UNLOCK_IRQRESTORE(sc->handlercommand.lock, flags);

#if 0
        pERROR(sc, "irq_thread: command=0x%x", command);
#endif

        _sis1100_irq_thread(sc, command);

#ifdef __linux__
	if (signal_pending (current)) {
	    SPIN_LOCK_IRQSAVE(current->SIGMASK_LOCK, flags);
	    flush_signals(current);
	    SPIN_UNLOCK_IRQRESTORE(current->SIGMASK_LOCK, flags);
	}
#endif /*__linux__*/

    }
#ifdef __linux__
    return 0;
#endif
}