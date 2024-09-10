// Scan directory for CD-ROM drives, add them to prefs
static void scan_for_cdrom_drives(const char *directory)
{
	// Set directory
	BDirectory dir;
	dir.SetTo(directory);
	if (dir.InitCheck() != B_NO_ERROR)
		return;
	dir.Rewind();

	// Scan each entry
	BEntry entry;
	while (dir.GetNextEntry(&entry) >= 0) {

		// Get path and ref for entry
		BPath path;
		if (entry.GetPath(&path) != B_NO_ERROR)
			continue;
		const char *name = path.Path();
		entry_ref e;
		if (entry.GetRef(&e) != B_NO_ERROR)
			continue;

		// Recursively enter subdirectories (except for floppy)
		if (entry.IsDirectory()) {
			if (!strcmp(e.name, "floppy"))
				continue;
			scan_for_cdrom_drives(name);
		} else {

			D(bug(" checking '%s'\n", name));

			// Ignore partitions
			if (strcmp(e.name, "raw"))
				continue;

			// Open device
			int fd = open(name, O_RDONLY);
			if (fd < 0)
				continue;

			// Get geometry and device type
			device_geometry g;
			if (ioctl(fd, B_GET_GEOMETRY, &g, sizeof(g)) < 0) {
				close(fd);
				continue;
			}

			// Insert to list if it is a CD drive
			if (g.device_type == B_CD)
				PrefsAddString("cdrom", name);
			close(fd);
		}
	}
}