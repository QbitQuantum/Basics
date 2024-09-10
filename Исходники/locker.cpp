	status_t lock_with_timeout(bigtime_t time)// だめだめ
	{
		#ifdef NTK_WINNT
			bigtime_t start_time = GetTickCount();//timeGetTime();

			while(TryEnterCriticalSection(&m_critical_section))
			{
				if(GetTickCount() - start_time > time)//timeGetTime()
					return Locker::status::TIME_OUT_ERROR;

				snooze(1);// 数値は適当
			}

			++m_lock_count;
			return st::OK;
		#else
			time = time;
			return status_t(st::ERR,
				"TryEnterCriticalSection: Windows9x ではサポートされてないようです。");
		#endif
	}