/*
 * cset_in_hard --
 *	Determine whether a character is in the set without using
 *	the cache.
 */
bool
cset_in_hard(struct cset *cs, wchar_t ch)
{
	struct csclass *csc;

	for (csc = cs->cs_classes; csc != NULL; csc = csc->csc_next)
		if (csc->csc_invert ^ (iswctype(ch, csc->csc_type) != 0))
			return (cs->cs_invert ^ true);
	if (cs->cs_root != NULL) {
		cs->cs_root = cset_splay(cs->cs_root, ch);
		return (cs->cs_invert ^ (cset_rangecmp(cs->cs_root, ch) == 0));
	}
	return (cs->cs_invert ^ false);
}