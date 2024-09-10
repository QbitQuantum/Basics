    void LinkPlugin::InitializeLinkedMem()
    {
#ifdef WIN32
		HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
		if (hMapObject == NULL)
        {
            reason_ = "Shared memory is not available, please ensure that mumble client is running.";
			return;
        }

		linked_mem_ = (LinkedMem *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
		if (linked_mem_ == NULL) {
			CloseHandle(hMapObject);
			hMapObject = NULL;
            reason_ = "Shared memory is not available, cannot open the file.";
			return;
		}
#else
		char memname[256];
		snprintf(memname, 256, "/MumbleLink.%d", getuid());

		int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

		if (shmfd < 0)
        {
            reason_ = "Shared memory is not available, please ensure that mumble client is running.";
			return;
		}

		linked_mem_ = (LinkedMem *)(mmap(NULL, sizeof(struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0));

		if (linked_mem_ == (void *)(-1))
        {
            reason_ = "Shared memory is not available, cannot open the file.";
			linked_mem_ = NULL;
			return;
		}
#endif
    }