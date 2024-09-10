int
main(int argc, char *argv[])
{
	char exepath[MAX_PATH];
	char linkpath[MAX_PATH];
	HRESULT hres;
	char *install_dir;
	char *exe;
	char *linkname;

	(void) get_version_info();

	/* Pull in the parameter. */
	if (argc != 4) {
	    	fprintf(stderr, "usage: %s install-dir exe linkname\n",
			argv[0]);
		return 1;
	}
	install_dir = argv[1];
	exe = argv[2];
	linkname = argv[3];
	sprintf(exepath, "%s\\%s", install_dir, exe);

	/* Figure out the link path. */
	if (is_nt) {
	    	char *userprof;

		userprof = getenv("USERPROFILE");
		if (userprof == NULL) {
			fprintf(stderr, "Sorry, I can't figure out where your user "
				"profile is.\n");
			return 1;
		}
		sprintf(linkpath, "%s\\Desktop\\%s.lnk", userprof, linkname);
	} else {
		char *windir;

		windir = getenv("WinDir");
		if (windir == NULL) {
			printf("Sorry, I can't figure out where %%WinDir%% "
				"is.\n");
			return -1;
		}
		sprintf(linkpath, "%s\\Desktop\\%s.pif", windir, linkname);
	}

	/* Create the link. */
	if (is_nt)
		hres = CreateLink(
			exepath,
			linkpath,
			NULL,
			NULL,
			install_dir,
			44,
			80,
			L"Lucida Console",
			0,
			0);
	else
	    	hres = Piffle(
			linkname,
			exepath,
			linkpath,
			"",
			"",
			install_dir,
			44,
			80,
			"Lucida Console");

	if (hres) {
		fprintf(stderr, "Link creation failed.\n");
	}

	return hres;
}