void		BBWinAgentManager::Rename(LPCTSTR newHostName) {
	bbdisplay_t::iterator			itr;
	BBWinNet						hobNet;
		
	assert(newHostName != NULL);
	PrepareBBWinNetObj(hobNet);
	for ( itr = m_bbdisplay.begin(); itr != m_bbdisplay.end(); ++itr) {
		hobNet.SetBBDisplay((*itr));
		try {
			hobNet.Rename(newHostName);
		} catch (BBWinNetException ex) {
			if (m_logReportFailure) {
				string mes;
			
				mes = "Sending report to " + (*itr) + " failed.";
				LPCTSTR		arg[] = {m_agentName.c_str(), mes.c_str(), NULL};
				m_log->reportWarnEvent(BBWIN_AGENT, EVENT_MESSAGE_AGENT, 2, arg);
			}
			continue ; 
		}
	}
}