afs_int32
uss_kauth_SetFields(char *username, char *expirestring, char *reuse,
		    char *failures, char *lockout)
{
#ifdef USS_KAUTH_DB
    static char rn[] = "uss_kauth_SetFields";
#endif
    afs_int32 code;
    char misc_auth_bytes[4];
    int i;
    afs_int32 flags = 0;
    Date expiration = 0;
    afs_int32 lifetime = 0;
    afs_int32 maxAssociates = -1;
    afs_int32 was_spare = 0;
    char instance = '\0';
    int pwexpiry;
    int nfailures, locktime, hrs, mins;

    if (strlen(username) > uss_UserLen) {
	fprintf(stderr,
		"%s: * User field in add cmd too long (max is %d chars; truncated value is '%s')\n",
		uss_whoami, uss_UserLen, uss_User);
	return (-1);
    }

    strcpy(uss_User, username);
    code = uss_kauth_CheckUserName();
    if (code)
	return (code);

    /*  no point in doing this any sooner than necessary */
    for (i = 0; i < 4; misc_auth_bytes[i++] = 0);

    pwexpiry = atoi(expirestring);
    if (pwexpiry < 0 || pwexpiry > 254) {
	fprintf(stderr, "Password lifetime range must be [0..254] days.\n");
	fprintf(stderr, "Zero represents an unlimited lifetime.\n");
	fprintf(stderr,
		"Continuing with default lifetime == 0 for user %s.\n",
		username);
	pwexpiry = 0;
    }
    misc_auth_bytes[0] = pwexpiry + 1;

    if (!strcmp(reuse, "noreuse")) {
	misc_auth_bytes[1] = KA_NOREUSEPW;
    } else {
	misc_auth_bytes[1] = KA_REUSEPW;
	if (strcmp(reuse, "reuse"))
	  fprintf(stderr, "must specify \"reuse\" or \"noreuse\": \"reuse\" assumed\n");
    }

    nfailures = atoi(failures);
    if (nfailures < 0 || nfailures > 254) {
	fprintf(stderr, "Failure limit must be in [0..254].\n");
	fprintf(stderr, "Zero represents unlimited login attempts.\n");
	fprintf(stderr, "Continuing with limit == 254 for user %s.\n",
		username);
	misc_auth_bytes[2] = 255;
    } else
	misc_auth_bytes[2] = nfailures + 1;

    hrs = 0;
    if (strchr(lockout, ':'))
	sscanf(lockout, "%d:%d", &hrs, &mins);
    else
	sscanf(lockout, "%d", &mins);

    locktime = hrs*60 + mins;
    if (hrs < 0 || hrs > 36 || mins < 0) {
	fprintf(stderr,"Lockout times must be either minutes or hh:mm.\n");
	fprintf(stderr,"Lockout times must be less than 36 hours.\n");
	return KABADCMD;
    } else if (locktime > 36*60) {
	fprintf(stderr, "Lockout times must be either minutes or hh:mm.\n");
	fprintf(stderr, "Lockout times must be less than 36 hours.\n");
	fprintf(stderr, "Continuing with lock time == forever for user %s.\n",
		username);
	misc_auth_bytes[3] = 1;
    } else {
	locktime = (locktime * 60 + 511) >> 9;  /* ceil(l*60/512) */
	misc_auth_bytes[3] = locktime + 1;
    }

    if (uss_SkipKaserver) {
	if (uss_verbose)
	    printf("[Skipping Kaserver as requested]\n");
	return 0;
    }

    /*
     * Make sure the module has been initialized before we start trying
     * to talk to AuthServers.
     */
    if (!initDone) {
	code = InitThisModule();
	if (code)
	    exit(code);
    }

    if (!uss_DryRun) {
	if (uss_verbose)
	    fprintf(stderr, "Setting options for '%s' in database.\n",
		    username);

	was_spare = pack_long(misc_auth_bytes);

	if (was_spare || flags || expiration || lifetime
	    || (maxAssociates >= 0)) {

	    if (!expiration)
		expiration = uss_Expires;
	    code =
		ubik_KAM_SetFields(uconn_kauthP, 0, username, &instance,
			  flags, expiration, lifetime, maxAssociates,
			  was_spare, /* spare */ 0);
	} else
	    fprintf(stderr,
		    "Must specify one of the optional parameters. Continuing...\n");

	if (code) {
	    afs_com_err(uss_whoami, code, "calling KAM_SetFields for %s",
		    username);

	    return (code);
	}
    } /*Not a dry run */
    else
	fprintf(stderr, "\t[Dry run - user '%s' NOT changed.]\n", username);

    return (0);

}				/*uss_kauth_SetFields */