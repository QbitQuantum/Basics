void CLogger::SetLogPath(const QString& LogPath)
{
	m_LogPath = LogPath;
	CreateDir(m_LogPath);
	CreateLogFile();
}