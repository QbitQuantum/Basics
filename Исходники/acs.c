int main(int argc, char **argv)
{
	struct nl80211_state nlstate;
	int devidx = 0;
	char *devname;
	int err;
	unsigned int surveys = 10;

        /* strip off self */
	argc--;
	argv0 = *argv++;

	if (argc > 0 && strcmp(*argv, "--debug") == 0) {
		nl_debug = 1;
		argc--;
		argv++;
	}

	if (argc > 0 && strcmp(*argv, "--version") == 0) {
		version();
		return 0;
	}

	/* need to treat "help" command specially so it works w/o nl80211 */
	if (argc == 0 || strcmp(*argv, "help") == 0) {
		usage();
		return 0;
	}

	err = nl80211_init(&nlstate);
	if (err)
		return 1;

	if (argc <= 0) {
		return 1;
	}

	devidx = if_nametoindex(*argv);
	if (devidx == 0)
		devidx = -1;

	devname = *argv;
	argc--;
	argv++;

	if (devidx < 0)
		return -errno;

	if (!is_link_up(devname)) {
		err = -ENOLINK;
		printf("Link for %s must be up to use acs\n", devname);
		goto nl_cleanup;
	}

	/*
	 * XXX: we should probably get channel list properly here
	 * but I'm lazy. THIS IS A REQUIREMENT, given that if a device
	 * is down and comes up we won't have any survey data to study.
	 */
	err = get_freq_list(&nlstate, devidx);
	if (err)
		return err;

	while (surveys--) {
		err = study_freqs(&nlstate, devidx);
		if (err)
			return err;
	}

	parse_freq_list();
	parse_freq_int_factor();

nl_cleanup:
	nl80211_cleanup(&nlstate);
	clear_offchan_ops_list();
	clean_freq_list();

	return err;
}