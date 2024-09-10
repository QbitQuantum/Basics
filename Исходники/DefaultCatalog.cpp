status_t
DefaultCatalog::ReadFromResource(const entry_ref &appOrAddOnRef)
{
	BFile file;
	status_t res = file.SetTo(&appOrAddOnRef, B_READ_ONLY);
	if (res != B_OK)
		return B_ENTRY_NOT_FOUND;

	BResources rsrc;
	res = rsrc.SetTo(&file);
	if (res != B_OK)
		return res;

	size_t sz;
	const void *buf = rsrc.LoadResource('CADA', fLanguageName, &sz);
	if (!buf)
		return B_NAME_NOT_FOUND;

	BMemoryIO memIO(buf, sz);
	res = Unflatten(&memIO);

	return res;
}