BBitmap*
MediaAlert::InitIcon()
{
	// The alert icons are in the app_server resources
	BBitmap* icon = NULL;
	BPath path;
	if (find_directory(B_BEOS_SERVERS_DIRECTORY, &path) == B_OK) {
		path.Append("app_server");
		BFile file;
		if (file.SetTo(path.Path(), B_READ_ONLY) == B_OK) {
			BResources resources;
			if (resources.SetTo(&file) == B_OK) {
				// Which icon are we trying to load?
				const char* iconName = "warn";

				// Load the raw icon data
				size_t size;
				const void* rawIcon =
					resources.LoadResource(B_VECTOR_ICON_TYPE, iconName, &size);

				if (rawIcon != NULL) {
					// Now build the bitmap
					icon = new BBitmap(BRect(0, 0, 31, 31), B_RGBA32);
					if (BIconUtils::GetVectorIcon((const uint8*)rawIcon, size,
							icon) != B_OK) {
						delete icon;
						return NULL;
					}
				}
			}
		}
	}

	return icon;
}