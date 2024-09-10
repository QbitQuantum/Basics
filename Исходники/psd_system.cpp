psd_int psd_fsize(void * file)
{
	IStream *is = (IStream *)file;
	if (is) {
		STATSTG stat;
		is->Stat(&stat, STATFLAG_NONAME);
		return (psd_int)stat.cbSize.QuadPart;
	}
	return 0;
}