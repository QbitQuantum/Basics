// Read the configuration from the folder
void ElLoadConfigFromFolder(EL *e, FOLDER *root)
{
	UINT i;
	TOKEN_LIST *t;
	FOLDER *devices;

	// Validate arguments
	if (e == NULL || root == NULL)
	{
		return;
	}

	i = CfgGetInt(root, "AdminPort");
	if (i >= 1 && i <= 65535)
	{
		e->Port = i;
	}

	e->AutoDeleteCheckDiskFreeSpaceMin = CfgGetInt64(root, "AutoDeleteCheckDiskFreeSpaceMin");
	if (CfgIsItem(root, "AutoDeleteCheckDiskFreeSpaceMin") == false && e->AutoDeleteCheckDiskFreeSpaceMin == 0)
	{
		e->AutoDeleteCheckDiskFreeSpaceMin = DISK_FREE_SPACE_DEFAULT;
	}

	if (e->AutoDeleteCheckDiskFreeSpaceMin != 0)
	{
		if (e->AutoDeleteCheckDiskFreeSpaceMin < DISK_FREE_SPACE_MIN)
		{
			e->AutoDeleteCheckDiskFreeSpaceMin = DISK_FREE_SPACE_MIN;
		}
	}

	if (CfgGetByte(root, "AdminPassword", e->HashedPassword, sizeof(e->HashedPassword)) != sizeof(e->HashedPassword))
	{
		Hash(e->HashedPassword, "", 0, true);
	}

	if (ELOG_IS_BETA == false)
	{
		EiLoadLicenseManager(e,	CfgGetFolder(root, "LicenseManager"));
	}

	devices = CfgGetFolder(root, "Devices");
	if(devices != NULL)
	{
		LockList(e->DeviceList);
		{
			t = CfgEnumFolderToTokenList(devices);
			for (i = 0;i < t->NumTokens;i++)
			{
				char *name = t->Token[i];
				FOLDER *f = CfgGetFolder(devices, name);

				if (f != NULL)
				{
					HUB_LOG g;

					Zero(&g, sizeof(g));
					SiLoadHubLogCfg(&g, f);
					ElAddCaptureDevice(e, name, &g, CfgGetBool(f, "NoPromiscusMode"));
				}
			}
			FreeToken(t);
		}
		UnlockList(e->DeviceList);
	}
}