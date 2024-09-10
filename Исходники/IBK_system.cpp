unsigned int getFreeDiskSpace(const IBK::Path& dir) {

#if defined(_WIN32)
	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD freeClusters;
	DWORD totalClusters;

	std::string drive = dir.drive();
	drive += "\\";

	//get disk space for current drive
	bool success = (GetDiskFreeSpaceA(
		drive.c_str(), //current drive
		&sectorsPerCluster, //sectors per cluster
		&bytesPerSector, //bytes per sector
		&freeClusters, //free clusters
		&totalClusters //total clusters
	) == 1);

	if(!success) {
		return 0;
	}

	unsigned int kBPerCluster = bytesPerSector * sectorsPerCluster / 1024;

	return kBPerCluster * freeClusters / 1024;

#else


	struct statvfs	fs;
	int				returnCode = 0;

	returnCode = statvfs( dir.absolutePath().c_str(), &fs );

	if (returnCode == 0)
		return fs.f_bsize * fs.f_bfree / 1024;

	/// \todo error code handling
	return 0;

#endif
}