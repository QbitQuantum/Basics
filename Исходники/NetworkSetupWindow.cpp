void
NetworkSetupWindow::_BuildShowMenu(BMenu* menu, int32 msg_what)
{
	menu->SetRadioMode(true);		
	BPath path;
	BPath addon_path;
	BDirectory dir;
	BEntry entry;

	char* search_paths = getenv("ADDON_PATH");
	if (!search_paths)
		return;

	fMinAddonViewRect.Set(0, 0, 200, 200);	// Minimum size
		
	search_paths = strdup(search_paths);	
	char* next_path_token;
	char* search_path = strtok_r(search_paths, ":", &next_path_token);
	
	while (search_path) {
		if (strncmp(search_path, "%A/", 3) == 0) {
			app_info ai;			
			be_app->GetAppInfo(&ai);
			entry.SetTo(&ai.ref);
			entry.GetPath(&path);
			path.GetParent(&path);
			path.Append(search_path + 3);
		} else {
			path.SetTo(search_path);
			path.Append("network_setup");
		}

		search_path = strtok_r(NULL, ":", &next_path_token);
		
		dir.SetTo(path.Path());
		if (dir.InitCheck() != B_OK)
			continue;
		
		dir.Rewind();
		while (dir.GetNextEntry(&entry) >= 0) {
			if (entry.IsDirectory())
				continue;

			entry.GetPath(&addon_path);
			image_id addon_id = load_add_on(addon_path.Path());
			if (addon_id < 0) {
				printf("Failed to load %s addon: %s.\n", addon_path.Path(), 
					strerror(addon_id));
				continue;
			}

			network_setup_addon_instantiate get_nth_addon;
			status_t status = get_image_symbol(addon_id, "get_nth_addon", 
				B_SYMBOL_TYPE_TEXT, (void **) &get_nth_addon);
				
			if (status == B_OK) {
				NetworkSetupAddOn *addon;
				int n = 0;
				while ((addon = get_nth_addon(addon_id, n)) != NULL) {
					BMessage* msg = new BMessage(msg_what);
					
					BRect r(0, 0, 0, 0);
					BView* addon_view = addon->CreateView(&r);
					fMinAddonViewRect = fMinAddonViewRect | r;
					
					msg->AddInt32("image_id", addon_id);
					msg->AddString("addon_path", addon_path.Path());
					msg->AddPointer("addon", addon);
					msg->AddPointer("addon_view", addon_view);
					menu->AddItem(new BMenuItem(addon->Name(), msg));
					n++;
				}
				continue;
			}

			//  No "addon instantiate function" symbol found in this addon
			printf("No symbol \"get_nth_addon\" found in %s addon: not a "
				"network setup addon!\n", addon_path.Path());
			unload_add_on(addon_id);
		}
	}

	free(search_paths);
}	