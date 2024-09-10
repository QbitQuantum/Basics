WinCPUUsage::WinCPUUsage()
	: CPUUsage()
	, m_startSysIdle()
	, m_startSysKernel()
	, m_startSysUser()
	, m_startProcKernel()
	, m_startProcUser()
{
	// Remember current CPU statistics
	FILETIME createTime, exitTime;
	GetSystemTimes(&m_startSysIdle, &m_startSysKernel, &m_startSysUser);
	GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime,
		&m_startProcKernel, &m_startProcUser);
}