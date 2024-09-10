HttpHeaderFieldInfo *
httpHeaderBuildFieldsInfo(const HttpHeaderFieldAttrs * attrs, int count)
{
    int i;
    HttpHeaderFieldInfo *table = NULL;
    assert(attrs && count);

    /* allocate space */
    table = xcalloc(count, sizeof(HttpHeaderFieldInfo));

    for (i = 0; i < count; ++i) {
	const int id = attrs[i].id;
	HttpHeaderFieldInfo *info = table + id;
	/* sanity checks */
	assert(id >= 0 && id < count);
	assert(attrs[i].name);
	assert(info->id == 0 && info->type == 0);	/* was not set before */
	/* copy and init fields */
	info->id = id;
	info->type = attrs[i].type;
	stringInit(&info->name, attrs[i].name);
	assert(strLen(info->name));
	/* init stats */
	memset(&info->stat, 0, sizeof(info->stat));
    }
    return table;
}