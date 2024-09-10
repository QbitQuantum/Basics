TypeItem*
TResourceSet::LoadResource(type_code type, int32 id, const char* name,
	TypeList** inOutList)
{
	TypeItem* item = NULL;

	if (name) {
		BEntry entry;

		// If a named resource, first look in directories.
		fLock.Lock();
		int32 count = fDirectories.CountItems();
		for (int32 i = 0; item == 0 && i < count; i++) {
			BPath* dir = (BPath*)fDirectories.ItemAt(i);
			if (dir) {
				fLock.Unlock();
				BPath path(dir->Path(), name);
				if (entry.SetTo(path.Path(), true) == B_OK ) {
					BFile file(&entry, B_READ_ONLY);
					if (file.InitCheck() == B_OK ) {
						item = new TypeItem(id, name, &file);
						item->SetSourceIsFile(true);
					}
				}
				fLock.Lock();
			}
		}
		fLock.Unlock();
	}

#if USE_RESOURCES
	if (!item) {
		// Look through resource objects for data.
		fLock.Lock();
		int32 count = fResources.CountItems();
		for (int32 i = 0; item == 0 && i < count; i++ ) {
			BResources* resource = (BResources*)fResources.ItemAt(i);
			if (resource) {
				const void* data = NULL;
				size_t size = 0;
				if (id >= 0)
					data = resource->LoadResource(type, id, &size);
				else if (name != NULL)
					data = resource->LoadResource(type, name, &size);

				if (data && size) {
					item = new TypeItem(id, name, data, size);
					item->SetSourceIsFile(false);
				}
			}
		}
		fLock.Unlock();
	}
#endif

	if (item) {
		TypeList* list = inOutList ? *inOutList : NULL;
		if (!list) {
			// Don't currently have a list for this type -- check if there is
			// already one.
			list = FindTypeList(type);
		}

		BAutolock lock(&fLock);

		if (!list) {
			// Need to make a new list for this type.
			list = new TypeList(type);
			fTypes.AddItem(list);
		}
		if (inOutList)
			*inOutList = list;

		list->AddItem(item);
	}

	return item;
}