/* routine via which the dot file is written */
void write_dot(const char * prefix, const char * figpath,
	       int id, const char *fmt, ...)
{
	static int flag = 0;
	static FILE * dotf[MAX_DOTF_NR];
	static char dotfilename[MAX_DOTF_NR][FILENAME_MAX];
	char cmd[CMD_MAX];

	va_list args;
	va_start(args, fmt);

	assert(id >= 0 && id < MAX_DOTF_NR);
	if (id < LOWEST_DOT_ID)
		return;

	if (!flag) {
		int i;
		for (i = 0; i < MAX_DOTF_NR; i++)
			dotf[i] = 0;
		flag = 1;
	}
	if (!dotf[id]) {
		sprintf(dotfilename[id], "%s%s%s (%03d).%s",
			figpath,
			figpath[strlen(figpath) - 1] == '/' ? "" : "/",
			prefix, id, GRAPHVIZ_FILE_EXT);

		mkdir_if_needed(dotfilename[id], 0);

		fprintf(stderr, "%sdot file: %s%s\n", INFO_COLOR,
			dotfilename[id], NOCOLOR);

		dotf[id] = fopen(dotfilename[id], "w");
		assert(dotf[id] != 0);

		fprintf(dotf[id], "digraph G {\n");

		fprintf(dotf[id],
			"\tsize=\"9,9\";"
			"\n");

		fprintf(dotf[id],
			"\tnode [shape=record"
			", fontname=Courier New"
			", penwidth=0.5"
			/* ", fixedsize=true" */
			/* ", width=0.6" */
			/* ", height=0.7" */
			", splines=\"compound\""
			"];\n");
	}

	assert(dotf[id] != 0);

	/* if the dot file becomes big, something must be wrong */
	int dot_f_max_size = 32*1024;
	if (ftell(dotf[id]) > dot_f_max_size) {
		fprintf(stderr,
			"%sdot file too big: %s"
			"%s%s%s"
			"%s, something must be wrong.\n%s",
			YELLOW, NOCOLOR,
			RED, dotfilename[id], NOCOLOR,
			YELLOW, NOCOLOR);
		assert(ftell(dotf[id]) <= dot_f_max_size);
	}

	if (!fmt[0]) {
		fprintf(dotf[id], "}\n");
		fclose(dotf[id]);
		dotf[id] = 0;
		snprintf(cmd, (size_t)CMD_MAX, "%s -T%s \"%s\" -o "
			 "\"%s%s%s (%03d).%s\"",
			 GRAPHVIZ_CMD, GRAPHVIZ_FIG_TYPE, dotfilename[id],
			 figpath,
			 figpath[strlen(figpath) - 1] == '/' ? "" : "/",
			 prefix, id, GRAPHVIZ_FIG_TYPE);
		printf("%s$ %s%s%s\n", WHITE, WHITE, cmd, NOCOLOR);
		/* printf("%s$ %s%s%s\n", WHITE, GREEN, cmd, NOCOLOR); */
		assert(system(cmd) == 0);
	} else {
		fprintf(dotf[id], "\t");
		vfprintf(dotf[id], fmt, args);
	}

	va_end(args);
}