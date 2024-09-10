void LiteLog::traceOff()
{
	char date[100],time[100];
	_strtime(time);
	_strdate(date);
	std::string buffer;
	buffer = "#End-Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);
	m_log->traceOff();
}