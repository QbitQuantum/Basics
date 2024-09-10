DeviceWatcher::DeviceWatcher()
	: BLooper("MIDI devices watcher"),
	fDeviceEndpointsMap(), fVectorIconData(NULL), fVectorIconDataSize(0),
	fLargeIcon(NULL), fMiniIcon(NULL)
{
	// Load midi endpoint vector icon data
	app_info info;
	be_app->GetAppInfo(&info);
	BFile file(&info.ref, B_READ_ONLY);

	BResources resources;
	if (resources.SetTo(&file) == B_OK) {
		size_t dataSize;
		// Load MIDI port endpoint vector icon
		const uint8* data = (const uint8*)resources.LoadResource(
			B_VECTOR_ICON_TYPE,	"endpoint_vector_icon", &dataSize);

		if (data != NULL && dataSize > 0)
			fVectorIconData = new(std::nothrow) uint8[dataSize];

		if (fVectorIconData) {
			// data is own by resources local object: copy its content for
			// later use
			memcpy(fVectorIconData, data, dataSize);
			fVectorIconDataSize = dataSize;
		}
	}

	// Render 32x32 and 16x16 B_CMAP8 icons for R5 compatibility
	if (fVectorIconData != NULL) {
		fLargeIcon = new(std::nothrow) BBitmap(BRect(0, 0, 31, 31), B_CMAP8);
		fMiniIcon  = new(std::nothrow) BBitmap(BRect(0, 0, 15, 15), B_CMAP8);

		if (BIconUtils::GetVectorIcon(fVectorIconData, fVectorIconDataSize,
			fLargeIcon) != B_OK) {
			delete fLargeIcon;
			fLargeIcon = NULL;
		}
		if (BIconUtils::GetVectorIcon(fVectorIconData, fVectorIconDataSize,
			fMiniIcon) != B_OK) {
			delete fMiniIcon;
			fMiniIcon = NULL;
		}
	}

	Start();
}