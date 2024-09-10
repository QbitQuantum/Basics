int _tmain(int argc, _TCHAR* argv[])
{
	std::wstring symlink;
	std::wstring target;

	if (argc < 3)
	{
		printf("Usage: CreateDosDeviceSymlink [-d] symlink [target]\n");
		printf("Options:\n");
		printf("-d   : Delete the symlink\n");
		return 1;
	}	

	if (wcscmp(argv[1], L"-d") == 0)
	{	
		symlink = MakeSymlink(argv[2]);
		if (argc > 3)
		{
			target = argv[3];
		}

		if (DefineDosDeviceW(DDD_NO_BROADCAST_SYSTEM | DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION |
			DDD_EXACT_MATCH_ON_REMOVE, symlink.c_str(), target.size() > 0 ? target.c_str() : nullptr))
		{
			printf("Removed symlink\n");
		}
		else
		{
			printf("Error removing symlink: %ls\n", GetErrorMessage().c_str());
		}		
	}
	else
	{
		symlink = MakeSymlink(argv[1]);		
		target = argv[2];	

		if (DefineDosDevice(DDD_NO_BROADCAST_SYSTEM | DDD_RAW_TARGET_PATH, symlink.c_str(), target.c_str()))
		{
			printf("Created symlink\n");
		}
		else
		{
			printf("Error creating symlink: %ls\n", GetErrorMessage().c_str());
		}
	}

	return 0;
}