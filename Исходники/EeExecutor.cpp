void CEeExecutor::RemoveExceptionHandler()
{
#if defined(_WIN32)
	RemoveVectoredExceptionHandler(m_handler);
#endif
	g_eeExecutor = nullptr;
}