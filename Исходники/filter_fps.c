static int
parse_options(char *options, int *pre, double *infps, double *outfps)
{
	char	*p, *pbase, *q, *r;
	size_t	len;
	vob_t	*vob;
	int	default_pre, i;

	/* defaults from -f and --export_fps */
	vob = tc_get_vob();
	if (!vob) return -1;
	*infps = vob->fps;
	*outfps = vob->ex_fps;
	default_pre = 1;

	if (!options || !*options) return 0;
	if (!strcmp(options, "help")) {
		tc_log_info(MOD_NAME, "(%s) help\n"
"This filter converts the video frame rate, by repeating or dropping frames.\n"
"options: <input fps>:<output fps>\n"
"example: -J fps=25:29.97 will convert from PAL to NTSC\n"
"In addition to the frame rate options, you may also specify pre or post.\n"
"If no rate options are given, defaults or -f/--export_fps/--export_frc will\n"
"be used.\n"
"If no pre or post options are given, decreasing rates will preprocess and\n"
"increasing rates will postprocess.\n"
			    , MOD_CAP);
		return -1;
	}

	len = strlen(options);
	p = pbase = malloc(len + 1);
	ac_memcpy(p, options, len);
	p[len] = '\0';

	i = 0;
	do {
		q = memchr(p, ':', len);
		if (q) *q++ = '\0';
		if (!strcmp(p, "pre")) {
			*pre = 1;
			default_pre = 0;
		} else if (!strncmp(p, "pre=", 4) && *(p + 4)) {
			*pre = strtol(p + 4, &r, 0);
			if (r == p) return -1;
			default_pre = 0;
		} else if (!strcmp(p, "post")) {
			*pre = 0;
			default_pre = 0;
		} else if (!strncmp(p, "post=", 5) && *(p + 5)) {
			*pre = !strtol(p + 4, &r, 0);
			if (r == p) return -1;
			default_pre = 0;
		} else {
			if (i == 0) {
				*infps = strtod(p, &r);
				if (r == p) return -1;
			} else if (i == 1) {
				*outfps = strtod(p, &r);
				if (r == p) return -1;
			} else return -1;
			i++;
		}
	} while (q && (p = q));

	free(pbase);

	if (default_pre) {
		if (*infps > *outfps) *pre = 1;
		else if (*infps < *outfps) *pre = 0;
	}

	return 0;
}