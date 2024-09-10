DWORD FileProcessor::Run(LPVOID /*arg*/)
{
	if( PP ){
	 FileEntry entry;
		nProcessed = 0;
		while( !PP->quitRequested() && (isBackwards ? PP->getBack(entry) : PP->getFront(entry)) ){
		 // create a scoped lock without closing it immediately
		 CRITSECTLOCK::Scope scp(PP->ioLock, 0);
			scope = &scp;
			currentEntry = &entry;
			_InterlockedIncrement(&PP->nProcessing);
			entry.compress( this, PP );
			_InterlockedDecrement(&PP->nProcessing);
			_InterlockedIncrement(&PP->nProcessed);
			currentEntry = NULL;
			nProcessed += 1;
			scope = NULL;

			runningTotalRaw += entry.fileInfo.st_size;
			runningTotalCompressed += (entry.compressedSize > 0)? entry.compressedSize : entry.fileInfo.st_size;
			/*if( PP->verbose() > 1 )*/{
#if defined(__MACH__)
                mach_port_t thread = mach_thread_self();
				mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
				thread_basic_info_data_t info;
				int kr = thread_info(thread, THREAD_BASIC_INFO, (thread_info_t) &info, &count);
				if( kr == KERN_SUCCESS ){
					 userTime = info.user_time.seconds + info.user_time.microseconds * 1e-6;
					 systemTime = info.system_time.seconds + info.system_time.microseconds * 1e-6;
					 avCPUUsage += info.cpu_usage * 100.0 / TH_USAGE_SCALE;
					 threadInfo = info;
					 hasInfo = true;
				}
				mach_port_deallocate(mach_task_self(), thread);
#elif defined(linux)
				struct rusage rtu;
				if (!getrusage(RUSAGE_THREAD, &rtu)) {
					const auto ut = rtu.ru_utime.tv_sec + rtu.ru_utime.tv_usec * 1e-6;
					const auto st = rtu.ru_stime.tv_sec + rtu.ru_stime.tv_usec * 1e-6;
					if (ut >= 0 && st >= 0) {
						userTime = ut, systemTime = st, hasInfo = true;
					}
				}
#	ifdef CLOCK_THREAD_CPUTIME_ID
				struct timespec ts;
				if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) != -1) {
					cpuTime = ts.tv_sec + ts.tv_nsec * 1e-9;
					double t = userTime + systemTime;
					if (cpuTime > 0) {
						avCPUUsage += t * 100.0 / cpuTime;
					}
				}
#	endif
#endif
			}
		}
	}
	return DWORD(nProcessed);
}