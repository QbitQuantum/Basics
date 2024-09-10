bool Win32_ConditionVariable::Wait(Mutex* mutex, unsigned int timeout)
{
	Win32_Mutex* win32mutex = static_cast<Win32_Mutex*>(mutex);

	if (timeout == 0)
	{
		timeout = INFINITE;
	}

	return (SleepConditionVariableCS(&m_convar_handle, &win32mutex->m_critical_section, timeout) != 0);
}