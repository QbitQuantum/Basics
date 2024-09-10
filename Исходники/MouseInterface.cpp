CMouseInterface::CMouseInterface() :
	m_pSlotRom(NULL)
{
	m_6821.SetListenerB( this, M6821_Listener_B );
	m_6821.SetListenerA( this, M6821_Listener_A );
//	g_cDIMouse.SetMouseListener( this, MouseHandler );

	Uninitialize();
	Reset();
}