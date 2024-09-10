void Mumble_CreateLink()
{
#ifdef _WIN32
	if (hMapObject != NULL)
	{
		ST_Printf(PRINT_FAIL,"Mumble link already initialized.\n");
		return;
	}
	hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL)
	{
		//Com_Printf("Mumble is not running\n");
		return;
	}

	lm = (struct LinkedMem *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(struct LinkedMem));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		ST_Printf(PRINT_FAIL,"Mumble link initialization failed.\n");
		return;
	}
#else // Linux && Mac
	char memname[256];
	
	if (lm != NULL)
	{
		ST_Printf(PRINT_FAIL,"Mumble link already initialized.\n");
		return;
	}
	
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if(shmfd < 0)
	{
		ST_Printf(PRINT_INFO,"Mumble initialization skipped. Mumble not running.\n");
		return;
	}

	lm = (struct LinkedMem *) (mmap(NULL, sizeof(struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0));

	if (lm == (void *) (-1))
	{
		lm = NULL;
		
		close(shmfd);
		shmfd = -1;
		
		ST_Printf(PRINT_FAIL,"Mumble link initialization failed.\n");
		return;
	}
#endif

	mbstowcs(lm->name, "jQuake", sizeof(lm->name));
	Com_Printf(CharsToBrownStatic("Mumble link initialized."));
	Com_Printf("\n");
}