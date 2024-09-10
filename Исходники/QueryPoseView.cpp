QueryEntryListCollection::QueryEntryListCollection(Model* model,
	BHandler* target, PoseList* oldPoseList)
	:	fQueryListRep(new QueryListRep(new BObjectList<BQuery>(5, true)))
{
	Rewind();
	attr_info info;
	BQuery query;

	if (!model->Node()) {
		fStatus = B_ERROR;
		return;
	}

	// read the actual query string
	fStatus = model->Node()->GetAttrInfo(kAttrQueryString, &info);
	if (fStatus != B_OK)
		return;

	BString buffer;
	if (model->Node()->ReadAttr(kAttrQueryString, B_STRING_TYPE, 0,
		buffer.LockBuffer((int32)info.size),
			(size_t)info.size) != info.size) {
		fStatus = B_ERROR;
		return;
	}

	buffer.UnlockBuffer();

	// read the extra options
	MoreOptionsStruct saveMoreOptions;
	if (ReadAttr(model->Node(), kAttrQueryMoreOptions,
			kAttrQueryMoreOptionsForeign, B_RAW_TYPE, 0, &saveMoreOptions,
			sizeof(MoreOptionsStruct),
			&MoreOptionsStruct::EndianSwap) != kReadAttrFailed) {
		fQueryListRep->fShowResultsFromTrash = saveMoreOptions.searchTrash;
	}

	fStatus = query.SetPredicate(buffer.String());

	fQueryListRep->fOldPoseList = oldPoseList;
	fQueryListRep->fDynamicDateQuery = false;

	fQueryListRep->fRefreshEveryHour = false;
	fQueryListRep->fRefreshEveryMinute = false;

	if (model->Node()->ReadAttr(kAttrDynamicDateQuery, B_BOOL_TYPE, 0,
			&fQueryListRep->fDynamicDateQuery,
			sizeof(bool)) != sizeof(bool)) {
		fQueryListRep->fDynamicDateQuery = false;
	}

	if (fQueryListRep->fDynamicDateQuery) {
		// only refresh every minute on debug builds
		fQueryListRep->fRefreshEveryMinute = buffer.IFindFirst("second") != -1
			|| buffer.IFindFirst("minute") != -1;
		fQueryListRep->fRefreshEveryHour = fQueryListRep->fRefreshEveryMinute
			|| buffer.IFindFirst("hour") != -1;

#if !DEBUG
		// don't refresh every minute unless we are running debug build
		fQueryListRep->fRefreshEveryMinute = false;
#endif
	}

	if (fStatus != B_OK)
		return;

	bool searchAllVolumes = true;
	status_t result = B_OK;

	// get volumes to perform query on
	if (model->Node()->GetAttrInfo(kAttrQueryVolume, &info) == B_OK) {
		char* buffer = NULL;

		if ((buffer = (char*)malloc((size_t)info.size)) != NULL
			&& model->Node()->ReadAttr(kAttrQueryVolume, B_MESSAGE_TYPE, 0,
				buffer, (size_t)info.size) == info.size) {

			BMessage message;
			if (message.Unflatten(buffer) == B_OK) {
				for (int32 index = 0; ;index++) {
					ASSERT(index < 100);
					BVolume volume;
						// match a volume with the info embedded in
						// the message
					result = MatchArchivedVolume(&volume, &message, index);
					if (result == B_OK) {
						// start the query on this volume
						result = FetchOneQuery(&query, target,
							fQueryListRep->fQueryList, &volume);
						if (result != B_OK)
							continue;

						searchAllVolumes = false;
					} else if (result != B_DEV_BAD_DRIVE_NUM) {
						// if B_DEV_BAD_DRIVE_NUM, the volume just isn't
						// mounted this time around, keep looking for more
						// if other error, bail
						break;
					}
				}
			}
		}

		free(buffer);
	}

	if (searchAllVolumes) {
		// no specific volumes embedded in query, search everything
		BVolumeRoster roster;
		BVolume volume;

		roster.Rewind();
		while (roster.GetNextVolume(&volume) == B_OK)
			if (volume.IsPersistent() && volume.KnowsQuery()) {
				result = FetchOneQuery(&query, target,
					fQueryListRep->fQueryList, &volume);
				if (result != B_OK)
					continue;
			}
	}

	fStatus = B_OK;
	return;
}