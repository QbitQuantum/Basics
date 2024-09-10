int
fseek(FILE *iop, long offset, int ptrname)
{
	off_t	p;
	rmutex_t *lk;

	FLOCKFILE(lk, iop);
	iop->_flag &= ~_IOEOF;

	if (!(iop->_flag & _IOREAD) && !(iop->_flag & (_IOWRT | _IORW))) {
		errno = EBADF;
		FUNLOCKFILE(lk);
		return (-1);
	}

	if (iop->_flag & _IOREAD) {
		if (ptrname == 1 && iop->_base && !(iop->_flag&_IONBF)) {
			offset -= iop->_cnt;
		}
	} else if (iop->_flag & (_IOWRT | _IORW)) {
		if (_fflush_u(iop) == EOF) {
			FUNLOCKFILE(lk);
			return (-1);
		}
	}
	iop->_cnt = 0;
	iop->_ptr = iop->_base;
	if (iop->_flag & _IORW) {
		iop->_flag &= ~(_IOREAD | _IOWRT);
	}
	p = lseek(FILENO(iop), (off_t)offset, ptrname);
	FUNLOCKFILE(lk);
	return ((p == (off_t)-1) ? -1: 0);
}