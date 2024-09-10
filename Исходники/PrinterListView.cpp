BBitmap*
PrinterItem::_LoadVectorIcon(const char* resourceName, float iconSize)
{
	size_t dataSize;
	BResources* resources = BApplication::AppResources();
	const void* data = resources->LoadResource(B_VECTOR_ICON_TYPE,
		resourceName, &dataSize);

	if (data != NULL){
		BBitmap *iconBitmap = new BBitmap(BRect(0, 0, iconSize - 1,
			iconSize - 1), 0, B_RGBA32);
		if (BIconUtils::GetVectorIcon(
				reinterpret_cast<const uint8*>(data),
				dataSize, iconBitmap) == B_OK)
			return iconBitmap;
		else
			delete iconBitmap;
	};
	return NULL;
}