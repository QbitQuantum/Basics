status_t
ThemeManager::LoadAddons()
{
	FENTRY;
	ThemesAddon *ta;
	BPath path;
	BDirectory dir;
	entry_ref ref;
#ifndef SINGLE_BINARY
	uint32 addonFlags;
	int dirwhich;
	int32 i;
	status_t err;
	image_id img;
	ThemesAddon *(*instantiate_func)();
#endif
	
#ifndef SINGLE_BINARY
	for (dirwhich = 0; dirwhich < 2; dirwhich++) {
		if (!dirwhich)	/* find system settings dir */
			err = find_directory(B_BEOS_ADDONS_DIRECTORY, &path);
		else			/* find user settings dir */
			err = find_directory(B_USER_ADDONS_DIRECTORY, &path);
		if (err)	return err;
		
		path.Append(Z_THEMES_ADDON_FOLDER);
		
		err = dir.SetTo(path.Path());
		if (err)	continue;
		
		err = dir.Rewind();
		if (err)	continue;
		
		while ((err = dir.GetNextRef(&ref)) == B_OK) {
			bool screwed = false;
			BPath imgpath(&ref);
			BString p(Z_THEMES_ADDON_FOLDER);
			p << "/" << ref.name;
			PRINT(("ThemeManager: trying to load_add_on(%s)\n", p.String()));
			img = load_add_on(imgpath.Path());
			if (img < B_OK)
				fprintf(stderr, "ThemeManager: load_add_on 0x%08lx\n", img);
			if (img < B_OK)
				continue;
			err = get_image_symbol(img, "instantiate_themes_addon", 
							B_SYMBOL_TYPE_TEXT, (void **)&instantiate_func);
			if (err)
				fprintf(stderr, "ThemeManager: get_image_symbol 0x%08lx\n", err);
			if (err)	continue;
			ta = instantiate_func();
			if (!ta)
				fprintf(stderr, "ThemeManager: instantiate_themes_addon returned NULL\n");
			if (!ta)
				continue;
			ta->SetImageId(img);
			/* check for existing names */
			for (i = 0; i < fAddonList.CountItems(); i++) {
				ThemesAddon *a = AddonAt(i);
				if (!a)
					fprintf(stderr, "ThemeManager: screwed! addon@%ld null\n", i);
				if (a->MessageName() && ta->MessageName() && 
							!strcmp(a->MessageName(), ta->MessageName())) {
					fprintf(stderr, "ThemeManager: screwed! addon@%ld has same msgname\n", i);
					screwed = true;
					break;
				}
				if (a->Name() && ta->Name() && 
							!strcmp(a->Name(), ta->Name())) {
					fprintf(stderr, "ThemeManager: screwed! addon@%ld has same name\n", i);
					screwed = true;
					break;
				}
			}
			if (screwed)
				continue;
			/* add it to the list */
			fAddonList.AddItem((void *)ta);
			PRINT(("ThemeManager: Added addon %ld '%s', msgname '%s'\n", ta->ImageId(), ta->Name(), ta->MessageName()));
		}
		//if (err)	return err;
	}
#else

#define ADDA(a) \
	if (ta) { \
		fAddonList.AddItem((void *)ta); \
		PRINT(("ThemeManager: Added addon %ld '%s', msgname '%s'\n", ta->ImageId(), ta->Name(), ta->MessageName())); \
	}


	ta = instantiate_themes_addon_backgrounds();
	ADDA(ta);
	ta = instantiate_themes_addon_beide();
	ADDA(ta);
	ta = instantiate_themes_addon_deskbar();
	ADDA(ta);
#ifndef ZETA_ADDONS
	ta = instantiate_themes_addon_eddie();
	ADDA(ta);
#endif
	ta = instantiate_themes_addon_pe();
	ADDA(ta);
	ta = instantiate_themes_addon_screensaver();
	ADDA(ta);
#ifndef ZETA_ADDONS
	ta = instantiate_themes_addon_soundplay();
	ADDA(ta);
#endif
	ta = instantiate_themes_addon_sounds();
	ADDA(ta);
	ta = instantiate_themes_addon_terminal();
	ADDA(ta);
#if defined(__ANTARES__) || defined(B_BEOS_VERSION_DANO)
	ta = instantiate_themes_addon_ui_settings();
	ADDA(ta);
#endif
#ifndef ZETA_ADDONS
	ta = instantiate_themes_addon_winamp_skin();
	ADDA(ta);
#endif
	ta = instantiate_themes_addon_window_decor();
	ADDA(ta);
#endif
	//if (err)	return err;
	fAddonCount = fAddonList.CountItems();
	PRINT(("ThemeManager: %ld addons loaded\n", fAddonCount));
	return B_OK;
}