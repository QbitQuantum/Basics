int w_numcmp(const void *a, const void *b)
{
	wchar_t *pa = ((const kw_t*)a)->w->s, *pb = ((const kw_t*)b)->w->s;
	int sa, sb, ea, eb;
	while (*pa && *pb) {
		if (iswdigit(*pa) && iswdigit(*pb)) {
			/* skip leading zeros */
			sa = sb = 0;
			while (pa[sa] == L'0') sa++;
			while (pb[sb] == L'0') sb++;
			/* find end of numbers */
			ea = sa; eb = sb;
			while (iswdigit(pa[ea])) ea++;
			while (iswdigit(pb[eb])) eb++;
			if (eb - sb > ea - sa) return -1;
			if (eb - sb < ea - sa) return 1;
			while (sb < eb) {
				if (pa[sa] > pb[sb]) return 1;
				if (pa[sa] < pb[sb]) return -1;
				sa++; sb++;
			}

			pa += ea; pb += eb;
		}
		else if (iswdigit(*pa)) return 1;
		else if (iswdigit(*pb)) return -1;
		else {
			if (*pa > *pb) return 1;
			if (*pa < *pb) return -1;
			pa++; pb++;
		}
	}
	return (!*pa && !*pb) ? 0 : *pa ?  1 : -1;
}