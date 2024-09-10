int DeviceServiceEntry(PDEVICE_SERVICE_ENTRY_POINTS pEntryPoints)
{
	RDPDR_DRIVE* drive;
#ifdef WIN32
	char* dev;
	int len;
	char devlist[512], buf[512];
#endif

	drive = (RDPDR_DRIVE*) pEntryPoints->device;

#ifndef WIN32

	if (strcmp(drive->Path, "*") == 0)
	{
		/* all drives */

		free(drive->Path);
		drive->Path = _strdup("/");
	}
	else if (strcmp(drive->Path, "%") == 0)
	{
		char* home_env = NULL;

		/* home directory */

		home_env = getenv("HOME");
		free(drive->Path);

		if (home_env)
			drive->Path = _strdup(home_env);
		else
			drive->Path = _strdup("/");
	}

        drive_register_drive_path(pEntryPoints, drive->Name, drive->Path);

#else
        /* Special case: path[0] == '*' -> export all drives */
	/* Special case: path[0] == '%' -> user home dir */
        if (strcmp(drive->Path, "%") == 0)
	{
		_snprintf(buf, sizeof(buf), "%s\\", getenv("USERPROFILE"));
		drive_register_drive_path(pEntryPoints, drive->Name, _strdup(buf));
	}
	else if (strcmp(drive->Path, "*") == 0)
	{
		int i;

		/* Enumerate all devices: */
		GetLogicalDriveStringsA(sizeof(devlist) - 1, devlist);

		for (dev = devlist, i = 0; *dev; dev += 4, i++)
		{
			if (*dev > 'B')
                        {
				/* Suppress disk drives A and B to avoid pesty messages */
				_snprintf(buf, sizeof(buf) - 4, "%s", drive->Name);
				len = strlen(buf);
				buf[len] = '_';
				buf[len + 1] = dev[0];
				buf[len + 2] = 0;
				buf[len + 3] = 0;
				drive_register_drive_path(pEntryPoints, _strdup(buf), _strdup(dev));
			}
		}
	}
        else
        {
		drive_register_drive_path(pEntryPoints, drive->Name, drive->Path);
	}
#endif
	
        return 0;
 }