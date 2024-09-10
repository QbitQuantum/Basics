static int r_debug_native_reg_write (RDebug *dbg, int type, const ut8* buf, int size) {

	// XXX use switch or so
	if (type == R_REG_TYPE_DRX) {
#if __i386__ || __x86_64__
#if __KFBSD__
		return (0 == ptrace (PT_SETDBREGS, dbg->pid,
			(caddr_t)buf, sizeof (struct dbreg)));
#elif __linux__
		return linux_reg_write (dbg, type, buf, size);
#elif __APPLE__
		if (1) return false; //disable until fixed ?? know why this
		return xnu_reg_write (dbg, type, buf, size);
#else
		//eprintf ("TODO: No support for write DRX registers\n");
		#if __WINDOWS__
		int tid = dbg->tid;
		int pid = dbg->pid;
		BOOL ret;
		HANDLE thread;
		CONTEXT ctx __attribute__((aligned (16)));
		memcpy (&ctx, buf, sizeof (CONTEXT));
		ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
		thread = w32_open_thread (pid, tid);
		ret=SetThreadContext (thread, &ctx)? true: false;
		CloseHandle(thread);
		return ret;
		#endif
		return false;
#endif
#else // i386/x86-64
		return false;
#endif
	} else
	if (type == R_REG_TYPE_GPR) {
#if __WINDOWS__ && !__CYGWIN__
		BOOL ret;
		CONTEXT ctx __attribute__((aligned (16)));
		memcpy (&ctx, buf, sizeof (CONTEXT));
		ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
	//	eprintf ("EFLAGS =%x\n", ctx.EFlags);
		HANDLE thread = w32_open_thread (dbg->pid, dbg->tid);
		ret = SetThreadContext (thread, &ctx)? true: false;
		CloseHandle (thread);
		return ret;
#elif __linux__
		return linux_reg_write (dbg, type, buf, size);
#elif __sun || __NetBSD__ || __KFBSD__ || __OpenBSD__
		int ret = ptrace (PTRACE_SETREGS, dbg->pid,
			(void*)(size_t)buf, sizeof (R_DEBUG_REG_T));
		if (sizeof (R_DEBUG_REG_T) < size)
			size = sizeof (R_DEBUG_REG_T);
		return (ret != 0) ? false: true;
#elif __APPLE__
		return xnu_reg_write (dbg, type, buf, size);
#else
#warning r_debug_native_reg_write not implemented
#endif
	} //else eprintf ("TODO: reg_write_non-gpr (%d)\n", type);
	return false;
}