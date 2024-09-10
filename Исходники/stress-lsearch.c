/*
 *  stress_lsearch()
 *	stress lsearch
 */
static int stress_lsearch(const args_t *args)
{
	int32_t *data, *root;
	size_t i, max;
	uint64_t lsearch_size = DEFAULT_LSEARCH_SIZE;

	if (!get_setting("lsearch-size", &lsearch_size)) {
		if (g_opt_flags & OPT_FLAGS_MAXIMIZE)
			lsearch_size = MAX_LSEARCH_SIZE;
		if (g_opt_flags & OPT_FLAGS_MINIMIZE)
			lsearch_size = MIN_LSEARCH_SIZE;
	}
	max = (size_t)lsearch_size;

	if ((data = calloc(max, sizeof(*data))) == NULL) {
		pr_fail_dbg("malloc");
		return EXIT_NO_RESOURCE;
	}
	if ((root = calloc(max, sizeof(*data))) == NULL) {
		free(data);
		pr_fail_dbg("malloc");
		return EXIT_NO_RESOURCE;
	}

	do {
		size_t n = 0;

		/* Step #1, populate with data */
		for (i = 0; g_keep_stressing_flag && i < max; i++) {
			void *ptr;

			data[i] = ((mwc32() & 0xfff) << 20) ^ i;
			ptr = lsearch(&data[i], root, &n, sizeof(*data), cmp);
			(void)ptr;
		}
		/* Step #2, find */
		for (i = 0; g_keep_stressing_flag && i < n; i++) {
			int32_t *result;

			result = lfind(&data[i], root, &n, sizeof(*data), cmp);
			if (g_opt_flags & OPT_FLAGS_VERIFY) {
				if (result == NULL)
					pr_fail("%s: element %zu could not be found\n", args->name, i);
				else if (*result != data[i])
					pr_fail("%s: element %zu found %" PRIu32 ", expecting %" PRIu32 "\n",
					args->name, i, *result, data[i]);
			}
		}
		inc_counter(args);
	} while (keep_stressing());

	free(root);
	free(data);
	return EXIT_SUCCESS;
}