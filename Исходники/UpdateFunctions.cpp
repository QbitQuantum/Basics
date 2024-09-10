bool ServiceUpdate(bool validService)
{
	if (validService)
	{
		ServiceInstaller si;

		if (si.run() != 0)
			return false;
	}
	else
	{
		std::wstring appPath = UTIL::OS::getCommonProgramFilesPath();

		if (!FolderExists(appPath.c_str()))
			CreateDirectoryW(appPath.c_str(), NULL);

		std::wstring newService = UTIL::OS::getCommonProgramFilesPath(L"desura_service.exe");
		std::wstring curService = UTIL::OS::getCurrentDir(L"desura_service.exe");

		char regname[255];
		Safe::snprintf(regname, 255, "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\%s\\ImagePath", SERVICE_NAME);

		CopyFileW(curService.c_str(), newService.c_str(), FALSE);
		UTIL::WIN::setRegValue(regname, gcString(newService).c_str());
	}

	return true;
}