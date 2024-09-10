/*
 * This function invokes /usr/bin/prodreg register, using
 * pfexec in order to gain the required authorizations
 * needed to modify the registry.
 *
 * Syntax:
 *
 * prodreg register -u uuid
 *   [-b backward-compatible-version ] *
 *   [-c child-uuid '{' instance# '}' '{' version '}'] *
 *   [-d dependent-uuid '{' instance# '}' '{' version '}'] *
 *   [-D attribute '{' value '}' ] *
 *   [-n display-name '{' language-tag '}' ] *
 *   [-p location ]
 *   [-P parent-uuid '{' instance# '}' '{' version '}']
 *   [-r required-uuid '{' instance# '}' '{' version '}'] *
 *   [-R alt_root ]
 *   [-t (PRODUCT | FEATURE | COMPONENT) ] ----> default: COMPONENT
 *   [-U unique-name ]
 *   [-v prod-version ]
 *   [-V vendor-string ]
 *   [-x uninstaller-command ]
 *
 * Anything with a '*' can appear more than once in the command line.
 * Other options can only appear zero or one time.  The -u uuid option
 * *MUST* be present.
 *
 */
int
_private_prodreg_register(Wsreg_component *comp)
{

	int		i;
	char		*argv[1024];
	int		argc = 0;
	char		**tmpp;
	char		*tmp;
	Wsreg_component	**tmpc;
	char		buf[MAXPATHLEN];

	if (access(PRODREG_CLI, X_OK) != 0) {
		/* can't find prodreg */
		return (1);
	}

	/* form arguments to prodreg */
	argv[argc++] = RBAC_CLI;
	argv[argc++] = PRODREG_CLI;
	argv[argc++] = "register";
	argv[argc++] = "-u";
	argv[argc++] = wsreg_get_id(comp);

	/* backwards compatible versions */
	for (tmpp = wsreg_get_compatible_versions(comp);
		(tmpp != NULL) && (*tmpp != NULL);
		tmpp++) {
		argv[argc++] = "-b";
		argv[argc++] = *tmpp;
	}

	/* parent */
	if (wsreg_get_parent(comp) != NULL) {
		argv[argc++] = "-P";
		(void) snprintf(buf, MAXPATHLEN, "%s{%d}{%s}",
		    ESCAPE(wsreg_get_id(wsreg_get_parent(comp))),
		    wsreg_get_instance(wsreg_get_parent(comp)),
		    ESCAPE(wsreg_get_version(wsreg_get_parent(comp))));
		argv[argc++] = strdup(buf);
	}

	/* children */
	for (tmpc = wsreg_get_child_components(comp);
		(tmpc != NULL) && (*tmpc != NULL);
		tmpc++) {
		argv[argc++] = "-c";
		(void) snprintf(buf, MAXPATHLEN, "%s{%d}{%s}",
		    ESCAPE(wsreg_get_id(*tmpc)),
		    wsreg_get_instance(*tmpc),
		    ESCAPE(wsreg_get_version(*tmpc)));
		argv[argc++] = strdup(buf);
	}

	/* dependents */
	for (tmpc = wsreg_get_dependent_components(comp);
		(tmpc != NULL) && (*tmpc != NULL);
		tmpc++) {
		argv[argc++] = "-d";
		(void) snprintf(buf, MAXPATHLEN, "%s{%d}{%s}",
		    ESCAPE(wsreg_get_id(*tmpc)),
		    wsreg_get_instance(*tmpc),
		    ESCAPE(wsreg_get_version(*tmpc)));
		argv[argc++] = strdup(buf);
	}

	/* requirements */
	for (tmpc = wsreg_get_required_components(comp);
		(tmpc != NULL) && (*tmpc != NULL);
		tmpc++) {
		argv[argc++] = "-r";
		(void) snprintf(buf, MAXPATHLEN, "%s{%d}{%s}",
		    ESCAPE(wsreg_get_id(*tmpc)),
		    wsreg_get_instance(*tmpc),
		    ESCAPE(wsreg_get_version(*tmpc)));
		argv[argc++] = strdup(buf);
	}

	/* attributes */
	if ((tmpp = wsreg_get_data_pairs(comp)) != NULL) {
		while (*tmpp != NULL)  {
			argv[argc++] = "-D";
			(void) snprintf(buf, MAXPATHLEN, "%s{%s}",
			    ESCAPE(*tmpp), ESCAPE(*(tmpp + 1)));
			argv[argc++] = strdup(buf);
			tmpp += 2;
		}
	}

	/* display name */
	for (tmpp = wsreg_get_display_languages(comp);
		(tmpp != NULL) && (*tmpp != NULL);
		tmpp++) {
		argv[argc++] = "-n";
		(void) snprintf(buf, MAXPATHLEN, "%s{%s}",
		    ESCAPE(wsreg_get_display_name(comp, *tmpp)),
		    ESCAPE(*tmpp));
		argv[argc++] = strdup(buf);
	}

	/* location */
	if ((tmp = wsreg_get_location(comp)) != NULL) {
		argv[argc++] = "-p";
		argv[argc++] = tmp;
	}

	/* alt root */
	if (((tmp = wsreg_get_alternate_root()) != NULL) &&
	    (strlen(tmp) > 0)) {
		argv[argc++] = "-R";
		argv[argc++] = tmp;
	}

	/* type */
	switch (wsreg_get_type(comp)) {
	case WSREG_PRODUCT:
		argv[argc++] = "-t";
		argv[argc++] = "PRODUCT";
		break;
	case WSREG_FEATURE:
		argv[argc++] = "-t";
		argv[argc++] = "FEATURE";
		break;
	case WSREG_COMPONENT:
		/* the default is COMPONENT so we need not repeat it */
		break;
	}

	/* unique name */
	if ((tmp = wsreg_get_unique_name(comp)) != NULL) {
		argv[argc++] = "-U";
		argv[argc++] = tmp;
	}

	/* version */
	if ((tmp = wsreg_get_version(comp)) != NULL) {
		argv[argc++] = "-v";
		argv[argc++] = tmp;
	}

	/* vendor string */
	if ((tmp = wsreg_get_vendor(comp)) != NULL) {
		argv[argc++] = "-V";
		argv[argc++] = tmp;
	}

	/* uninstaller */
	if ((tmp = wsreg_get_uninstaller(comp)) != NULL) {
		argv[argc++] = "-x";
		argv[argc++] = tmp;
	}

	/* terminate argument array */
	argv[argc++] = NULL;

	/*
	 * Since we must return values following the libwsreg
	 * convention (0 indicates failure, nonzero success),
	 * we must reverse the results returned by prodreg
	 * which follows the Unix command line convention of
	 * 0 indicates success and nonzero means failure.
	 */
	i = _private_exec(argv);
	if (i == 0)
		i = 1;
	else
		i = 0;

	return (i);
}