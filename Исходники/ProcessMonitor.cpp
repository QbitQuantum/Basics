void ProcessMonitor::logMessage(const wchar_t* message, bool showPID){
	//method sends message to the logger
	if (logger){
		std::wstringstream messageStream;
		messageStream << L"ProcessMonitor: ";
		if(showPID)messageStream << "[" << getPID() << "] ";
		messageStream << message;
		logger->log(messageStream.str());
	}
}