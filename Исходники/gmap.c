map_gnode *
init_gmap(int groups)
{
	map_gnode *gmap;
	size_t len;

	if (!groups)
		groups = MAXGROUPNODE;
	len = sizeof(map_gnode) * groups;
	gmap = (map_gnode *) xmalloc(len);
	setzero(gmap, len);

	reset_gmap(gmap, groups);

	return gmap;
}