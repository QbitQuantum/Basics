int main (int argc, char *argv[]) {
    const char *me;
    krb5_data crealm, srealm, transit;
    krb5_error_code r;
    int expand_only = 0;

    me = strrchr (argv[0], '/');
    me = me ? me+1 : argv[0];

    while (argc > 3 && argv[1][0] == '-') {
	if (!strcmp ("-v", argv[1]))
	    verbose++, argc--, argv++;
	else if (!strcmp ("-x", argv[1]))
	    expand_only++, argc--, argv++;
	else
	    goto usage;
    }

    if (argc != 4) {
    usage:
	printf ("usage: %s [-v] [-x] clientRealm serverRealm transitEncoding\n",
		me);
	return 1;
    }

    crealm.data = argv[1];
    crealm.length = strlen(argv[1]);
    srealm.data = argv[2];
    srealm.length = strlen(argv[2]);
    transit.data = argv[3];
    transit.length = strlen(argv[3]);

    if (expand_only) {

	printf ("client realm: %s\n", argv[1]);
	printf ("server realm: %s\n", argv[2]);
	printf ("transit enc.: %s\n", argv[3]);

	if (argv[3][0] == 0) {
	    printf ("no other realms transited\n");
	    return 0;
	}

	r = foreach_realm (print_a_realm, NULL, &crealm, &srealm, &transit);
	if (r)
	    printf ("--> returned error %ld\n", (long) r);
	return r != 0;

    } else {

	/* Actually check the values against the supplied krb5.conf file.  */
	krb5_context ctx;
	r = krb5_init_context (&ctx);
	if (r) {
	    com_err (me, r, "initializing krb5 context");
	    return 1;
	}
	r = krb5_check_transited_list (ctx, &transit, &crealm, &srealm);
	if (r == KRB5KRB_AP_ERR_ILL_CR_TKT) {
	    printf ("NO\n");
	} else if (r == 0) {
	    printf ("YES\n");
	} else {
	    printf ("kablooey!\n");
	    com_err (me, r, "checking transited-realm list");
	    return 1;
	}
	return 0;
    }
}