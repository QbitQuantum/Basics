static int
ci_compare(const void *p, const void *q)
{
	const char *pp = *(const char **)p;
	const char *qq = *(const char **)q;
	int ci;
	while (*pp && *qq) {
		if (toLOWER(*pp) != toLOWER(*qq))
			break;
		++pp;
		++qq;
	}
	ci = toLOWER(*pp) - toLOWER(*qq);
	if (ci == 0)
		return compare(p, q);
	return ci;
}