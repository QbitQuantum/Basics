int32
CDAudioDevice::_FindDrives(const char *path)
{
	BDirectory dir(path);

	if (dir.InitCheck() != B_OK)
		return B_ERROR; 

	dir.Rewind();

	BEntry entry; 
	while (dir.GetNextEntry(&entry) >= 0) {
		BPath path;
		const char *name;
		entry_ref e;

		if (entry.GetPath(&path) != B_OK)
			continue;

		name = path.Path();
		if (entry.GetRef(&e) != B_OK)
			continue;

		if (entry.IsDirectory()) {
			// ignore floppy -- it is not silent
			if (strcmp(e.name, "floppy") == 0)
				continue;
			else if (strcmp(e.name, "ata") == 0)
				continue;

			// Note that if we check for the count here, we could
			// just search for one drive. However, we want to find *all* drives
			// that are available, so we keep searching even if we've found one
			_FindDrives(name);

		} else {
			int devfd;
			device_geometry g;

			// ignore partitions
			if (strcmp(e.name, "raw") != 0)
				continue;

			devfd = open(name, O_RDONLY);
			if (devfd < 0)
				continue;

			if (ioctl(devfd, B_GET_GEOMETRY, &g, sizeof(g)) >= 0) {
				if (g.device_type == B_CD)
					fDriveList.AddItem(new BString(name));
			}
			close(devfd);
		}
	}
	return fDriveList.CountItems();
}