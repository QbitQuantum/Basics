status_t
CDDBQuery::_OpenContentFile(const int32 &discID)
{
	// Makes sure that the lookup has a valid file to work with for the CD
	// content. Returns true if there is an existing file, false if a lookup is
	// required.

	BFile file;
	BString predicate;
	predicate << "CD:key == " << discID;
	entry_ref ref;

	BVolumeRoster roster;
	BVolume volume;
	roster.Rewind();
	while (roster.GetNextVolume(&volume) == B_OK) {
		if (volume.IsReadOnly() || !volume.IsPersistent() || !volume.KnowsAttr()
			|| !volume.KnowsQuery())
			continue;

		// make sure the volume we are looking at is indexed right
		fs_create_index(volume.Device(), "CD:key", B_INT32_TYPE, 0);

		BQuery query;
		query.SetVolume(&volume);
		query.SetPredicate(predicate.String());
		if (query.Fetch() != B_OK)
			continue;

		if (query.GetNextRef(&ref) == B_OK) 
			break;
	}

	status_t status = fCDData.Load(ref);
	if (status == B_NO_INIT) {
		// We receive this error when the Load() function couldn't load the
		// track times This just means that we get it from the SCSI data given
		// to us in SetToCD
		vector<CDAudioTime> times;
		GetTrackTimes(&fSCSIData,times);

		for (int32 i = 0; i < fCDData.CountTracks(); i++) {
			CDAudioTime *item = fCDData.TrackTimeAt(i);
			*item = times[i + 1] - times[i];
		}

		status = B_OK;
	}

	return status;
}