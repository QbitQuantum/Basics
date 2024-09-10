void NetworkPacketDumper::deleteAdapterFiles() {
	std::list<NetworkAdapter*>::iterator it;
	for(it = adapterList.begin(); it != adapterList.end(); it++)
	{
		string adapterName = (*it)->getAdapterName();
		char* szLogFileName = new char[1024];
		string logName = "logs\\";
		logName += adapterName;
		logName += ".pcap";
		GetFullPathNameA(logName.c_str(), 1024, szLogFileName, NULL);
		LOG(INFO, "NetworkdPacketDumper: deleting log files %s",logName.c_str());
		DeleteFileA(szLogFileName);
		delete [] szLogFileName;
	}
	
}