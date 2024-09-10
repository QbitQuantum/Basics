static void trapILL(int sig RECARG)
{
	static const char *emsg[] = {
			/* FPE_NOOP	  0*/ "SIGILL",
			/* ILL_ILLOPC 1*/ "illegal opcode",
			/* ILL_ILLTRP 2*/ "illegal trap",
			/* ILL_PRVOPC 3*/ "privileged opcode",
			/* ILL_ILLOPN 4*/ "illegal operand",
			/* 	5	*/ "illegal addressing mode",
			/* 	6	*/ "privileged register",
			/* 	7	*/ "coprocessor error",
			/* 	8	*/ "internal stack error"};
	CTX ctx = knh_getCurrentContext();
	record_signal(ctx, sig RECDATA);
	if(ctx != NULL) {
#if defined(K_USING_MINGW_)
		int si_code = 0;
#else
		int si_code = (si->si_code < 9) ? si->si_code : 0;
#endif /* defined(K_USING_MINGW_) */
		WCTX(ctx)->signal = sig;
		THROW_Halt(ctx, NULL, emsg[si_code]);
	}
	_Exit(EX_SOFTWARE);
}