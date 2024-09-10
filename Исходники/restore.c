/*
 * This is the routine used to extract files for the 'r' command.
 * Extract new leaves.
 */
void
createleaves(char *symtabfile)
{
	struct entry *ep;
	ino_t first;
	long curvol;

	if (command == 'R') {
		Vprintf(stdout, "Continue extraction of new leaves\n");
	} else {
		Vprintf(stdout, "Extract new leaves.\n");
		dumpsymtable(symtabfile, volno);
	}
	first = lowerbnd(ROOTINO);
	curvol = volno;
	while (curfile.ino < maxino) {
		first = lowerbnd(first);
		/*
		 * If the next available file is not the one which we
		 * expect then we have missed one or more files. Since
		 * we do not request files that were not on the tape,
		 * the lost files must have been due to a tape read error,
		 * or a file that was removed while the dump was in progress.
		 */
		while (first < curfile.ino) {
			ep = lookupino(first);
			if (ep == NULL)
				panic("%d: bad first\n", first);
			fprintf(stderr, "%s: not found on tape\n", myname(ep));
			ep->e_flags &= ~(NEW|EXTRACT);
			first = lowerbnd(first);
		}
		/*
		 * If we find files on the tape that have no corresponding
		 * directory entries, then we must have found a file that
		 * was created while the dump was in progress. Since we have
		 * no name for it, we discard it knowing that it will be
		 * on the next incremental tape.
		 */
		if (first != curfile.ino) {
			fprintf(stderr, "expected next file %d, got %d\n",
				first, curfile.ino);
			skipfile();
			goto next;
		}
		ep = lookupino(curfile.ino);
		if (ep == NULL)
			panic("unknown file on tape\n");
		if ((ep->e_flags & (NEW|EXTRACT)) == 0)
			badentry(ep, "unexpected file on tape");
		/*
		 * If the file is to be extracted, then the old file must
		 * be removed since its type may change from one leaf type
		 * to another (eg "file" to "character special").
		 */
		if ((ep->e_flags & EXTRACT) != 0) {
			removeleaf(ep);
			ep->e_flags &= ~REMOVED;
		}
		(void)extractfile(myname(ep));
		ep->e_flags &= ~(NEW|EXTRACT);
		/*
		 * We checkpoint the restore after every tape reel, so
		 * as to simplify the amount of work re quired by the
		 * 'R' command.
		 */
	next:
		if (curvol != volno) {
			dumpsymtable(symtabfile, volno);
			skipmaps();
			curvol = volno;
		}
	}
}