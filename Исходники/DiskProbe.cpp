void
DiskProbe::RefsReceived(BMessage* message)
{
	bool traverseLinks = (modifiers() & B_SHIFT_KEY) == 0;

	int32 index = 0;
	entry_ref ref;
	while (message->FindRef("refs", index++, &ref) == B_OK) {
		const char* attribute = NULL;
		if (message->FindString("attributes", index - 1, &attribute) == B_OK)
			traverseLinks = false;

		BEntry entry;
		status_t status = entry.SetTo(&ref, traverseLinks);

		if (status == B_OK)
			status = Probe(entry, attribute);

		if (status != B_OK) {
			char buffer[1024];
			snprintf(buffer, sizeof(buffer),
				B_TRANSLATE_COMMENT("Could not open \"%s\":\n"
				"%s", "Opening of entry reference buffer for a DiskProbe "
				"request Alert message. The name of entry reference and "
				"error message is shown."),
				ref.name, strerror(status));

			BAlert* alert = new BAlert(B_TRANSLATE("DiskProbe request"),
				buffer, B_TRANSLATE("OK"), NULL, NULL,
				B_WIDTH_AS_USUAL, B_STOP_ALERT);
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
		}
	}
}