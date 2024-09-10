void
init_vocoders()
{
	char fname[1024];
	DIR *dirp;
	struct dirent *dp;
	int i = 0;
	struct stat st;
	int cnt = 0;

	for (i = 0; i < MAXCODECS; i++) {
		vocoders[i].f = vocoder_default;
		vocoders[i].rate = 0;
	}
	if ((dirp = opendir(gmodpath)) == NULL) {
		misc_debug(0, "init_vocoders: cannot open modules dir %s: %s\n", gmodpath, strerror(errno));
		return;
	}
	while((dp = readdir(dirp)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || (memcmp(dp->d_name, "mod", 3) != 0))
			continue;
		snprintf(fname, sizeof(fname) - 2, "%s/%s", gmodpath, dp->d_name);
		stat(fname, &st);
		if (S_ISREG(st.st_mode)) 
			if (securemod(&st, fname))
				if (loadmodule(fname) == 0)
					cnt++;
	}
	misc_debug(0, "loaded %d module(s)\n", cnt);
}