void
NotificationWindow::_LoadSettings(bool startMonitor)
{
	BPath path;
	BMessage settings;

	if (find_directory(B_USER_SETTINGS_DIRECTORY, &path) != B_OK)
		return;

	path.Append(kSettingsFile);

	BFile file(path.Path(), B_READ_ONLY | B_CREATE_FILE);
	settings.Unflatten(&file);

	_LoadGeneralSettings(settings);
	_LoadDisplaySettings(settings);
	_LoadAppFilters(settings);

	if (startMonitor) {
		node_ref nref;
		BEntry entry(path.Path());
		entry.GetNodeRef(&nref);

		if (watch_node(&nref, B_WATCH_ALL, BMessenger(this)) != B_OK) {
			BAlert* alert = new BAlert(B_TRANSLATE("Warning"),
				B_TRANSLATE("Couldn't start general settings monitor.\n"
					"Live filter changes disabled."), B_TRANSLATE("OK"));
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go(NULL);
		}
	}
}