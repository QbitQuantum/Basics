int DeviceDir::RemoveDir(const char name[], size_t length)
{
	DeviceEntry *entry = FindEntry(name, length);
	if (entry == 0)
		return E_NO_SUCH_FILE;

	if (entry->Lookup(".", 1, (VNode**) &entry) < 0)	// note: acquires reference if successful
		return E_NOT_DIR;

	if (((DeviceDir*) entry)->GetEntryList()->CountItems() != 2) {
		entry->ReleaseRef();
		return E_ENTRY_EXISTS;
	}
		
	fEntryList.Remove(entry);
	entry->MakeDead();
	entry->ReleaseRef();
	return E_NO_ERROR;
}