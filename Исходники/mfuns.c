const char *
mfn_select(MFUNARGS)
{
	char origprop[BUFFER_LEN];
	char propname[BUFFER_LEN];
	char bestname[BUFFER_LEN];
	dbref obj = what;
	dbref bestobj = 0;
	char *pname;
	const char *ptr;
	char *out, *in;
	int i, targval, bestval;
	int baselen;
	int limit;
	int blessed = 0;

	pname = argv[1];
	if (argc == 3) {
		obj = mesg_dbref(descr, player, what, perms, argv[2], mesgtyp);
	}
	if (obj == PERMDENIED)
		ABORT_MPI("SELECT", "Permission denied.");
	if (obj == UNKNOWN || obj == AMBIGUOUS || obj == NOTHING || obj == HOME)
		ABORT_MPI("SELECT", "Match failed.");

	/*
	 * Search contiguously for a bit, looking for a best match.
	 * This allows fast hits on LARGE lists.
	 */

	limit = 18;
	i = targval = atoi(argv[0]);
	do {
		ptr = get_list_item(player, obj, perms, (char *)pname, i--, mesgtyp, &blessed);
	} while (limit-->0 && i >= 0 && ptr && !*ptr);
	if (ptr == NULL)
		ABORT_MPI("SELECT", "Failed list read.");
	if (*ptr != '\0')
		return ptr;

	/*
	 * If we didn't find it before, search only existing props.
	 * This gets fast hits on very SPARSE lists.
	 */

	/* First, normalize the base propname */
	out = origprop;
	in = argv[1];
	while (*in != '\0') {
		*out++ = PROPDIR_DELIMITER;
		while (*in == PROPDIR_DELIMITER) in++;
		while (*in && *in != PROPDIR_DELIMITER) *out++ = *in++;
	}
	*out++ = '\0';

	i = targval;
	bestname[0] = '\0';
	bestval = 0;
	baselen = strlen(origprop);
	for (; obj != NOTHING; obj = getparent(obj)) {
		pname = next_prop_name(obj, propname, sizeof(propname), origprop);
		while (pname && string_prefix(pname, origprop)) {
			ptr = pname + baselen;
			if (*ptr == NUMBER_TOKEN) ptr++;
			if (!*ptr && is_propdir(obj, pname)) {
				char propname2[BUFFER_LEN];
				char *pname2;
				int sublen = strlen(pname);

				pname2 = strcpyn(propname2, sizeof(propname2), pname);
				propname2[sublen++] = PROPDIR_DELIMITER;
				propname2[sublen] = '\0';

				pname2 = next_prop_name(obj, propname2, sizeof(propname2), pname2);
				while (pname2) {
					ptr = pname2 + sublen;
					if (number(ptr)) {
						i = atoi(ptr);
						if (bestval < i && i <= targval) {
							bestval = i;
							bestobj = obj;
							strcpyn(bestname, sizeof(bestname), pname2);
						}
					}
					pname2 = next_prop_name(obj, propname2, sizeof(propname2), pname2);
				}
			}
			ptr = pname + baselen;
			if (number(ptr)) {
				i = atoi(ptr);
				if (bestval < i && i <= targval) {
					bestval = i;
					bestobj = obj;
					strcpyn(bestname, sizeof(bestname), pname);
				}
			}
			pname = next_prop_name(obj, propname, sizeof(propname), pname);
		}
	}
	
	if (*bestname) {
		ptr = safegetprop_strict(player, bestobj, perms, bestname, mesgtyp, &blessed);
		if (!ptr)
			ABORT_MPI("SELECT", "Failed property read.");
	} else {
		ptr = "";
	}
	return ptr;
}