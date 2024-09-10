/**
* CLoggingSystem::CLoggingSystem
* @date Modified Mar 27, 2006
*/
CLoggingSystem::CLoggingSystem(void)
{
	m_ofLogFile.exceptions(std::ios::badbit | std::ios::failbit);
	try
	{
		m_ofLogFile.open("AckZombies.log");

		// Get Date
		char dbuffer[9];
		_strdate(dbuffer);

		CString sFmt = "-",
				sTitle;
		sFmt *= 80;
		sTitle.Format("%-69s %8s ", "Ack! Zombies - Cypher Edge Interactive",  dbuffer);
		m_ofLogFile << sFmt << "\n ";
		m_ofLogFile << sTitle << '\n';
		m_ofLogFile << sFmt << '\n';

	}
	catch(...)
	{
		if(m_ofLogFile.is_open())
			m_ofLogFile.close();
	}
}