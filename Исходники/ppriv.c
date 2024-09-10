static int
parsespec(const char *spec)
{
	char *p;
	const char *q;
	int count;
	priv_set_t ***toupd;
	priv_set_t *upd;
	int i;
	boolean_t freeupd = B_TRUE;

	if (pri == NULL)
		loadprivinfo();

	p = strpbrk(spec, "+-=");

	if (p == NULL || p - spec > pri->priv_nsets)
		badspec(spec);

	if (p[1] == '\0' || (upd = priv_str_to_set(p + 1, ",", NULL)) == NULL)
		badspec(p + 1);

	count = p - spec;
	switch (*p) {
	case '+':
		toupd = &add;
		break;
	case '-':
		toupd = &rem;
		priv_inverse(upd);
		break;
	case '=':
		toupd = &assign;
		break;
	}

	/* Update all sets? */
	if (count == 0 || *spec == 'a' || *spec == 'A') {
		count = pri->priv_nsets;
		q = sets;
	} else
		q = spec;

	for (i = 0; i < count; i++) {
		int ind = strindex(q[i], sets);

		if (ind == -1)
			badspec(spec);

		/* Assign is mutually exclusive with add/remove and itself */
		if (((toupd == &rem || toupd == &add) && assign[ind] != NULL) ||
		    (toupd == &assign && (assign[ind] != NULL ||
		    rem[ind] != NULL || add[ind] != NULL))) {
			(void) fprintf(stderr, "%s: conflicting spec: %s\n",
			    command, spec);
			exit(1);
		}
		if ((*toupd)[ind] != NULL) {
			if (*p == '-')
				priv_intersect(upd, (*toupd)[ind]);
			else
				priv_union(upd, (*toupd)[ind]);
		} else {
			(*toupd)[ind] = upd;
			freeupd = B_FALSE;
		}
	}
	if (freeupd)
		priv_freeset(upd);
	return (0);
}