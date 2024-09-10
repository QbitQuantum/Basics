//------------------------------------------------------------------
//
//	EndLog(..)
//
//	Writes foot entry
//
//------------------------------------------------------------------
void CDebugLog::EndLog()
{
	if (m_bInit) {
		time_t rawTime;
		struct tm timeinfo;
		char buffer[32];

		time(&rawTime);
		localtime_s(&timeinfo, &rawTime);
		asctime_s(buffer, &timeinfo);
		m_fileStream << "\nDebug Log Ended: " << buffer;
	}
}