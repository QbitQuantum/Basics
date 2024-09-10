time_t SaveManager::getLastBackupTime()
{
	if (lastBackupTime == 0)
	{
		std::vector<std::wstring> backupFiles = getBackupFiles();
		if (!backupFiles.empty())
		{
			std::wstring fileName = getFileNameFromPath(backupFiles.front());
			swscanf_s(fileName.c_str(), L"%llu", &lastBackupTime);
		}
	}
	SDLOG(3, "SaveManager: last backup time %llu", lastBackupTime);
	return lastBackupTime;
}