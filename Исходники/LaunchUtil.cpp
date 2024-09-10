bool
isConfigNewer(time_t& oldTime, bool userConfig)
{
	time_t newTime = oldTime;
	if (userConfig) {
		CString path = ARCH->getUserDirectory();
		if (!path.empty()) {
			path = ARCH->concatPath(path, CONFIG_NAME);
			getFileTime(path, newTime);
		}
	}
	else {
		CString path = ARCH->getSystemDirectory();
		if (!path.empty()) {
			path = ARCH->concatPath(path, CONFIG_NAME);
			getFileTime(path, newTime);
		}
	}
	bool result = (newTime > oldTime);
	oldTime = newTime;
	return result;
}