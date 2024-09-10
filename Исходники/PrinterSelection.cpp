void PrinterSelectionView::FillVendors()
{
	BDirectory directory("/boot/beos/etc/ppd");
	BEntry entry;
	while (directory.GetNextEntry(&entry) == B_OK) {
		char name[B_FILE_NAME_LENGTH];
		entry.GetName(name);
		BPath path;
		entry.GetPath(&path);
		fVendors->AddItem(new FileItem(name, path.Path()));
	}
}