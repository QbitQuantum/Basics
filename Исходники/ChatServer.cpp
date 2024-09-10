int main(int argc, char* argv[])
{
	// Load configuration
	std::string path(argv[0]);
	unsigned found = path.find_last_of("/\\");
	path = path.substr(0, found + 1);
	Configuration *configuration = Configuration::getInstance(path);
	Log *loggr = Log::getInstance();

	serviceName = L"ChatServer";
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
	ServiceTable[0].lpServiceName = serviceName;
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTIONW)ServiceMain;
	StartServiceCtrlDispatcherW(&ServiceTable[0]);

	return 0;
}