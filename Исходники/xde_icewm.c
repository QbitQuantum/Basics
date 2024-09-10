/** @brief Set the icewm style.
  *
  * When icewm changes the style, it writes the new style to the ~/.icewm/theme
  * or $ICEWM_PRIVCFG/theme file and then restarts.  The ~/.icewm/theme file
  * looks like:
  *
  *   Theme="Penguins/default.theme"
  *   #Theme="Airforce/default.theme"
  *   ##Theme="Penguins/default.theme"
  *   ###Theme="Pedestals/default.theme"
  *   ####Theme="Penguins/default.theme"
  *   #####Theme="Airforce/default.theme"
  *   ######Theme="Archlinux/default.theme"
  *   #######Theme="Airforce/default.theme"
  *   ########Theme="Airforce/default.theme"
  *   #########Theme="Airforce/default.theme"
  *   ##########Theme="Penguins/default.theme"
  *
  * icewm cannot distinguish between system an user styles.  The theme name
  * specifies a directory in the /usr/share/icewm/themes, ~/.icewm/themes or
  * $ICEWM_PRIVCFG/themes subdirectories.
  *
  * When xde-session runs, it sets the ICEWM_PRIVCFG environment variable.
  * xde-session and associated tools will always set this environment variable
  * before launching icewm.  icewm respects this environment variable and no
  * special options are necessary when launching icewm.
  *
  * The default configuration directory when ICEWM_PRIVCFG is not specified is
  * ~/.icewm.  The location of all other icewm configuration files are in this
  * directory.  xde-session typically sets ICEWM_PRIVCFG to
  * $XDG_CONFIG_HOME/icewm.
  */
static void
set_style_ICEWM()
{
	FILE *f;
	struct stat st;
	char *stylefile, *themerc, *buf, *pos, *end, *line;
	int n, len;
	size_t read, total;

	if (!(stylefile = find_style_ICEWM())) {
		EPRINTF("cannot find style '%s'\n", options.style);
		goto no_stylefile;
	}
	free(stylefile);

	len = strlen(wm->pdir) + strlen("/theme") + 1;
	themerc = calloc(len, sizeof(*themerc));
	snprintf(themerc, len, "%s/theme", wm->pdir);

	if (!(f = fopen(themerc, "r"))) {
		EPRINTF("%s: %s\n", themerc, strerror(errno));
		goto no_themerc;
	}
	if (fstat(fileno(f), &st)) {
		EPRINTF("%s: %s\n", themerc, strerror(errno));
		goto no_stat;
	}
	buf = calloc(st.st_size + 1, sizeof(*buf));
	/* read entire file into buffer */
	total = 0;
	while (total < st.st_size) {
		read = fread(buf + total, 1, st.st_size - total, f);
		total += read;
		if (total >= st.st_size)
			break;
		if (ferror(f)) {
			EPRINTF("%s: %s\n", themerc, strerror(errno));
			goto no_buf;
		}
		if (feof(f))
			break;
	}

	len = strlen(options.style) + strlen("Theme=\"\"") + 1;
	line = calloc(len, sizeof(*line));
	snprintf(line, len, "Theme=\"%s\"", options.style);
	if (strncmp(buf, line, strlen(line)) == 0) {
		OPRINTF("style %s did not change\n", line);
		goto no_change;
	}

	if (options.dryrun) {
	} else {
		OPRINTF("writing new style %s\n", options.style);
		if (!(f = freopen(themerc, "w", f))) {
			EPRINTF("%s: %s\n", themerc, strerror(errno));
			goto no_change;
		}
		fprintf(f, "Theme=\"%s\"\n", options.style);
		for (n = 0, pos = buf, end = buf + st.st_size; pos < end && n < 10;
		     n++, pos = pos + strlen(pos) + 1) {
			*strchrnul(pos, '\n') = '\0';
			fprintf(f, "#%s\n", pos);
		}
		if (options.reload)
			reload_style_ICEWM();
	}
      no_change:
	free(line);
      no_buf:
	free(buf);
      no_stat:
	fclose(f);
      no_themerc:
	free(themerc);
      no_stylefile:
	return;
}