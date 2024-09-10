		Chrono::Chrono(Type type)
		{
#ifdef __linux__
			switch (type)
			{
			case Type::REAL_TIME:
				m_clockId = CLOCK_MONOTONIC_RAW;
				break;

			case Type::PROCESS_TIME:
				m_clockId = CLOCK_PROCESS_CPUTIME_ID;
				break;

			case Type::THREAD_TIME:
				m_clockId = CLOCK_THREAD_CPUTIME_ID;
				break;
			}

			timespec now = {};
			if (clock_gettime(m_clockId, &now))
			{
				m_clockId = CLOCK_MONOTONIC;
				if (clock_gettime(m_clockId, &now))
				{
					m_clockId = CLOCK_REALTIME;
					if (clock_gettime(m_clockId, &now))
					{
						m_clockId = -1;
						m_timestamp = 0;
						return;
					}
				}
			}

			m_timestamp = now.tv_sec * 1000000000 + now.tv_nsec;

#elif defined(_WIN32)
			m_type = type;

			switch (m_type)
			{
			case Type::REAL_TIME:
				if (QueryPerformanceFrequency(&m_counterFreq))
				{
					LARGE_INTEGER counter;
					if (QueryPerformanceCounter(&counter))
					{
						m_timestamp = counter.QuadPart;
						return;
					}
				}
				break;

			case Type::PROCESS_TIME:
				{
					FILETIME time[4];
					if (GetProcessTimes(GetCurrentProcess(), time, time + 1, time + 2, time + 3))
					{
						m_timestamp = static_cast<long long>(time[2].dwHighDateTime) << 32 | time[2].dwLowDateTime;
						m_timestamp += static_cast<long long>(time[3].dwHighDateTime) << 32 | time[3].dwLowDateTime;
						return;
					}
				}
				break;

			case Type::THREAD_TIME:
				{
					FILETIME time[4];
					if (GetThreadTimes(GetCurrentThread(), time, time + 1, time + 2, time + 3))
					{
						m_timestamp = static_cast<long long>(time[2].dwHighDateTime) << 32 | time[2].dwLowDateTime;
						m_timestamp += static_cast<long long>(time[3].dwHighDateTime) << 32 | time[3].dwLowDateTime;
						return;
					}
				}
				break;
			}

			m_counterFreq.QuadPart = 0;
			m_timestamp = 0;
#endif //__linux__
		}