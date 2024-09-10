int dim_get_scheduler_class(int *pclass)
{
	HANDLE hProc;
	DWORD ret;

#ifndef PXI
	hProc = GetCurrentProcess();

	ret = GetPriorityClass(hProc);
	if(ret == 0)
	  return 0;
	if(ret == IDLE_PRIORITY_CLASS)
		*pclass = -1;
/*
	else if(ret == BELOW_NORMAL_PRIORITY_CLASS)
		*pclass = -1;
*/
	else if(ret == NORMAL_PRIORITY_CLASS)
		*pclass = 0;
/*
	else if(ret == ABOVE_NORMAL_PRIORITY_CLASS)
		*pclass = 1;
*/
	else if(ret == HIGH_PRIORITY_CLASS)
		*pclass = 1;
	else if(ret == REALTIME_PRIORITY_CLASS)
		*pclass = 2;
	return 1;
#else
	*pclass = 0;
	return 0;
#endif
}