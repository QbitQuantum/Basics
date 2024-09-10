void
OpenWindow::CollectDevices(BMenu *menu, BEntry *startEntry)
{
	BDirectory directory;
	if (startEntry != NULL)
		directory.SetTo(startEntry);
	else
		directory.SetTo("/dev/disk");

	BEntry entry;
	while (directory.GetNextEntry(&entry) == B_OK) {
		if (entry.IsDirectory()) {
			CollectDevices(menu, &entry);
			continue;
		}

		entry_ref ref;
		if (entry.GetRef(&ref) != B_OK)
			continue;

		BPath path;
		if (entry.GetPath(&path) != B_OK)
			continue;

		BMessage *message = new BMessage(B_REFS_RECEIVED);
		message->AddRef("refs", &ref);

		menu->AddItem(new BMenuItem(path.Path(), message));
	}
}