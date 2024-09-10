void
BootPromptWindow::_InitCatalog(bool saveSettings)
{
	// Initilialize the Locale Kit
	// TODO: The below code is a work-around for not being able to
	// call GetAppCatalog() more than once.
	be_catalog = be_app_catalog = NULL;
	// NOTE: be_catalog and be_app_catalog will point fo &fCatalog!

	be_locale->GetAppCatalog(&fCatalog);

	// Generate a settings file
	// TODO: This should not be necessary.
	// be_locale_roster->SetPreferredLanguages() should take care of things
	if (!saveSettings)
		return;

	BPath path;
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &path) != B_OK
		|| path.Append("Locale settings") != B_OK) {
		return;
	}

	BMessage settings;

	BFile file;
	if (file.SetTo(path.Path(), B_READ_ONLY) == B_OK)
		settings.Unflatten(&file);

	BString language;
	if (fCatalog.GetLanguage(&language) == B_OK) {
		settings.RemoveName("language");
		settings.AddString("language", language.String());
	}

	settings.RemoveName("country");
	BCountry country(language.String(), language.ToUpper());
	settings.AddString("country", country.Code());

	if (file.SetTo(path.Path(), B_CREATE_FILE | B_ERASE_FILE | B_WRITE_ONLY)
			!= B_OK
		|| settings.Flatten(&file) != B_OK) {
		fprintf(stderr, "Failed to write Local Kit settings!\n");
	}
}