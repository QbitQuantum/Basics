void VCInit(void)
{
	HANDLE cp,ct;


	cp = GetCurrentProcess();	//得到当前进程句柄
	ct = GetCurrentThread();	//得到当前线程伪句柄

	SetProcessAffinityMask(cp, 1L); //Select the first CPU

#if  FP_SAVE_RESTORE_EN > 0u
	Context.ContextFlags = CONTEXT_FULL; //Don't need to save CONTEXT_FLOATING_POINT
#else
	Context.ContextFlags = (CONTEXT_FULL | CONTEXT_FLOATING_POINT); //Important
#endif

	DuplicateHandle(cp, ct, cp, &MainHandle, 0, TRUE, 2);	//伪句柄转换，得到线程真句柄
}