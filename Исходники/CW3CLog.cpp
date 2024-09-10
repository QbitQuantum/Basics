void W3CLog::traceOn(std::auto_ptr<ILog> log, const std::string& appInfo, const std::string& format)
{
	m_format = ((sstring)format).split(" ");

	m_log = log;
	
	m_log->trace("");
	char date[100],time[100];
	_strtime(time);
	_strdate(date);

	std::string buffer;
	buffer = "#Software: " + appInfo;  //TRACER_FORMAT("%s %s\r\n","#Software:",id_cliente);
	m_log->trace(buffer);
	
	buffer = "#Version: 1.0";
	m_log->trace(buffer);
	
	buffer = "#Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	buffer = "#Fields: " + format;
	m_log->trace(buffer);

	buffer = "#Start-Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	



}