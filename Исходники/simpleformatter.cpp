std::string SimpleFormatter::format(const LogEvent& logEvent) const
{
	std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());

	struct tm* timeinfo = localtime(&logEvent.getTime());
	char timeString[80];
	strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

	std::stringstream ss;
	ss
		<< "[" << timeString << "]"
		<< "[" << logLevelString << "]"
		<< "[pid=" << logEvent.getPid() << "]"
		<< "[tid=" << logEvent.getTid() << "]"
		<< "[file=" << logEvent.getFile() << "]"
		<< "[line=" << logEvent.getLine() << "]"
#ifdef HUMBLE_INCLUDE_PRETTY_FUNCTION
		<< "[func=" << logEvent.getFunction() << "]"
#endif
		<< " "
		<< logEvent.getMessage()
		<< "\n";
	return ss.str(); // optional: std::move(ss.str())
}