/*
 * Initialize a symbol table from a file
 */
void
initsymtable(char *filename)
{
	char *base;
	long tblsize;
	struct entry *ep;
	struct entry *baseep, *lep;
	struct symtableheader hdr;
	struct stat stbuf;
	long i;
	int fd;

	Vprintf(stdout, "Initialize symbol table.\n");
	if (filename == NULL) {
		entrytblsize = maxino / HASHFACTOR;
		entry = calloc(entrytblsize, sizeof(struct entry *));
		if (entry == NULL)
			panic("no memory for entry table\n");
		ep = addentry(".", ROOTINO, NODE);
		ep->e_flags |= NEW;
		return;
	}
	if ((fd = open(filename, O_RDONLY, 0)) < 0) {
		warn("open");
		panic("cannot open symbol table file %s\n", filename);
	}
	if (fstat(fd, &stbuf) < 0) {
		warn("stat");
		panic("cannot stat symbol table file %s\n", filename);
	}
	tblsize = stbuf.st_size - sizeof(struct symtableheader);
	base = calloc(tblsize, sizeof(char));
	if (base == NULL)
		panic("cannot allocate space for symbol table\n");
	if (read(fd, base, tblsize) < 0 ||
	    read(fd, &hdr, sizeof(struct symtableheader)) < 0) {
		warn("read");
		panic("cannot read symbol table file %s\n", filename);
	}
	switch (command) {
	case 'r':
		/*
		 * For normal continuation, insure that we are using
		 * the next incremental tape
		 */
		if (hdr.dumpdate != dumptime)
			errx(1, "Incremental tape too %s",
			    (hdr.dumpdate < dumptime) ? "low" : "high");
		break;
	case 'R':
		/*
		 * For restart, insure that we are using the same tape
		 */
		curfile.action = SKIP;
		dumptime = hdr.dumptime;
		dumpdate = hdr.dumpdate;
		if (!bflag)
			newtapebuf(hdr.ntrec);
		getvol(hdr.volno);
		break;
	default:
		panic("initsymtable called from command %c\n", command);
		break;
	}
	maxino = hdr.maxino;
	entrytblsize = hdr.entrytblsize;
	entry = (struct entry **)
		(base + tblsize - (entrytblsize * sizeof(struct entry *)));
	baseep = (struct entry *)(base + hdr.stringsize - sizeof(struct entry));
	lep = (struct entry *)entry;
	for (i = 0; i < entrytblsize; i++) {
		if (entry[i] == NULL)
			continue;
		entry[i] = &baseep[(long)entry[i]];
	}
	for (ep = &baseep[1]; ep < lep; ep++) {
		ep->e_name = base + (long)ep->e_name;
		ep->e_parent = &baseep[(long)ep->e_parent];
		if (ep->e_sibling != NULL)
			ep->e_sibling = &baseep[(long)ep->e_sibling];
		if (ep->e_links != NULL)
			ep->e_links = &baseep[(long)ep->e_links];
		if (ep->e_entries != NULL)
			ep->e_entries = &baseep[(long)ep->e_entries];
		if (ep->e_next != NULL)
			ep->e_next = &baseep[(long)ep->e_next];
	}
}