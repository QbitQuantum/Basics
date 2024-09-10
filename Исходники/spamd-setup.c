int
main(int argc, char *argv[])
{
	size_t blc, bls, black, white;
	char *db_array[2], *buf, *name;
	struct blacklist *blists;
	struct servent *ent;
	int daemonize = 0, ch;

	while ((ch = getopt(argc, argv, "bdDn")) != -1) {
		switch (ch) {
		case 'n':
			dryrun = 1;
			break;
		case 'd':
			debug = 1;
			break;
		case 'b':
			greyonly = 0;
			break;
		case 'D':
			daemonize = 1;
			break;
		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc != 0)
		usage();

	if (daemonize)
		daemon(0, 0);

	if ((ent = getservbyname("spamd-cfg", "tcp")) == NULL)
		errx(1, "cannot find service \"spamd-cfg\" in /etc/services");
	ent->s_port = ntohs(ent->s_port);

	db_array[0] = PATH_SPAMD_CONF;
	db_array[1] = NULL;

	if (cgetent(&buf, db_array, "all") != 0)
		err(1, "Can't find \"all\" in spamd config");
	name = strsep(&buf, ": \t"); /* skip "all" at start */
	blists = NULL;
	blc = bls = 0;
	while ((name = strsep(&buf, ": \t")) != NULL) {
		if (*name) {
			/* extract config in order specified in "all" tag */
			if (blc == bls) {
				struct blacklist *tmp;

				bls += 32;
				tmp = realloc(blists,
				    bls * sizeof(struct blacklist));
				if (tmp == NULL)
					errx(1, "malloc failed");
				blists = tmp;
			}
			if (blc == 0)
				black = white = 0;
			else {
				white = blc - 1;
				black = blc;
			}
			memset(&blists[black], 0, sizeof(struct blacklist));
			black = getlist(db_array, name, &blists[white],
			    &blists[black]);
			if (black && blc > 0) {
				/* collapse and free previous blacklist */
				send_blacklist(&blists[blc - 1], ent->s_port);
			}
			blc += black;
		}
	}
	/* collapse and free last blacklist */
	if (blc > 0)
		send_blacklist(&blists[blc - 1], ent->s_port);
	return (0);
}