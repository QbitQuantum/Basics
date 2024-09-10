bool CGPUUsage::EnoughTimePassed()
{
	const int minElapsedMS = 1000;
	return (GetTickCount() - m_dwLastRun) >= minElapsedMS; 
}