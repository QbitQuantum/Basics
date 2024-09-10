uint64_t CFileSystemObject::rootFileSystemId() const
{
	if (_rootFileSystemId == std::numeric_limits<uint64_t>::max())
	{
#ifdef _WIN32
		const auto driveNumber = PathGetDriveNumberW((WCHAR*) _properties.fullPath.utf16());
		if (driveNumber != -1)
			_rootFileSystemId = (uint64_t) driveNumber;
#else
		struct stat info;
		const int ret = stat(_properties.fullPath.toUtf8().constData(), &info);
		if (ret == 0 || errno == ENOENT)
			_rootFileSystemId = (uint64_t) info.st_dev;
		else
		{
			qInfo() << __FUNCTION__ << "Failed to query device ID for" << _properties.fullPath;
			qInfo() << strerror(errno);
		}
#endif
	}

	return _rootFileSystemId;
}