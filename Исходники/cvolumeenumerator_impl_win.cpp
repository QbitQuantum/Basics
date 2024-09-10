const std::deque<VolumeInfo> CVolumeEnumerator::enumerateVolumesImpl()
{
	std::deque<VolumeInfo> volumes;

	const auto oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
	EXEC_ON_SCOPE_EXIT([oldErrorMode]() {SetErrorMode(oldErrorMode);});

	DWORD drives = GetLogicalDrives();
	if (drives == 0)
	{
		qInfo() << "GetLogicalDrives() returned an error:" << ErrorStringFromLastError();
		return volumes;
	}

	for (char driveLetter = 'A'; drives != 0 && driveLetter <= 'Z'; ++driveLetter, drives >>= 1)
	{
		if ((drives & 0x1) == 0)
			continue;

		const auto volumeInfo = volumeInfoForDriveLetter(QString(driveLetter) + QStringLiteral(":\\"));
		if (!volumeInfo.isEmpty())
			volumes.push_back(volumeInfo);
	}

	return volumes;
}