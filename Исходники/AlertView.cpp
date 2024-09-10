BBitmap*
AlertView::InitIcon()
{
	// This is how BAlert gets to its icon
	BBitmap* icon = NULL;
	BPath path;
	if (find_directory(B_BEOS_SERVERS_DIRECTORY, &path) == B_OK) {
		path.Append("app_server");
		BResources resources;
		BFile file;
		if (file.SetTo(path.Path(), B_READ_ONLY) == B_OK
			&& resources.SetTo(&file) == B_OK) {
			size_t size;
			const void* data = resources.LoadResource(B_VECTOR_ICON_TYPE,
				"warn", &size);
			if (data) {
				icon = new BBitmap(BRect(0, 0, 31, 31), 0, B_RGBA32);
				if (BIconUtils::GetVectorIcon((const uint8*)data, size, icon)
						!= B_OK) {
					delete icon;
					icon = NULL;
				}
			}
		}
	}

	return icon;
}