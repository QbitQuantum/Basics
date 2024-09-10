bool
BNavMenu::StartBuildingItemList()
{
	BEntry entry;

	if (fNavDir.device < 0 || entry.SetTo(&fNavDir) != B_OK
		|| !entry.Exists()) 
		return false;

	fItemList = new BObjectList<BMenuItem>(50);

	fIteratingDesktop = false;
	
	BDirectory parent;
	status_t status = entry.GetParent(&parent);

	// if ref is the root item then build list of volume root dirs
	fFlags = uint8((fFlags & ~kVolumesOnly) | (status == B_ENTRY_NOT_FOUND ? kVolumesOnly : 0));
	if (fFlags & kVolumesOnly)
		return true;
		
	Model startModel(&entry, true);
	if (startModel.InitCheck() != B_OK || !startModel.IsContainer()) 
		return false;

	if (startModel.IsQuery()) 
		fContainer = new QueryEntryListCollection(&startModel);
	else if (FSIsDeskDir(&entry)) {
		fIteratingDesktop = true;
		fContainer = DesktopPoseView::InitDesktopDirentIterator(0, startModel.EntryRef());
		AddRootItemsIfNeeded();
	} else if (FSIsTrashDir(&entry)) {
		// the trash window needs to display a union of all the
		// trash folders from all the mounted volumes
		BVolumeRoster volRoster;
		volRoster.Rewind();
		BVolume volume;
		fContainer = new EntryIteratorList();
		
		while (volRoster.GetNextVolume(&volume) == B_OK) {
			if (!volume.IsPersistent())
				continue;
			
			BDirectory trashDir;
			
			if (FSGetTrashDir(&trashDir, volume.Device()) == B_OK)
				dynamic_cast<EntryIteratorList *>(fContainer)->
					AddItem(new DirectoryEntryList(trashDir));
		}
	} else
		fContainer = new DirectoryEntryList(*dynamic_cast<BDirectory *>
			(startModel.Node()));
	
	if (fContainer == NULL || fContainer->InitCheck() != B_OK)
		return false;

	fContainer->Rewind();

	return true;
}