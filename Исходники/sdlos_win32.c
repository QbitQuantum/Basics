const char *osd_get_volume_name(int idx)
{
	static char szBuffer[128];
	const char *p;

	GetLogicalDriveStringsA(ARRAY_LENGTH(szBuffer), szBuffer);

	p = szBuffer;
	while(idx--) {
		p += strlen(p) + 1;
		if (!*p) return NULL;
	}

	return p;
}