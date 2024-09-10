void BeCheckersWindow::SavedGames(BListView *list) {
	char name[B_FILE_NAME_LENGTH];

	BEntry entry;
	BDirectory dir;
	BPath p;
	find_directory(B_USER_DIRECTORY, &p);
	p.Append(APP_SGP);

	dir.SetTo(p.Path());
	dir.Rewind();

	while (dir.GetNextEntry(&entry) == B_OK) {
		entry.GetName(name);
		strtok(name, ".");	// Strip the filename extension
		list->AddItem(new BStringItem(name));
	}
}