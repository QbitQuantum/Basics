BootManagerController::BootManagerController()
	:
	fBootDrive(NULL),
	fBootMenu(NULL)
{
	// set defaults
	fSettings.AddBool("install", true);
	fSettings.AddInt32("defaultPartition", 0);
	fSettings.AddInt32("timeout", -1);

	BPath path;
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &path, true) == B_OK) {
		path.Append("bootman/MBR");
		fSettings.AddString("file", path.Path());
		// create directory
		BPath parent;
		if (path.GetParent(&parent) == B_OK) {
			BDirectory directory;
			directory.CreateDirectory(parent.Path(), NULL);
		}
	} else {
		fSettings.AddString("file", "");
	}

	// That's the only boot menu we support at the moment.
	fBootMenus.AddItem(new LegacyBootMenu());
}