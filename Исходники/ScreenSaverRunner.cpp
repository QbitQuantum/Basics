void
ScreenSaverRunner::_LoadAddOn()
{
	// This is a new set of preferences. Free up what we did have
	// TODO: this is currently not meant to be used after creation
	if (fThread >= B_OK) {
		Suspend();
		if (fSaver != NULL)
			fSaver->StopSaver();
	}
	_CleanUp();

	if (!strcmp("", fSettings.ModuleName())) {
		Resume();
		return;
	}

	BScreenSaver* (*instantiate)(BMessage*, image_id);

	// try all directories until the first one succeeds

	directory_which which[] = {
		B_USER_ADDONS_DIRECTORY,
		B_COMMON_ADDONS_DIRECTORY,
		B_SYSTEM_ADDONS_DIRECTORY,
	};
	BPath path;

	for (uint32 i = 0; i < sizeof(which) / sizeof(which[0]); i++) {
		if (find_directory(which[i], &path, false) != B_OK)
			continue;

		path.Append("Screen Savers");
		path.Append(fSettings.ModuleName());

		fAddonImage = load_add_on(path.Path());
		if (fAddonImage >= B_OK)
			break;
	}

	if (fAddonImage < B_OK) {
		printf("Unable to open add-on: %s: %s\n", path.Path(), strerror(fAddonImage));
	} else {
		// Look for the one C function that should exist.
		if (get_image_symbol(fAddonImage, "instantiate_screen_saver",
				B_SYMBOL_TYPE_TEXT, (void **)&instantiate) != B_OK) {
			printf("Unable to find the instantiator\n");
		} else {
			BMessage state;
			fSettings.GetModuleState(fSettings.ModuleName(), &state);
			fSaver = instantiate(&state, fAddonImage);
		}

		if (fSaver->InitCheck() != B_OK) {
			printf("ScreenSaver initialization failed: %s!\n", strerror(fSaver->InitCheck()));
			_CleanUp();
		}
	}

	Resume();
}