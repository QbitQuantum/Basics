GetCpuUseage::GetCpuUseage()
{	
	GetSystemTimes(&m_preidleTime, &m_prekernelTime, &m_preuserTime);
	Sleep(100);
}