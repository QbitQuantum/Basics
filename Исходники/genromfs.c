int main(int argc, char *argv[])
{
	int c;
	char *dir = ".";
	char *outf = NULL;
	char *volname = NULL;
	int verbose=0;
	char buf[256];
	struct filenode *root;
	struct stat sb;
	int lastoff;
	int i;
	char *p;
	struct aligns *pa, *pa2;
	struct excludes *pe, *pe2;
	FILE *f;

	while ((c = getopt(argc, argv, "V:vd:f:ha:A:x:")) != EOF) {
		switch(c) {
		case 'd':
			dir = optarg;
			break;
		case 'f':
			outf = optarg;
			break;
		case 'V':
			volname = optarg;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'h':
			showhelp(argv[0]);
			exit(0);
		case 'a':
			align = strtoul(optarg, NULL, 0);
			if (align < 16 || (align & (align - 1))) {
				fprintf(stderr, "Align has to be at least 16 bytes and a power of two\n");
				exit(1);
			}
			break;
		case 'A':
			i = strtoul(optarg, &p, 0);
			if (i < 16 || (i & (i - 1))) {
				fprintf(stderr, "Align has to be at least 16 bytes and a power of two\n");
				exit(1);
			}
			if (*p != ',' || !p[1]) {
				fprintf(stderr, "-A takes N,PATTERN format of argument, where N is a number\n");
				exit(1);
			}
			/* strlen(p+1) + 1 eq strlen(p) */
			pa = (struct aligns *)malloc(sizeof(*pa) + strlen(p));
			pa->align = i;
			pa->next = NULL;
			strcpy(pa->pattern, p + 1);
			if (!alignlist)
				alignlist = pa;
			else {
				for (pa2 = alignlist; pa2->next; pa2 = pa2->next)
					;
				pa2->next = pa;
			}
			break;
		case 'x':
			pe = (struct excludes *)malloc(sizeof(*pe) + strlen(optarg) + 1);
			pe->next = NULL;
			strcpy(pe->pattern, optarg);
			if (!excludelist)
				excludelist = pe;
			else {
				for (pe2 = excludelist; pe2->next; pe2 = pe2->next)
					;
				pe2->next = pe;
			}
			break;
		default:
			exit(1);
		}
	}

	if (!volname) {
		sprintf(buf, "rom %08lx", time(NULL));
		volname = buf;
	}
	if (!outf) {
		fprintf(stderr, "%s: you must specify the destination file\n", argv[0]);
		fprintf(stderr, "Try `%s -h' for more information\n",argv[0]);
		exit(1);
	}
	if (strcmp(outf, "-") == 0) {
		f = fdopen(1,"wb");
	} else
		f = fopen(outf, "wb");

	if (!f) {
		perror(outf);
		exit(1);
	}
	
	realbase = strlen(dir);
	root = newnode(dir, volname, 0);
	root->parent = root;
	lastoff = processdir (1, dir, dir, &sb, root, root, spaceneeded(root));
	if (verbose)
		shownode(0, root, stderr);
	dumpall(root, lastoff, f);

	exit(0);
}