void
BSlowContextMenu::BuildVolumeMenu()
{
	BVolumeRoster roster;
	BVolume	volume;

	roster.Rewind();
	while (roster.GetNextVolume(&volume) == B_OK) {
		
		if (!volume.IsPersistent())
			continue;
		
		BDirectory startDir;
		if (volume.GetRootDirectory(&startDir) == B_OK) {
			BEntry entry;
			startDir.GetEntry(&entry);

			Model *model = new Model(&entry);
			if (model->InitCheck() != B_OK) {
				delete model;
				continue;
			}
			
			BNavMenu *menu = new BNavMenu(model->Name(), fMessage.what,
				fMessenger, fParentWindow, fTypesList);

			menu->SetNavDir(model->EntryRef());
			menu->InitTrackingHook(fTrackingHook.fTrackingHook, &(fTrackingHook.fTarget),
				fTrackingHook.fDragMessage);

			ASSERT(menu->Name());

			ModelMenuItem *item = new ModelMenuItem(model, menu);
			BMessage *message = new BMessage(fMessage);

			message->AddRef("refs", model->EntryRef());
			item->SetMessage(message);
			fItemList->AddItem(item);
			ASSERT(item->Label());
		}
	}
}