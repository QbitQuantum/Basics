bool ATVersion::GetAppVersion(const char *appName, std::string &version)
{
	std::list<unsigned long> pids;

	version = "";
	if (IsAppRunning(appName, pids)) {
		for (std::list<unsigned long>::iterator iter = pids.begin(); iter != pids.end(); iter++) {
			std::string path = GetAppPathByPid(*iter);
			if (!path.empty()) {
				version = GetProcessVersion(path);
				return true;
			}
		}
	}
	version = GetProcessVersion(ATVersion::appSearchPath + appName);
	if (version.empty()) {
		version = GetProcessVersion(appName);
	}
	return false;
}