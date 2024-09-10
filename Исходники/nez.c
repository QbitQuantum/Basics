static char *GetExt(char *filename) {
	char *p = filename, *p2 = 0;
	while (*p)
	{
		int l = mblen(p, MB_CUR_MAX);
		if (!l) break;
		if (*p == '/' || *p == '\\' || *p == ':') p2 = 0;
		if (*p == '.') p2 = p;
		p += l;
	}
	if (p2) return p2;
	return filename;
}