bool
GeneralView::_CanFindServer(entry_ref* ref)
{
	// Try searching with be_roster
	if (be_roster->FindApp(kNotificationServerSignature, ref) == B_OK)
		return true;

	// Try with a query and take the first result
	BVolumeRoster vroster;
	BVolume volume;
	char volName[B_FILE_NAME_LENGTH];

	vroster.Rewind();

	while (vroster.GetNextVolume(&volume) == B_OK) {
		if ((volume.InitCheck() != B_OK) || !volume.KnowsQuery())
			continue;

		volume.GetName(volName);

		BQuery *query = new BQuery();
		query->SetPredicate("(BEOS:APP_SIG==\""kNotificationServerSignature"\")");
		query->SetVolume(&volume);
		query->Fetch();

		if (query->GetNextRef(ref) == B_OK)
			return true;
	}

	return false;
}