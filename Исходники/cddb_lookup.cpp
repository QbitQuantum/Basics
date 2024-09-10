status_t
CDDBLookup::_WriteCDData(dev_t device, const QueryResponseData& diskData,
	const ReadResponseData& readResponse)
{
	// Rename volume.
	BVolume volume(device);

	status_t error = B_OK;

	BString name = diskData.artist;
	name += " - ";
	name += diskData.title;
	name.ReplaceSet("/", " ");

	status_t result = volume.SetName(name.String());
	if (result != B_OK) {
		printf("Can't set volume name.\n");
		return result;
	}

	// Rename tracks and add relevant Audio attributes.
	BDirectory cddaRoot;
	volume.GetRootDirectory(&cddaRoot);

	BEntry entry;
	int index = 0;
	while (cddaRoot.GetNextEntry(&entry) == B_OK) {
		TrackData* track = readResponse.tracks.ItemAt(index);

		// Update name.
		int trackNum = index + 1; // index=0 is actually Track 1
		name.SetToFormat("%02d %s.wav", trackNum, track->title.String());
		name.ReplaceSet("/", " ");

		result = entry.Rename(name.String());
		if (result != B_OK) {
			fprintf(stderr, "%s: Failed renaming entry at index %d to "
				"\"%s\".\n", kProgramName, index, name.String());
			error = result;
				// User can benefit from continuing through all tracks.
				// Report error later.
		}

		// Add relevant attributes. We consider an error here as non-fatal.
		BNode node(&entry);
		node.WriteAttrString("Media:Title", &track->title);
		node.WriteAttrString("Audio:Album", &readResponse.title);
		if (readResponse.genre.Length() != 0)
			node.WriteAttrString("Media:Genre", &readResponse.genre);
		if (readResponse.year != 0) {
			node.WriteAttr("Media:Year", B_INT32_TYPE, 0,
				&readResponse.year, sizeof(int32));
		}

		if (track->artist == "")
			node.WriteAttrString("Audio:Artist", &readResponse.artist);
		else
			node.WriteAttrString("Audio:Artist", &track->artist);

		index++;
	}

	return error;
}