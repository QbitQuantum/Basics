void TextClass::Render()
{
	INT64 currentTime;
	float timeDifference;

	PDH_FMT_COUNTERVALUE value;

	// Set timer


	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;


	// Set fps
	m_count++;

	// If one second has passed then update the frame per second speed.
	if (timeGetTime() >= (m_startTimeFps + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_startTimeFps = timeGetTime();
	}

	// Set cpu


	if (m_canReadCpu)
	{
		// If it has been 1 second then update the current cpu usage and reset the 1 second timer again.
		if ((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount();

			PdhCollectQueryData(m_queryHandle);

			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);

			m_cpuUsage = value.longValue;
		}
	}

	
	return;
}