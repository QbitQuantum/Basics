void StandardClock::sleepNS(MWTime time){ 
	

#ifdef USE_MACH_MOJO
	
	
	uint64_t now = mach_absolute_time();
	
	//mach_wait_until(now + (uint64_t)((long double)time / (long double)cv));
	mach_wait_until(now + (uint64_t)time * tTBI.denom / tTBI.numer);
	
#else
	
	long seconds = 0;
	long nano = 0;
	
	
	if((time - (MWTime)1000000000)){
		lldiv_t div = lldiv(time, (MWTime)1000000000);
		seconds = (long)(div.quot);
		nano = (long)(div.rem);
	} else {
//		mprintf("not bigger %lld", time - (MWTime)1000000000);
		nano = (long)time;
	}
	
//	mprintf("nanosleeping for %d seconds, %d ns", seconds, nano);
	
	struct timespec time_to_sleep;
	time_to_sleep.tv_sec = seconds;
	time_to_sleep.tv_nsec = nano; // check every 300 usec
	int result = nanosleep(&time_to_sleep, NULL);
	if(result < 0){
		char *resultstring = "Unknown error";
		switch(errno){
			case EINTR:
				resultstring = "Interrumpted by signal";
				break;
			case EINVAL:
				resultstring = "Invalid time value";
				break;
			case ENOSYS:
				resultstring = "Not supported";
				break;
			case EFAULT:
				resultstring = "Invalid address";
				break;
		}
		mprintf("Clock sleep error %d: %s (%d seconds, %d nano)", errno, resultstring, (long)seconds, (long)nano);
	}
	
#endif
}