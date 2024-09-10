BBitmap*
BrowserToolbar::_RetrieveBitmap(const char *name)
{
	BResources *resource = BApplication::AppResources();
	size_t size = 0;

	const void *data = resource->LoadResource('TBBM', name, &size);
	if (!data)
		return NULL;

	BBitmap *bitmap = new BBitmap(BRect(0, 0, 15, 15), B_RGBA32);
	if (BIconUtils::GetVectorIcon((const uint8 *)data, size, bitmap) != B_OK)
		return NULL;

	return bitmap;
}