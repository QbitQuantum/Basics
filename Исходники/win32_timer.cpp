		explicit impl(int64_t ms)
			: m_sink(nullptr)
		{
			m_h = CreateWaitableTimerW(nullptr, TRUE, nullptr);
			if (m_h == 0)
				throw detail::win32_error(::GetLastError());

			LARGE_INTEGER li;
			li.QuadPart = -(ms * 10000);
			if (!SetWaitableTimer(m_h, &li, 0, 0, 0, FALSE))
			{
				DWORD ec = ::GetLastError();
				CloseHandle(m_h);
				throw detail::win32_error(ec);
			}
		}