void SessionServer::TeardownFileLogger()
{
    time_t curTime = time(NULL);
    tm curTM;
    localtime_s(&curTM, &curTime);
    
	m_logger->ClearWriter();

    std::string curTimeString = GetCurrentDateTimeString(curTM);

    LogInfo(" ** Logging Session Ended at %s", curTimeString.c_str());
    if (m_logWriter)
    {
        delete m_logWriter;
        m_logWriter = NULL;
    }
}