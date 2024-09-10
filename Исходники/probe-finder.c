/* Find an appropriate scope fits to given conditions */
static Dwarf_Die *find_best_scope(struct probe_finder *pf, Dwarf_Die *die_mem)
{
	struct find_scope_param fsp = {
		.function = pf->pev->point.function,
		.file = pf->fname,
		.line = pf->lno,
		.diff = INT_MAX,
		.die_mem = die_mem,
		.found = false,
	};

	cu_walk_functions_at(&pf->cu_die, pf->addr, find_best_scope_cb, &fsp);

	return fsp.found ? die_mem : NULL;
}

static int probe_point_line_walker(const char *fname, int lineno,
				   Dwarf_Addr addr, void *data)
{
	struct probe_finder *pf = data;
	Dwarf_Die *sc_die, die_mem;
	int ret;

	if (lineno != pf->lno || strtailcmp(fname, pf->fname) != 0)
		return 0;

	pf->addr = addr;
	sc_die = find_best_scope(pf, &die_mem);
	if (!sc_die) {
		pr_warning("Failed to find scope of probe point.\n");
		return -ENOENT;
	}

	ret = call_probe_finder(sc_die, pf);

	/* Continue if no error, because the line will be in inline function */
	return ret < 0 ? ret : 0;
}

/* Find probe point from its line number */
static int find_probe_point_by_line(struct probe_finder *pf)
{
	return die_walk_lines(&pf->cu_die, probe_point_line_walker, pf);
}

/* Find lines which match lazy pattern */
static int find_lazy_match_lines(struct list_head *head,
				 const char *fname, const char *pat)
{
	FILE *fp;
	char *line = NULL;
	size_t line_len;
	ssize_t len;
	int count = 0, linenum = 1;

	fp = fopen(fname, "r");
	if (!fp) {
		pr_warning("Failed to open %s: %s\n", fname, strerror(errno));
		return -errno;
	}

	while ((len = getline(&line, &line_len, fp)) > 0) {

		if (line[len - 1] == '\n')
			line[len - 1] = '\0';

		if (strlazymatch(line, pat)) {
			line_list__add_line(head, linenum);
			count++;
		}
		linenum++;
	}

	if (ferror(fp))
		count = -errno;
	free(line);
	fclose(fp);

	if (count == 0)
		pr_debug("No matched lines found in %s.\n", fname);
	return count;
}