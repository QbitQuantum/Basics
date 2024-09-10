IV
PerlIOMmap_map(pTHX_ PerlIO *f)
{
    dVAR;
    PerlIOMmap * const m = PerlIOSelf(f, PerlIOMmap);
    const IV flags = PerlIOBase(f)->flags;
    IV code = 0;
    if (m->len)
	abort();
    if (flags & PERLIO_F_CANREAD) {
	PerlIOBuf * const b = PerlIOSelf(f, PerlIOBuf);
	const int fd = PerlIO_fileno(f);
	Stat_t st;
	code = Fstat(fd, &st);
	if (code == 0 && S_ISREG(st.st_mode)) {
	    SSize_t len = st.st_size - b->posn;
	    if (len > 0) {
		Off_t posn;
		if (PL_mmap_page_size <= 0)
		  Perl_croak(aTHX_ "panic: bad pagesize %" IVdf,
			     PL_mmap_page_size);
		if (b->posn < 0) {
		    /*
		     * This is a hack - should never happen - open should
		     * have set it !
		     */
		    b->posn = PerlIO_tell(PerlIONext(f));
		}
		posn = (b->posn / PL_mmap_page_size) * PL_mmap_page_size;
		len = st.st_size - posn;
		m->mptr = (Mmap_t)mmap(NULL, len, PROT_READ, MAP_SHARED, fd, posn);
		if (m->mptr && m->mptr != (Mmap_t) - 1) {
#if 0 && defined(HAS_MADVISE) && defined(MADV_SEQUENTIAL)
		    madvise(m->mptr, len, MADV_SEQUENTIAL);
#endif
#if 0 && defined(HAS_MADVISE) && defined(MADV_WILLNEED)
		    madvise(m->mptr, len, MADV_WILLNEED);
#endif
		    PerlIOBase(f)->flags =
			(flags & ~PERLIO_F_EOF) | PERLIO_F_RDBUF;
		    b->end = ((STDCHAR *) m->mptr) + len;
		    b->buf = ((STDCHAR *) m->mptr) + (b->posn - posn);
		    b->ptr = b->buf;
		    m->len = len;
		}
		else {
		    b->buf = NULL;
		}
	    }
	    else {
		PerlIOBase(f)->flags =
		    flags | PERLIO_F_EOF | PERLIO_F_RDBUF;
		b->buf = NULL;
		b->ptr = b->end = b->ptr;
		code = -1;
	    }
	}
    }
    return code;
}