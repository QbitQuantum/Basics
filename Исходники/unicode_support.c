int rename_utf8(const char *oldname_utf8, const char *newname_utf8)
{
	int ret = -1;
	
	wchar_t *oldname_utf16 = utf8_to_utf16(oldname_utf8);
	wchar_t *newname_utf16 = utf8_to_utf16(newname_utf8);
	
	if(oldname_utf16 && newname_utf16)
	{
		_wunlink(newname_utf16);
		ret = _wrename(oldname_utf16, newname_utf16);
	}

	if(newname_utf16) free(newname_utf16);
	if(oldname_utf16) free(oldname_utf16);

	return ret;
}