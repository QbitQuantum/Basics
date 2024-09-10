void 
Foobar::COM_ReleaseServer()
{
	BOOL test = m_comApp ? OleIsRunning((LPOLEOBJECT)m_comApp) : FALSE;

	// Stop listening to events
	/* When the program is terminating, make sure that we instruct our */
	/* Event Handler to disconnect from the connection point of the */
	/* object which implemented the IEventFiringObject interface. */
	/* We also needs to Release() it (instead of deleting it). */
	if (m_comPlaybackEventSink) {
		m_comPlaybackEventSink -> ShutdownConnectionPoint();
		m_comPlaybackEventSink -> Release();
		m_comPlaybackEventSink = NULL;
	}
	RELEASE(m_comPlayback, m_vbServerState);
	RELEASE(m_comApp, m_vbServerState);
	BSTRFREE(m_comRet);

	m_state = PL_OFFLINE;
	if(loaded)
		NotifyInfoChanged();
}