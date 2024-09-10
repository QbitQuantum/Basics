const char *
safegetprop_limited(dbref player, dbref what, dbref whom, dbref perms, const char *inbuf, int mesgtyp, int* blessed)
{
	const char *ptr;

	while (what != NOTHING) {
		ptr = safegetprop_strict(player, what, perms, inbuf, mesgtyp, blessed);
		if (!ptr)
			return ptr;
		if (*ptr) {
			if (OWNER(what) == whom || *blessed) {
				return ptr;
			}
		}
		what = getparent(what);
	}
	return "";
}