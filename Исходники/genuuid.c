int fill_entry_struct(struct Entry *entry, const struct Rc *rc,
                      const struct Options *opt)
{
	unsigned int i;

	assert(entry);
	assert(rc);
	assert(opt);

	/*
	 * Get information about the environment; hostname, current directory, 
	 * login name and tty.
	 *
	 * Fixme: Add check so this and the session info thing are run only 
	 * once. Only has some effect if creating many UUIDs.
	 */

	entry->host = get_hostname(rc);
	if (!entry->host) {
		myerror("fill_entry_struct(): Cannot get hostname");
		return EXIT_FAILURE;
	}
	if (!valid_hostname(entry->host)) {
		myerror("fill_entry_struct(): Got invalid hostname: \"%s\"",
		        entry->host);
		return EXIT_FAILURE;
	}
	entry->cwd = getpath();
	entry->user = get_username();
	entry->tty = get_tty();

	/*
	 * Store tags and comment in entry.
	 */

	for (i = 0; i < MAX_TAGS && opt->tag[i]; i++)
		if (store_tag(entry, opt->tag[i]) == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (opt->comment) {
		entry->txt = process_comment_option(opt->comment);
		if (!entry->txt)
			return EXIT_FAILURE;
	}

	/*
	 * Store session information from the environment variable.
	 */

	if (get_sess_info(entry) == EXIT_FAILURE) {
		free(entry->txt);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}