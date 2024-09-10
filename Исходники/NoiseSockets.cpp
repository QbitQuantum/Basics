NoiseSockets::NoiseSockets(HWND hwnd,CCriticalSection *connection_data_critical_section,vector<ConnectionData> *connection_data,FileSharingManager* fsm)
{
	p_fs_manager = fsm;
	m_hwnd=hwnd;
	p_connection_data_critical_section=connection_data_critical_section;
	p_connection_data=connection_data;

	m_num_bogus_connections=0;
	m_num_good_connections=0;

	int num_reserved_events=ReturnNumberOfReservedEvents();
	int num_socket_events=ReturnNumberOfSocketEvents();

	// Init the parent pointers and message window handles
	for(int i=0;i<num_socket_events;i++)
	{
		m_sockets[i].InitParent(this);
	}
	
	// Create the reserved events
	for(i=0;i<num_reserved_events;i++)
	{
		m_events[i]=WSACreateEvent();
		if(m_events[i]==WSA_INVALID_EVENT)
		{
			char msg[1024];
			strcpy(msg,"Could not create a valid reserved event ");
			_itoa(i,&msg[strlen(msg)],10);
			::MessageBox(NULL,msg,"Error",MB_OK);
		}
	}

	// Fully initialize events array
	for(i=0;i<num_socket_events;i++)
	{
		m_events[num_reserved_events+i]=m_sockets[i].ReturnEventHandle();
	}

	p_noise_data_buf=NULL;
	
	InitNoiseData();
}