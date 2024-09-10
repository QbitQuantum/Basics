void CrashLog_Init()
{
#ifdef _M_AMD64
	CONTEXT ctx;
	RtlCaptureContext(&ctx);

	/* The stack pointer for AMD64 must always be 16-byte aligned inside a
	 * function. As we are simulating a function call with the safe ESP value,
	 * we need to subtract 8 for the imaginary return address otherwise stack
	 * alignment would be wrong in the called function. */
	s_safe_esp = (void *)(ctx.Rsp - 8);
#else
#if defined(_MSC_VER)
	_asm {
		mov s_safe_esp, esp
	}
#else
	__asm__("movl %esp, _s_safe_esp");
#endif
#endif

	/* SIGABRT is not an unhandled exception, so we need to intercept it. */
	signal(SIGABRT, CustomAbort);
#if defined(_MSC_VER)
	/* Don't show abort message as we will get the crashlog window anyway. */
	_set_abort_behavior(0, _WRITE_ABORT_MSG);
#endif
	SetUnhandledExceptionFilter(ExceptionHandler);
}