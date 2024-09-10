static int set_high_prio(MSTicker *obj){
	int precision=2;
	int result=0;
	char* env_prio_c=NULL;
	//int min_prio, max_prio, env_prio;
	int prio=obj->prio;
	
	if (prio>MS_TICKER_PRIO_NORMAL){
#ifdef WIN32
		MMRESULT mm;
		TIMECAPS ptc;
		mm=timeGetDevCaps(&ptc,sizeof(ptc));
		if (mm==0){
			if (ptc.wPeriodMin<(UINT)precision)
				ptc.wPeriodMin=precision;
			else
				precision = ptc.wPeriodMin;
			mm=timeBeginPeriod(ptc.wPeriodMin);
			if (mm!=TIMERR_NOERROR){
				ms_warning("timeBeginPeriod failed.");
			}
			ms_message("win32 timer resolution set to %i ms",ptc.wPeriodMin);
		}else{
			ms_warning("timeGetDevCaps failed.");
		}

		if(!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST)){
			ms_warning("SetThreadPriority() failed (%d)\n", GetLastError());
		}
#else
		struct sched_param param;
		int policy=SCHED_RR;
		memset(&param,0,sizeof(param));

		if (prio==MS_TICKER_PRIO_REALTIME)
			policy=SCHED_FIFO;
		
		min_prio = sched_get_priority_min(policy);
		max_prio = sched_get_priority_max(policy);
		env_prio_c = getenv("MS_TICKER_SCHEDPRIO");

		env_prio = (env_prio_c == NULL)?max_prio:atoi(env_prio_c);

		env_prio = MAX(MIN(env_prio, max_prio), min_prio);
		ms_message("Priority used: %d", env_prio);

		param.sched_priority=env_prio;
		if((result=pthread_setschedparam(pthread_self(),policy, &param))) {
			if (result==EPERM){
				/*
					The linux kernel has 
					sched_get_priority_max(SCHED_OTHER)=sched_get_priority_max(SCHED_OTHER)=0.
					As long as we can't use SCHED_RR or SCHED_FIFO, the only way to increase priority of a calling thread
					is to use setpriority().
				*/
				if (setpriority(PRIO_PROCESS,0,-20)==-1){
					ms_message("%s setpriority() failed: %s, nevermind.",obj->name,strerror(errno));
				}else{
					ms_message("%s priority increased to maximum.",obj->name);
				}
			}else ms_warning("%s: Set pthread_setschedparam failed: %s",obj->name,strerror(result));
		} else {
			ms_message("%s priority set to %s and value (%i)",obj->name,
			           policy==SCHED_FIFO ? "SCHED_FIFO" : "SCHED_RR", param.sched_priority);
		}
#endif
	}
	return precision;
}