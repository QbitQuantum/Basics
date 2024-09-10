int
main(int argc, char *argv[])
{
	int		c;

	/* set the locale for only the messages system (all else is clean) */

	(void) setlocale(LC_ALL, "");
#if !defined(TEXT_DOMAIN)		/* Should be defined by cc -D */
#define	TEXT_DOMAIN	"SYS_TEST"	/* Use this only if it weren't */
#endif
	(void) textdomain(TEXT_DOMAIN);

	while ((c = getopt(argc, argv, "RhfHLPs")) != EOF)
		switch (c) {
			case 'R':
				rflag++;
				break;
			case 'h':
				hflag++;
				break;
			case 'f':
				fflag++;
				break;
			case 'H':
				/*
				 * If more than one of -H, -L, and -P
				 * are specified, only the last option
				 * specified determines the behavior of
				 * chgrp.  In addition, make [-H|-L]
				 * mutually exclusive of -h.
				 */
				Lflag = Pflag = 0;
				Hflag++;
				break;
			case 'L':
				Hflag = Pflag = 0;
				Lflag++;
				break;
			case 'P':
				Hflag = Lflag = 0;
				Pflag++;
				break;
			case 's':
				sflag++;
				break;
			default:
				usage();
		}
	/*
	 * Set Pflag by default for recursive operations
	 * if no other options were specified.
	 */
	if (rflag && !(Lflag || Hflag || Pflag || hflag)) {
		Pflag = 1;
	}

	/*
	 * Check for sufficient arguments
	 * or a usage error.
	 */
	argc -= optind;
	argv = &argv[optind];

	if ((argc < 2) ||
	    ((Hflag || Lflag || Pflag) && !rflag) ||
	    ((Hflag || Lflag || Pflag) && hflag)) {
		usage();
	}

	if (sflag) {
		if (sid_to_id(argv[0], B_FALSE, &gid)) {
			(void) fprintf(stderr, gettext(
			    "chgrp: invalid group sid %s\n"), argv[0]);
			exit(2);
		}
	} else if ((gr = getgrnam(argv[0])) != NULL) {
		gid = gr->gr_gid;
	} else {
		if (isnumber(argv[0])) {
			errno = 0;
			/* gid is an int */
			gid = (gid_t)strtoul(argv[0], NULL, 10);
			if (errno != 0) {
				if (errno == ERANGE) {
					(void) fprintf(stderr, gettext(
					"chgrp: group id is too large\n"));
					exit(2);
				} else {
					(void) fprintf(stderr, gettext(
					"chgrp: invalid group id\n"));
					exit(2);
				}
			}
		} else {
			(void) fprintf(stderr, "chgrp: ");
			(void) fprintf(stderr, gettext("unknown group: %s\n"),
			    argv[0]);
			exit(2);
		}
	}

	for (c = 1; c < argc; c++) {
		tree = NULL;
		if (lstat(argv[c], &stbuf) < 0) {
			status += Perror(argv[c]);
			continue;
		}
		if (rflag && ((stbuf.st_mode & S_IFMT) == S_IFLNK)) {
			if (hflag || Pflag) {
				/*
				 * Change the group id of the symbolic link
				 * specified on the command line.
				 * Don't follow the symbolic link to
				 * any other part of the file hierarchy.
				 */
				LCHOWN(argv[c], -1, gid);
			} else {
				if (stat(argv[c], &stbuf2) < 0) {
					status += Perror(argv[c]);
					continue;
				}
				/*
				 * We know that we are to change the
				 * group of the file referenced by the
				 * symlink specified on the command line.
				 * Now check to see if we are to follow
				 * the symlink to any other part of the
				 * file hierarchy.
				 */
				if (FOLLOW_CL_LINKS) {
					if ((stbuf2.st_mode & S_IFMT)
					    == S_IFDIR) {
						/*
						 * We are following symlinks so
						 * traverse into the directory.
						 * Add this node to the search
						 * tree so we don't get into an
						 * endless loop.
						 */
						if (add_tnode(&tree,
						    stbuf2.st_dev,
						    stbuf2.st_ino) == 1) {
							chgrpr(argv[c], gid);
							/*
							 * Try to restore the
							 * SET[UG]ID bits.
							 */
							SETUGID_PRESERVE(
							    argv[c],
							    stbuf2.st_mode &
							    ~S_IFMT);
						} else {
							/*
							 * Error occurred.
							 * rc can't be 0
							 * as this is the first
							 * node to be added to
							 * the search tree.
							 */
							status += Perror(
							    argv[c]);
						}
					} else {
						/*
						 * Change the group id of the
						 * file referenced by the
						 * symbolic link.
						 */
						CHOWN(argv[c], -1, gid);
					}
				} else {
					/*
					 * Change the group id of the file
					 * referenced by the symbolic link.
					 */
					CHOWN(argv[c], -1, gid);

					if ((stbuf2.st_mode & S_IFMT)
					    == S_IFDIR) {
						/* Reset the SET[UG]ID bits. */
						SETUGID_PRESERVE(argv[c],
						    stbuf2.st_mode & ~S_IFMT);
					}
				}
			}
		} else if (rflag && ((stbuf.st_mode & S_IFMT) == S_IFDIR)) {
			/*
			 * Add this node to the search tree so we don't
			 * get into a endless loop.
			 */
			if (add_tnode(&tree, stbuf.st_dev,
			    stbuf.st_ino) == 1) {
				chgrpr(argv[c], gid);

				/* Restore the SET[UG]ID bits. */
				SETUGID_PRESERVE(argv[c],
				    stbuf.st_mode & ~S_IFMT);
			} else {
				/*
				 * An error occurred while trying
				 * to add the node to the tree.
				 * Continue on with next file
				 * specified.  Note: rc shouldn't
				 * be 0 as this was the first node
				 * being added to the search tree.
				 */
				status += Perror(argv[c]);
			}
		} else {
			if (hflag || Pflag) {
				LCHOWN(argv[c], -1, gid);
			} else {
				CHOWN(argv[c], -1, gid);
			}
			/* If a directory, reset the SET[UG]ID bits. */
			if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
				SETUGID_PRESERVE(argv[c],
				    stbuf.st_mode & ~S_IFMT);
			}
		}
	}
	return (status);
}