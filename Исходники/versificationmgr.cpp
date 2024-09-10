char VersificationMgr::System::getVerseFromOffset(long offset, int *book, int *chapter, int *verse) const {

	if (offset < 1) {	// just handle the module heading corner case up front (and error case)
		(*book) = -1;
		(*chapter) = 0;
		(*verse) = 0;
		return offset;	// < 0 = error
	}

	// binary search for book
	vector<Book>::iterator b = lower_bound(p->books.begin(), p->books.end(), offset, BookOffsetLess());
	if (b == p->books.end()) b--;
	(*book)    = distance(p->books.begin(), b)+1;
	if (offset < (*(b->p->offsetPrecomputed.begin()))-((((!(*book)) || (*book)==BMAX[0]+1))?2:1)) { // -1 for chapter headings
		(*book)--;
		if (b != p->books.begin()) {
			b--;	
		}
	}
	vector<long>::iterator c = lower_bound(b->p->offsetPrecomputed.begin(), b->p->offsetPrecomputed.end(), offset);

	// if we're a book heading, we are lessthan chapter precomputes, but greater book.  This catches corner case.
	if (c == b->p->offsetPrecomputed.end()) {
		c--;
	}
	if ((offset < *c) && (c == b->p->offsetPrecomputed.begin())) {
		(*chapter) = (offset - *c)+1;	// should be 0 or -1 (for testament heading)
		(*verse) = 0;
	}
	else {
		if (offset < *c) c--;
		(*chapter) = distance(b->p->offsetPrecomputed.begin(), c)+1;
		(*verse)   = (offset - *c);
	}
	return ((*chapter > 0) && (*verse > b->getVerseMax(*chapter))) ? KEYERR_OUTOFBOUNDS : 0;
}