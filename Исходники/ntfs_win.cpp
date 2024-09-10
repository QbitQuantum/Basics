FSNTFSWIN::FSNTFSWIN(const std::string &pDev, IFSImageFactory::EReadaheadMode read_ahead, bool background_priority, IFsNextBlockCallback* next_block_callback)
	: Filesystem(pDev, read_ahead, next_block_callback), bitmap(NULL)
{
	HANDLE hDev=CreateFileW( Server->ConvertToWchar(pDev).c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_NO_BUFFERING, NULL );
	if(hDev==INVALID_HANDLE_VALUE)
	{
		Server->Log("Error opening device -2", LL_ERROR);
		has_error=true;
		return;
	}

	DWORD sectors_per_cluster;
	DWORD bytes_per_sector;
	DWORD NumberOfFreeClusters;
	DWORD TotalNumberOfClusters;
	BOOL b=GetDiskFreeSpaceW((Server->ConvertToWchar(pDev)+L"\\").c_str(), &sectors_per_cluster, &bytes_per_sector, &NumberOfFreeClusters, &TotalNumberOfClusters);
	if(!b)
	{
		Server->Log("Error in GetDiskFreeSpaceW", LL_ERROR);
		has_error=true;
		CloseHandle(hDev);
		return;
	}

	DWORD r_bytes;
	NTFS_VOLUME_DATA_BUFFER vdb;
	b=DeviceIoControl(hDev, FSCTL_GET_NTFS_VOLUME_DATA,  NULL,  0, &vdb,  sizeof(NTFS_VOLUME_DATA_BUFFER), &r_bytes, NULL);
	if(!b)
	{
		Server->Log("Error in DeviceIoControl(FSCTL_GET_NTFS_VOLUME_DATA)", LL_ERROR);
		has_error=true;
		CloseHandle(hDev);
		return;
	}

	sectorsize=bytes_per_sector;
	clustersize=sectorsize*sectors_per_cluster;
	drivesize=vdb.NumberSectors.QuadPart*sectorsize;

	uint64 numberOfClusters=drivesize/clustersize;

	STARTING_LCN_INPUT_BUFFER start;
	LARGE_INTEGER li;
	li.QuadPart=0;
	start.StartingLcn=li;

	size_t new_size=(size_t)(numberOfClusters/8);
	if(numberOfClusters%8!=0)
		++new_size;
			
	size_t n_clusters=new_size;

	new_size+=sizeof(VOLUME_BITMAP_BUFFER);

	VOLUME_BITMAP_BUFFER *vbb=(VOLUME_BITMAP_BUFFER*)(new char[new_size]);

	
	b=DeviceIoControl(hDev, FSCTL_GET_VOLUME_BITMAP, &start, sizeof(STARTING_LCN_INPUT_BUFFER), vbb, (DWORD)new_size, &r_bytes, NULL);
	if(!b)
	{
		Server->Log("DeviceIoControl(FSCTL_GET_VOLUME_BITMAP) failed", LL_ERROR);
		has_error=true;
		CloseHandle(hDev);
		return;
	}

	Server->Log("TotalNumberOfClusters="+convert((size_t)TotalNumberOfClusters)+" numberOfClusters="+convert(numberOfClusters)+" n_clusters="+convert(n_clusters)+" StartingLcn="+convert(vbb->StartingLcn.QuadPart)+" BitmapSize="+convert(vbb->BitmapSize.QuadPart)+" r_bytes="+convert((size_t)r_bytes), LL_DEBUG);

	bitmap=new unsigned char[(unsigned int)(n_clusters)];
	memset(bitmap, 0xFF, n_clusters);
	memcpy(bitmap+(unsigned int)(vbb->StartingLcn.QuadPart/8), vbb->Buffer, (size_t)(vbb->BitmapSize.QuadPart/8));

	delete []vbb;

	CloseHandle(hDev);

	initReadahead(read_ahead, background_priority);
}