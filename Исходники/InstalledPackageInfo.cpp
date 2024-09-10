status_t
InstalledPackageInfo::Uninstall()
{
	if (fStatus != B_OK)
		return fStatus;

	BString *iter;
	uint32 i, count = fInstalledItems.CountItems();
	BEntry entry;
	status_t ret;

	// Try to remove all entries that are present in the list
	for (i = 0; i < count; i++) {
		iter = static_cast<BString *>(fInstalledItems.ItemAt(count - i - 1));
		fprintf(stderr, "Removing: %s (%ld/%ld)\n", iter->String(), i, count);
		ret = entry.SetTo(iter->String());
		if (ret == B_BUSY) {
			// The entry's directory is locked - wait a few cycles for it to
			// unlock itself
			int32 tries = 0;
			for (tries = 0; tries < P_BUSY_TRIES; tries++) {
				ret = entry.SetTo(iter->String());
				if (ret != B_BUSY)
					break;
				// Wait a moment
				usleep(1000);
			}
		}

		if (ret == B_ENTRY_NOT_FOUND)
			continue;
		else if (ret != B_OK) {
			fStatus = B_ERROR;
			return fStatus;
		}

		fprintf(stderr, "...we continue\n");

		if (entry.Exists() && entry.Remove() != B_OK) {
			fprintf(stderr, "\n%s\n", strerror(ret));
			fStatus = B_ERROR;
			return fStatus;
		}
		fInstalledItems.RemoveItem(count - i - 1);
	}

	if (entry.SetTo(fPathToInfo.Path()) != B_OK) {
		fStatus = B_ERROR;
		return fStatus;
	}
	if (entry.Exists() && entry.Remove() != B_OK) {
		fStatus = B_ERROR;
		return fStatus;
	}

	return fStatus;
}