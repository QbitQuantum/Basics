int
main(int argc, char *argv[])
{
    int authenticated = 0;
    int retcode;
    char *username;
    int setcred = 1;

    if (argc < 2 || argc > 3) {
	fprintf(stderr, "Usage: %s [-u] <user>\n", argv[0]);
	exit(1);
    }
    if (argc == 3) {
	if (strcmp(argv[1], "-u") != 0) {
	    fprintf(stderr, "Usage: %s [-u] <user>\n", argv[0]);
	    exit(1);
	}
	/* service = "unixtest"; */
	setcred = 0;
	username = argv[2];
    } else {
	username = argv[1];
    }

    if ((retcode =
	 pam_start(service, username, &pam_conv, &pamh)) != PAM_SUCCESS) {
	fprintf(stderr, "PAM error %d\n", retcode);
	exit(1);
    }

    authenticated = ((retcode = pam_authenticate(pamh, 0)) == PAM_SUCCESS);

    if (!authenticated) {
	fprintf(stderr, "PAM couldn't authenticate you.\n");
	pam_end(pamh, PAM_ABORT);
	exit(1);
    }

    if ((retcode = pam_acct_mgmt(pamh, 0)) != PAM_SUCCESS) {
	fprintf(stderr, "pam_acct_mgmt returned %d.\n", retcode);
	pam_end(pamh, PAM_ABORT);
	exit(1);
    }

    /* pam_open_session */

    if (setcred)
	if ((retcode = pam_setcred(pamh, PAM_ESTABLISH_CRED)) != PAM_SUCCESS) {
	    fprintf(stderr, "pam_setcred returned %d.\n", retcode);
	    pam_end(pamh, PAM_ABORT);
	    exit(1);
	}

    if ((retcode = pam_open_session(pamh, PAM_SILENT)) != PAM_SUCCESS) {
	fprintf(stderr, "pam_open_session returned %d.\n", retcode);
	pam_end(pamh, PAM_ABORT);
	exit(1);
    }
    pam_end(pamh, PAM_SUCCESS);

    putenv((char *)new_envstring);
    putenv((char *)new_homestring);

    if ((retcode = chdir("/tmp")) != 0) {
	fprintf(stderr, "chdir returned %d.\n", retcode);
	exit(1);
    }

    printf("Type exit to back out.\n");
    return execl("/bin/csh", "/bin/csh", NULL);
}