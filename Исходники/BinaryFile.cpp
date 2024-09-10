	void	cBinaryFile::CreateTimestamp()
	{
	#ifdef WIN32
			char buffer[32];
			time_t ltime; time(&ltime);
			struct tm now; _localtime64_s(&now, &ltime);
			strftime(buffer, 32, "[%H:%M:%S] ", &now);
			int	l_iLength = (int)strlen(buffer);
			NvFWrite( buffer, sizeof(char),l_iLength, m_pFile );
	#endif //WIN32
	}