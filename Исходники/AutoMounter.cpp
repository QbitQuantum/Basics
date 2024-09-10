void
AutoMounter::_MountVolume(const BMessage* message)
{
	int32 id;
	if (message->FindInt32("id", &id) != B_OK)
		return;

	BDiskDeviceRoster roster;
	BPartition *partition;
	BDiskDevice device;
	if (roster.GetPartitionWithID(id, &device, &partition) != B_OK)
		return;

	uint32 mountFlags;
	if (!_SuggestMountFlags(partition, &mountFlags))
		return;

	status_t status = partition->Mount(NULL, mountFlags);
	if (status < B_OK) {
		char text[512];
		snprintf(text, sizeof(text),
			B_TRANSLATE("Error mounting volume:\n\n%s"), strerror(status));
		BAlert* alert = new BAlert(B_TRANSLATE("Mount error"), text,
			B_TRANSLATE("OK"));
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go(NULL);
	}
}