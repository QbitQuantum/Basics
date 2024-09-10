status_t
CDDBDaemon::_WriteCDData(dev_t device, QueryResponseData* diskData,
	ReadResponseData* readResponse)
{
	// Rename volume.
	BVolume volume(device);
	
	status_t result;
	status_t error = B_OK;
	
	BString name = diskData->artist << " - " << diskData->title;
	name.ReplaceSet("/", " ");
	
	if ((result = volume.SetName(name.String())) != B_OK) {
		printf("Can't set volume name.\n");
		return result;
	}
	
	// Rename tracks and add relevant Audio attributes.	
	BDirectory cddaRoot;
	volume.GetRootDirectory(&cddaRoot);
	
	BEntry entry;
	int index = 0;
	while (cddaRoot.GetNextEntry(&entry) == B_OK) {
		TrackData* data = (TrackData*)((readResponse->tracks).ItemAt(index));
		
		// Update name.
		name = data->title;
		name.ReplaceSet("/", " ");
		
		if ((result = entry.Rename(name.String())) != B_OK) {
			printf("Failed renaming entry at index %d to \"%s\".\n", index,
				name.String());
			error = result;
				// User can benefit from continuing through all tracks.
				// Report error later.
		}
		
		// Add relevant attributes. We consider an error here as non-fatal.
		BNode node(&entry);
		node.WriteAttr("Audio:Title", B_STRING_TYPE, 0, (data->title).String(),
			(data->title).Length());
		node.WriteAttr("Audio:Album", B_STRING_TYPE, 0,
			(readResponse->title).String(),
			(readResponse->title).Length());
		node.WriteAttr("Audio:Genre", B_STRING_TYPE, 0,
			(readResponse->genre).String(),
			(readResponse->genre).Length());
		node.WriteAttr("Audio:Year", B_INT32_TYPE, 0, &(readResponse->year),
			sizeof(int32));

		if (data->artist == "") {
			node.WriteAttr("Audio:Artist", B_STRING_TYPE, 0,
				(readResponse->artist).String(),
				(readResponse->artist).Length());
		} else {
			node.WriteAttr("Audio:Artist", B_STRING_TYPE, 0,
				(data->artist).String(), (data->artist).Length());			
		}
			
		index++;
	}
	
	return error;
}	