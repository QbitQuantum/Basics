int
main(int argc, char **argv)
{
    char buf[8192];
    char *user, *group, *extension_dn = NULL;
    char *ldapServer = NULL;
    LDAP *ld = NULL;
    int tryagain = 0, rc;
    int port = LDAP_PORT;
    int use_extension_dn = 0;
    int strip_nt_domain = 0;
    int strip_kerberos_realm = 0;
    int err = 0;

    setbuf(stdout, NULL);

    while (argc > 1 && argv[1][0] == '-') {
	char *value = "";
	char option = argv[1][1];
	switch (option) {
	case 'P':
	case 'R':
	case 'z':
	case 'Z':
	case 'd':
	case 'g':
	case 'S':
	    break;
	default:
	    if (strlen(argv[1]) > 2) {
		value = argv[1] + 2;
	    } else if (argc > 2) {
		value = argv[2];
		argv++;
		argc--;
	    } else
		value = "";
	    break;
	}
	argv++;
	argc--;
	switch (option) {
	case 'H':
#if !HAS_URI_SUPPORT
	    fprintf(stderr, "ERROR: Your LDAP library does not have URI support\n");
	    exit(1);
#endif
	    /* Fall thru to -h */
	case 'h':
	    if (ldapServer) {
		int len = strlen(ldapServer) + 1 + strlen(value) + 1;
		char *newhost = malloc(len);
		snprintf(newhost, len, "%s %s", ldapServer, value);
		free(ldapServer);
		ldapServer = newhost;
	    } else {
		ldapServer = strdup(value);
	    }
	    break;
	case 'b':
	    basedn = value;
	    break;
	case 'f':
	    searchfilter = value;
	    break;
	case 'B':
	    userbasedn = value;
	    break;
	case 'F':
	    usersearchfilter = value;
	    break;
	case 'u':
	    userdnattr = value;
	    break;
	case 's':
	    if (strcmp(value, "base") == 0)
		searchscope = LDAP_SCOPE_BASE;
	    else if (strcmp(value, "one") == 0)
		searchscope = LDAP_SCOPE_ONELEVEL;
	    else if (strcmp(value, "sub") == 0)
		searchscope = LDAP_SCOPE_SUBTREE;
	    else {
		fprintf(stderr, PROGRAM_NAME " ERROR: Unknown search scope '%s'\n", value);
		exit(1);
	    }
	    break;
	case 'E':
#if defined(NETSCAPE_SSL)
	    sslpath = value;
	    if (port == LDAP_PORT)
		port = LDAPS_PORT;
#else
	    fprintf(stderr, PROGRAM_NAME " ERROR: -E unsupported with this LDAP library\n");
	    exit(1);
#endif
	    break;
	case 'c':
	    connect_timeout = atoi(value);
	    break;
	case 't':
	    timelimit = atoi(value);
	    break;
	case 'a':
	    if (strcmp(value, "never") == 0)
		aliasderef = LDAP_DEREF_NEVER;
	    else if (strcmp(value, "always") == 0)
		aliasderef = LDAP_DEREF_ALWAYS;
	    else if (strcmp(value, "search") == 0)
		aliasderef = LDAP_DEREF_SEARCHING;
	    else if (strcmp(value, "find") == 0)
		aliasderef = LDAP_DEREF_FINDING;
	    else {
		fprintf(stderr, PROGRAM_NAME " ERROR: Unknown alias dereference method '%s'\n", value);
		exit(1);
	    }
	    break;
	case 'D':
	    binddn = value;
	    break;
	case 'w':
	    bindpasswd = value;
	    break;
	case 'W':
	    readSecret(value);
	    break;
	case 'P':
	    persistent = !persistent;
	    break;
	case 'p':
	    port = atoi(value);
	    break;
	case 'R':
	    noreferrals = !noreferrals;
	    break;
#ifdef LDAP_VERSION3
	case 'v':
	    switch (atoi(value)) {
	    case 2:
		version = LDAP_VERSION2;
		break;
	    case 3:
		version = LDAP_VERSION3;
		break;
	    default:
		fprintf(stderr, "Protocol version should be 2 or 3\n");
		exit(1);
	    }
	    break;
	case 'Z':
	    if (version == LDAP_VERSION2) {
		fprintf(stderr, "TLS (-Z) is incompatible with version %d\n",
		    version);
		exit(1);
	    }
	    version = LDAP_VERSION3;
	    use_tls = 1;
	    break;
#endif
	case 'd':
	    debug = 1;
	    break;
	case 'g':
	    use_extension_dn = 1;
	    break;
	case 'S':
	    strip_nt_domain = 1;
	    break;
	case 'K':
	    strip_kerberos_realm = 1;
	    break;
	default:
	    fprintf(stderr, PROGRAM_NAME " ERROR: Unknown command line option '%c'\n", option);
	    exit(1);
	}
    }

    while (argc > 1) {
	char *value = argv[1];
	if (ldapServer) {
	    int len = strlen(ldapServer) + 1 + strlen(value) + 1;
	    char *newhost = malloc(len);
	    snprintf(newhost, len, "%s %s", ldapServer, value);
	    free(ldapServer);
	    ldapServer = newhost;
	} else {
	    ldapServer = strdup(value);
	}
	argc--;
	argv++;
    }

    if (!ldapServer)
	ldapServer = "localhost";

    if (!basedn || !searchfilter) {
	fprintf(stderr, "\n" PROGRAM_NAME " version " PROGRAM_VERSION "\n\n");
	fprintf(stderr, "Usage: " PROGRAM_NAME " -b basedn -f filter [options] ldap_server_name\n\n");
	fprintf(stderr, "\t-b basedn (REQUIRED)\tbase dn under where to search for groups\n");
	fprintf(stderr, "\t-f filter (REQUIRED)\tgroup search filter pattern. %%u = user,\n\t\t\t\t%%g = group\n");
	fprintf(stderr, "\t-B basedn (REQUIRED)\tbase dn under where to search for users\n");
	fprintf(stderr, "\t-F filter (REQUIRED)\tuser search filter pattern. %%s = login\n");
	fprintf(stderr, "\t-s base|one|sub\t\tsearch scope\n");
	fprintf(stderr, "\t-D binddn\t\tDN to bind as to perform searches\n");
	fprintf(stderr, "\t-w bindpasswd\t\tpassword for binddn\n");
	fprintf(stderr, "\t-W secretfile\t\tread password for binddn from file secretfile\n");
#if HAS_URI_SUPPORT
	fprintf(stderr, "\t-H URI\t\t\tLDAPURI (defaults to ldap://localhost)\n");
#endif
	fprintf(stderr, "\t-h server\t\tLDAP server (defaults to localhost)\n");
	fprintf(stderr, "\t-p port\t\t\tLDAP server port (defaults to %d)\n", LDAP_PORT);
	fprintf(stderr, "\t-P\t\t\tpersistent LDAP connection\n");
#if defined(NETSCAPE_SSL)
	fprintf(stderr, "\t-E sslcertpath\t\tenable LDAP over SSL\n");
#endif
	fprintf(stderr, "\t-c timeout\t\tconnect timeout\n");
	fprintf(stderr, "\t-t timelimit\t\tsearch time limit\n");
	fprintf(stderr, "\t-R\t\t\tdo not follow referrals\n");
	fprintf(stderr, "\t-a never|always|search|find\n\t\t\t\twhen to dereference aliases\n");
#ifdef LDAP_VERSION3
	fprintf(stderr, "\t-v 2|3\t\t\tLDAP version\n");
	fprintf(stderr, "\t-Z\t\t\tTLS encrypt the LDAP connection, requires\n\t\t\t\tLDAP version 3\n");
#endif
	fprintf(stderr, "\t-g\t\t\tfirst query parameter is base DN extension\n\t\t\t\tfor this query\n");
	fprintf(stderr, "\t-S\t\t\tStrip NT domain from usernames\n");
	fprintf(stderr, "\t-K\t\t\tStrip Kerberos realm from usernames\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "\tIf you need to bind as a user to perform searches then use the\n\t-D binddn -w bindpasswd or -D binddn -W secretfile options\n\n");
	exit(1);
    }
/* On Windows ldap_start_tls_s is available starting from Windows XP, 
 * so we need to bind at run-time with the function entry point
 */
#ifdef _SQUID_MSWIN_
    if (use_tls) {

	HMODULE WLDAP32Handle;

	WLDAP32Handle = GetModuleHandle("wldap32");
	if ((Win32_ldap_start_tls_s = (PFldap_start_tls_s) GetProcAddress(WLDAP32Handle, LDAP_START_TLS_S)) == NULL) {
	    fprintf(stderr, PROGRAM_NAME ": ERROR: TLS (-Z) not supported on this platform.\n");
	    exit(1);
	}
    }
#endif

    while (fgets(buf, 256, stdin) != NULL) {
	int found = 0;
	if (!strchr(buf, '\n')) {
	    /* too large message received.. skip and deny */
	    fprintf(stderr, "%s: ERROR: Too large: %s\n", argv[0], buf);
	    while (fgets(buf, sizeof(buf), stdin)) {
		fprintf(stderr, "%s: ERROR: Too large..: %s\n", argv[0], buf);
		if (strchr(buf, '\n') != NULL)
		    break;
	    }
	    goto error;
	}
	user = strtok(buf, " \n");
	if (!user) {
	    fprintf(stderr, "%s: Invalid request\n", argv[0]);
	    goto error;
	}
	rfc1738_unescape(user);
	if (strip_nt_domain) {
	    char *u = strrchr(user, '\\');
	    if (!u)
		u = strrchr(user, '/');
	    if (u && u[1])
		user = u + 1;
	}
	if (strip_kerberos_realm) {
	    char *u = strchr(user, '@');
	    if (u != NULL) {
		*u = '\0';
	    }
	}
	if (use_extension_dn) {
	    extension_dn = strtok(NULL, " \n");
	    if (!extension_dn) {
		fprintf(stderr, "%s: Invalid request\n", argv[0]);
		goto error;
	    }
	    rfc1738_unescape(extension_dn);
	}
	while (!found && user && (group = strtok(NULL, " \n")) != NULL) {
	    rfc1738_unescape(group);

	  recover:
	    if (ld == NULL) {
#if HAS_URI_SUPPORT
		if (strstr(ldapServer, "://") != NULL) {
		    rc = ldap_initialize(&ld, ldapServer);
		    if (rc != LDAP_SUCCESS) {
			fprintf(stderr, "\nUnable to connect to LDAPURI:%s\n", ldapServer);
			break;
		    }
		} else
#endif
#if NETSCAPE_SSL
		if (sslpath) {
		    if (!sslinit && (ldapssl_client_init(sslpath, NULL) != LDAP_SUCCESS)) {
			fprintf(stderr, "\nUnable to initialise SSL with cert path %s\n",
			    sslpath);
			exit(1);
		    } else {
			sslinit++;
		    }
		    if ((ld = ldapssl_init(ldapServer, port, 1)) == NULL) {
			fprintf(stderr, "\nUnable to connect to SSL LDAP server: %s port:%d\n",
			    ldapServer, port);
			exit(1);
		    }
		} else
#endif
		if ((ld = ldap_init(ldapServer, port)) == NULL) {
		    fprintf(stderr, "\nUnable to connect to LDAP server:%s port:%d\n", ldapServer, port);
		    break;
		}
		if (connect_timeout)
		    squid_ldap_set_connect_timeout(ld, connect_timeout);

#ifdef LDAP_VERSION3
		if (version == -1) {
		    version = LDAP_VERSION2;
		}
		if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version) != LDAP_SUCCESS) {
		    fprintf(stderr, "Could not set LDAP_OPT_PROTOCOL_VERSION %d\n",
			version);
		    ldap_unbind(ld);
		    ld = NULL;
		    break;
		}
		if (use_tls) {
#ifdef LDAP_OPT_X_TLS
		    if (version != LDAP_VERSION3) {
			fprintf(stderr, "TLS requires LDAP version 3\n");
			exit(1);
		    } else if (ldap_start_tls_s(ld, NULL, NULL) != LDAP_SUCCESS) {
			fprintf(stderr, "Could not Activate TLS connection\n");
			ldap_unbind(ld);
			ld = NULL;
			break;
		    }
#else
		    fprintf(stderr, "TLS not supported with your LDAP library\n");
		    exit(1);
#endif
		}
#endif
		squid_ldap_set_timelimit(ld, timelimit);
		squid_ldap_set_referrals(ld, !noreferrals);
		squid_ldap_set_aliasderef(ld, aliasderef);
		if (binddn && bindpasswd && *binddn && *bindpasswd) {
		    rc = ldap_simple_bind_s(ld, binddn, bindpasswd);
		    if (rc != LDAP_SUCCESS) {
			fprintf(stderr, PROGRAM_NAME " WARNING, could not bind to binddn '%s'\n", ldap_err2string(rc));
			ldap_unbind(ld);
			ld = NULL;
			break;
		    }
		}
		if (debug)
		    fprintf(stderr, "Connected OK\n");
	    }
	    if (searchLDAP(ld, group, user, extension_dn) == 0) {
		found = 1;
		break;
	    } else {
		if (tryagain) {
		    tryagain = 0;
		    ldap_unbind(ld);
		    ld = NULL;
		    goto recover;
		}
	    }
	}
	if (found)
	    printf("OK\n");
	else {
	  error:
	    printf("ERR\n");
	}

	if (ld != NULL) {
	    if (!persistent || (squid_ldap_errno(ld) != LDAP_SUCCESS && squid_ldap_errno(ld) != LDAP_INVALID_CREDENTIALS)) {
		ldap_unbind(ld);
		ld = NULL;
	    } else {
		tryagain = 1;
	    }
	}
	err = 0;
    }
    if (ld)
	ldap_unbind(ld);
    return 0;
}