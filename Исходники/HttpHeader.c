int
httpHeaderIdByName(const char *name, int name_len, const HttpHeaderFieldInfo * info, int end)
{
    int i;
    for (i = 0; i < end; ++i) {
	if (name_len >= 0 && name_len != strLen(info[i].name))
	    continue;
	if (!strncasecmp(name, strBuf(info[i].name),
		name_len < 0 ? strLen(info[i].name) + 1 : name_len))
	    return i;
    }
    return -1;
}