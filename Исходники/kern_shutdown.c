void
vpanic(const char *fmt, va_list ap)
{
#ifdef SMP
	cpuset_t other_cpus;
#endif
	struct thread *td = curthread;
	int bootopt, newpanic;
	static char buf[256];

	spinlock_enter();

#ifdef SMP
	/*
	 * stop_cpus_hard(other_cpus) should prevent multiple CPUs from
	 * concurrently entering panic.  Only the winner will proceed
	 * further.
	 */
	if (panicstr == NULL && !kdb_active) {
		other_cpus = all_cpus;
		CPU_CLR(PCPU_GET(cpuid), &other_cpus);
		stop_cpus_hard(other_cpus);
	}

	/*
	 * Ensure that the scheduler is stopped while panicking, even if panic
	 * has been entered from kdb.
	 */
	td->td_stopsched = 1;
#endif

	bootopt = RB_AUTOBOOT;
	newpanic = 0;
	if (panicstr)
		bootopt |= RB_NOSYNC;
	else {
		bootopt |= RB_DUMP;
		panicstr = fmt;
		newpanic = 1;
	}

	if (newpanic) {
		(void)vsnprintf(buf, sizeof(buf), fmt, ap);
		panicstr = buf;
		cngrab();
		printf("panic: %s\n", buf);
	} else {
		printf("panic: ");
		vprintf(fmt, ap);
		printf("\n");
	}
#ifdef SMP
	printf("cpuid = %d\n", PCPU_GET(cpuid));
#endif

#ifdef KDB
	if (newpanic && trace_on_panic)
		kdb_backtrace();
	if (debugger_on_panic)
		kdb_enter(KDB_WHY_PANIC, "panic");
#endif
	/*thread_lock(td); */
	td->td_flags |= TDF_INPANIC;
	/* thread_unlock(td); */
	if (!sync_on_panic)
		bootopt |= RB_NOSYNC;
	kern_reboot(bootopt);
}