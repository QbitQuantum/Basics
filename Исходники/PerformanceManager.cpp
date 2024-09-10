bool PerformanceManager::update()
{
	float timeDifference;
	INT64 currentTime;
	PDH_FMT_COUNTERVALUE value;

	//=====
	// FPS 
	//=====

	m_frameCount++;

	// If one second has passed then update the frame per second speed.
	if (timeGetTime() >= (m_fpsStart + 1000))
	{
		// Store FPS Count
		m_fps = m_frameCount;

		// Reset
		m_frameCount = 0;
		m_fpsStart = timeGetTime();
	}

	//=====
	// CPU
	//=====

	if (m_canAccessCPU)
	{
		// If it has been 1 second then update the current cpu usage and reset the 1 second timer again.
		if ((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount();

			PdhCollectQueryData(m_queryHandle);

			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);

			m_usage = value.longValue;
		}
	}

	//=======
	// Timer
	//=======

	// Query the current time
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate difference in time since last check
	timeDifference = (float)(currentTime - m_timerStart);

	// Calculate the frame time by the time difference over the timer speed resolution.
	m_frameTime = timeDifference / m_ticksPerMs;

	// Restart the timer.
	QueryPerformanceCounter((LARGE_INTEGER*)&m_timerStart);

	return true;
}