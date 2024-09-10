FTConnectionModule::~FTConnectionModule()
{
	// Kill the thread
	if(p_critical_section!=NULL)
	{
		WSASetEvent(p_thread_data->m_reserved_events[0]);
	}

	// Destroy message window
	m_wnd.DestroyWindow();
}