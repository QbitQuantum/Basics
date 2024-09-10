static void
make_dist(const char *homedir, const char *pkg, const char *suff, Package *plist)
{
    struct stat sb;
    char tball[FILENAME_MAX];
    PackingList p;
    int ret;
    const char *args[50];	/* Much more than enough. */
    int nargs = 0;
    int pipefds[2];
    FILE *totar;
    pid_t pid;
    const char *cname;
    char *prefix = NULL;


    args[nargs++] = "tar";	/* argv[0] */

    if (*pkg == '/')
	snprintf(tball, FILENAME_MAX, "%s.%s", pkg, suff);
    else
	snprintf(tball, FILENAME_MAX, "%s/%s.%s", homedir, pkg, suff);

    /*
     * If the package tarball exists already, and we are running in `no
     * clobber' mode, skip this package.
     */
    if (stat(tball, &sb) == 0 && Regenerate == FALSE) {
	if (Verbose)
	    printf("Skipping package '%s'.  It already exists.\n", tball);
	return;
    }

    args[nargs++] = "-c";
    args[nargs++] = "-f";
    args[nargs++] = tball;
    if (strchr(suff, 'z')) {	/* Compress/gzip/bzip2? */
	if (Zipper == BZIP2) {
	    args[nargs++] = "-j";
	    cname = "bzip'd ";
	}
	else if (Zipper == XZ) {
	    args[nargs++] = "-J";
	    cname = "xz'd ";
	}
	else {
	    args[nargs++] = "-z";
	    cname = "gzip'd ";
	}
    } else {
	cname = "";
    }
    if (Dereference)
	args[nargs++] = "-h";
    if (ExcludeFrom) {
	args[nargs++] = "-X";
	args[nargs++] = ExcludeFrom;
    }
    args[nargs++] = "-T";	/* Take filenames from file instead of args. */
    args[nargs++] = "-";	/* Use stdin for the file. */
    args[nargs] = NULL;

    if (Verbose)
	printf("Creating %star ball in '%s'\n", cname, tball);

    /* Set up a pipe for passing the filenames, and fork off a tar process. */
    if (pipe(pipefds) == -1) {
	cleanup(0);
	errx(2, "%s: cannot create pipe", __func__);
    }
    if ((pid = fork()) == -1) {
	cleanup(0);
	errx(2, "%s: cannot fork process for tar", __func__);
    }
    if (pid == 0) {	/* The child */
	dup2(pipefds[0], 0);
	close(pipefds[0]);
	close(pipefds[1]);
	execv("/usr/bin/tar", (char * const *)(uintptr_t)args);
	cleanup(0);
	errx(2, "%s: failed to execute tar command", __func__);
    }

    /* Meanwhile, back in the parent process ... */
    close(pipefds[0]);
    if ((totar = fdopen(pipefds[1], "w")) == NULL) {
	cleanup(0);
	errx(2, "%s: fdopen failed", __func__);
    }

    fprintf(totar, "%s\n", CONTENTS_FNAME);
    fprintf(totar, "%s\n", COMMENT_FNAME);
    fprintf(totar, "%s\n", DESC_FNAME);

    if (Install)
	fprintf(totar, "%s\n", INSTALL_FNAME);
    if (PostInstall)
	fprintf(totar, "%s\n", POST_INSTALL_FNAME);
    if (DeInstall)
	fprintf(totar, "%s\n", DEINSTALL_FNAME);
    if (PostDeInstall)
	fprintf(totar, "%s\n", POST_DEINSTALL_FNAME);
    if (Require)
	fprintf(totar, "%s\n", REQUIRE_FNAME);
    if (Display)
	fprintf(totar, "%s\n", DISPLAY_FNAME);
    if (Mtree)
	fprintf(totar, "%s\n", MTREE_FNAME);

    for (p = plist->head; p; p = p->next) {
	if (p->type == PLIST_FILE)
	    fprintf(totar, "%s\n", p->name);
	else if (p->type == PLIST_CWD && p->name == NULL)
	    fprintf(totar, "-C\n%s\n", prefix);
	else if (p->type == PLIST_CWD && BaseDir && p->name && p->name[0] == '/')
	    fprintf(totar, "-C\n%s%s\n", BaseDir, p->name);
	else if (p->type == PLIST_CWD || p->type == PLIST_SRC)
	    fprintf(totar, "-C\n%s\n", p->name);
	else if (p->type == PLIST_IGNORE)
	     p = p->next;
	if (p->type == PLIST_CWD && !prefix)
	    prefix = p->name;

    }

    fclose(totar);
    wait(&ret);
    /* assume either signal or bad exit is enough for us */
    if (ret) {
	cleanup(0);
	errx(2, "%s: tar command failed with code %d", __func__, ret);
    }
}