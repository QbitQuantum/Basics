bool Win32AudioCDManager::tryAddDrive(char drive, DriveList &drives) {
	Common::String drivePath = Common::String::format("%c:\\", drive);

	// Ensure it's an actual CD drive
	if (GetDriveTypeA(drivePath.c_str()) != DRIVE_CDROM)
		return false;

	debug(2, "Detected drive %c:\\ as a CD drive", drive);
	drives.push_back(drive);
	return true;
}