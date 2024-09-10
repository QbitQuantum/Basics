status_t
ACPIDriverInterface::_FindDrivers(const char* path)
{
	BDirectory dir(path);
	BEntry entry;

	status_t status = B_ERROR;

	while (dir.GetNextEntry(&entry) == B_OK) {
		BPath path;
		entry.GetPath(&path);

		if (entry.IsDirectory()) {
			if (_FindDrivers(path.Path()) == B_OK)
				return B_OK;
		}
		else {
			int32 handler = open(path.Path(), O_RDWR);
			if (handler >= 0) {
				printf("try %s\n", path.Path());
				Battery* battery = new Battery(handler);
				if (battery->InitCheck() == B_OK) {
					fDriverList.AddItem(battery);
					status = B_OK;
				}
				else
					delete battery;
			}
		}

	}
	return status;
}