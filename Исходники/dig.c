static void
parse_args(isc_boolean_t is_batchfile, isc_boolean_t config_only,
	   int argc, char **argv) {
	isc_result_t result;
	isc_textregion_t tr;
	isc_boolean_t firstarg = ISC_TRUE;
	dig_lookup_t *lookup = NULL;
	dns_rdatatype_t rdtype;
	dns_rdataclass_t rdclass;
	isc_boolean_t open_type_class = ISC_TRUE;
	char batchline[MXNAME];
	int bargc;
	char *bargv[64];
	int rc;
	char **rv;
#ifndef NOPOSIX
	char *homedir;
	char rcfile[256];
#endif
	char *input;
	int i;
	isc_boolean_t need_clone = ISC_TRUE;

	/*
	 * The semantics for parsing the args is a bit complex; if
	 * we don't have a host yet, make the arg apply globally,
	 * otherwise make it apply to the latest host.  This is
	 * a bit different than the previous versions, but should
	 * form a consistent user interface.
	 *
	 * First, create a "default lookup" which won't actually be used
	 * anywhere, except for cloning into new lookups
	 */

	debug("parse_args()");
	if (!is_batchfile) {
		debug("making new lookup");
		default_lookup = make_empty_lookup();
		default_lookup->adflag = ISC_TRUE;
		default_lookup->edns = 0;

#ifndef NOPOSIX
		/*
		 * Treat ${HOME}/.digrc as a special batchfile
		 */
		INSIST(batchfp == NULL);
		homedir = getenv("HOME");
		if (homedir != NULL) {
			unsigned int n;
			n = snprintf(rcfile, sizeof(rcfile), "%s/.digrc",
				     homedir);
			if (n < sizeof(rcfile))
				batchfp = fopen(rcfile, "r");
		}
		if (batchfp != NULL) {
			while (fgets(batchline, sizeof(batchline),
				     batchfp) != 0) {
				debug("config line %s", batchline);
				bargc = 1;
				input = batchline;
				bargv[bargc] = next_token(&input, " \t\r\n");
				while ((bargv[bargc] != NULL) &&
				       (bargc < 62)) {
					bargc++;
					bargv[bargc] =
						next_token(&input, " \t\r\n");
				}

				bargv[0] = argv[0];
				argv0 = argv[0];

				for(i = 0; i < bargc; i++)
					debug(".digrc argv %d: %s",
					      i, bargv[i]);
				parse_args(ISC_TRUE, ISC_TRUE, bargc,
					   (char **)bargv);
			}
			fclose(batchfp);
		}
#endif
	}

	if (is_batchfile && !config_only) {
		/* Processing '-f batchfile'. */
		lookup = clone_lookup(default_lookup, ISC_TRUE);
		need_clone = ISC_FALSE;
	} else
		lookup = default_lookup;

	rc = argc;
	rv = argv;
	for (rc--, rv++; rc > 0; rc--, rv++) {
		debug("main parsing %s", rv[0]);
		if (strncmp(rv[0], "%", 1) == 0)
			break;
		if (strncmp(rv[0], "@", 1) == 0) {
			addresscount = getaddresses(lookup, &rv[0][1], NULL);
		} else if (rv[0][0] == '+') {
			plus_option(&rv[0][1], is_batchfile,
				    lookup);
		} else if (rv[0][0] == '-') {
			if (rc <= 1) {
				if (dash_option(&rv[0][1], NULL,
						&lookup, &open_type_class,
						&need_clone, config_only,
						argc, argv, &firstarg)) {
					rc--;
					rv++;
				}
			} else {
				if (dash_option(&rv[0][1], rv[1],
						&lookup, &open_type_class,
						&need_clone, config_only,
						argc, argv, &firstarg)) {
					rc--;
					rv++;
				}
			}
		} else {
			/*
			 * Anything which isn't an option
			 */
			if (open_type_class) {
				if (strncasecmp(rv[0], "ixfr=", 5) == 0) {
					rdtype = dns_rdatatype_ixfr;
					result = ISC_R_SUCCESS;
				} else {
					tr.base = rv[0];
					tr.length = strlen(rv[0]);
					result = dns_rdatatype_fromtext(&rdtype,
						(isc_textregion_t *)&tr);
					if (result == ISC_R_SUCCESS &&
					    rdtype == dns_rdatatype_ixfr) {
						fprintf(stderr, ";; Warning, "
							"ixfr requires a "
							"serial number\n");
						continue;
					}
				}
				if (result == ISC_R_SUCCESS) {
					if (lookup->rdtypeset) {
						fprintf(stderr, ";; Warning, "
							"extra type option\n");
					}
					if (rdtype == dns_rdatatype_ixfr) {
						isc_uint32_t serial;
						lookup->rdtype =
							dns_rdatatype_ixfr;
						lookup->rdtypeset = ISC_TRUE;
						result = parse_uint(&serial,
								    &rv[0][5],
								    MAXSERIAL,
							      "serial number");
						if (result != ISC_R_SUCCESS)
							fatal("Couldn't parse "
							      "serial number");
						lookup->ixfr_serial = serial;
						lookup->section_question =
							plusquest;
						lookup->comments = pluscomm;
						lookup->tcp_mode = ISC_TRUE;
					} else {
						lookup->rdtype = rdtype;
						lookup->rdtypeset = ISC_TRUE;
						if (rdtype ==
						    dns_rdatatype_axfr) {
						    lookup->section_question =
								plusquest;
						    lookup->comments = pluscomm;
						}
						lookup->ixfr_serial = ISC_FALSE;
					}
					continue;
				}
				result = dns_rdataclass_fromtext(&rdclass,
						     (isc_textregion_t *)&tr);
				if (result == ISC_R_SUCCESS) {
					if (lookup->rdclassset) {
						fprintf(stderr, ";; Warning, "
							"extra class option\n");
					}
					lookup->rdclass = rdclass;
					lookup->rdclassset = ISC_TRUE;
					continue;
				}
			}

			if (!config_only) {
				if (need_clone)
					lookup = clone_lookup(default_lookup,
								      ISC_TRUE);
				need_clone = ISC_TRUE;
				strncpy(lookup->textname, rv[0],
					sizeof(lookup->textname));
				lookup->textname[sizeof(lookup->textname)-1]=0;
				lookup->trace_root = ISC_TF(lookup->trace  ||
						     lookup->ns_search_only);
				lookup->new_search = ISC_TRUE;
				if (firstarg) {
					printgreeting(argc, argv, lookup);
					firstarg = ISC_FALSE;
				}
				ISC_LIST_APPEND(lookup_list, lookup, link);
				debug("looking up %s", lookup->textname);
			}
			/* XXX Error message */
		}
	}

	/*
	 * If we have a batchfile, seed the lookup list with the
	 * first entry, then trust the callback in dighost_shutdown
	 * to get the rest
	 */
	if ((batchname != NULL) && !(is_batchfile)) {
		if (strcmp(batchname, "-") == 0)
			batchfp = stdin;
		else
			batchfp = fopen(batchname, "r");
		if (batchfp == NULL) {
			perror(batchname);
			if (exitcode < 8)
				exitcode = 8;
			fatal("couldn't open specified batch file");
		}
		/* XXX Remove code dup from shutdown code */
	next_line:
		if (fgets(batchline, sizeof(batchline), batchfp) != 0) {
			bargc = 1;
			debug("batch line %s", batchline);
			if (batchline[0] == '\r' || batchline[0] == '\n'
			    || batchline[0] == '#' || batchline[0] == ';')
				goto next_line;
			input = batchline;
			bargv[bargc] = next_token(&input, " \t\r\n");
			while ((bargv[bargc] != NULL) && (bargc < 14)) {
				bargc++;
				bargv[bargc] = next_token(&input, " \t\r\n");
			}

			bargv[0] = argv[0];
			argv0 = argv[0];

			for(i = 0; i < bargc; i++)
				debug("batch argv %d: %s", i, bargv[i]);
			parse_args(ISC_TRUE, ISC_FALSE, bargc, (char **)bargv);
			return;
		}
		return;
	}
	/*
	 * If no lookup specified, search for root
	 */
	if ((lookup_list.head == NULL) && !config_only) {
		if (need_clone)
			lookup = clone_lookup(default_lookup, ISC_TRUE);
		need_clone = ISC_TRUE;
		lookup->trace_root = ISC_TF(lookup->trace ||
					    lookup->ns_search_only);
		lookup->new_search = ISC_TRUE;
		strcpy(lookup->textname, ".");
		lookup->rdtype = dns_rdatatype_ns;
		lookup->rdtypeset = ISC_TRUE;
		if (firstarg) {
			printgreeting(argc, argv, lookup);
			firstarg = ISC_FALSE;
		}
		ISC_LIST_APPEND(lookup_list, lookup, link);
	}
	if (!need_clone)
		destroy_lookup(lookup);
}