bool
BTrashWatcher::CheckTrashDirs()
{
	BVolumeRoster volRoster;
	volRoster.Rewind();
	BVolume	volume;
	while (volRoster.GetNextVolume(&volume) == B_OK) {
		if (volume.IsReadOnly() || !volume.IsPersistent())
			continue;

		BDirectory trashDir;
		FSGetTrashDir(&trashDir, volume.Device());
		trashDir.Rewind();
		BEntry entry;
		if (trashDir.GetNextEntry(&entry) == B_OK)
			return true;
	}

	return false;
}