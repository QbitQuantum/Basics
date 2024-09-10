void Fatal ()
// fatal error, attempt to shut down and exit
// if we already tried to shut down -- just abort without doing anything
{
	static BOOL fTwice;
	if (!fTwice) {
		fTwice = TRUE;
		if (pnmBsc) pnmBsc->close();
		if (pdbBsc) {
			pdbBsc->Close();	// do not commit!

			// see if we should delete
			if (fDeleteOnFatal && OutputFileName) {
				_unlink(OutputFileName);
			}
			else // restore the file time if possible...
			if (OutputFileName && sbufBsc.st_atime && sbufBsc.st_mtime) {
				struct _utimbuf ubuf;
				ubuf.actime  = sbufBsc.st_atime;
				ubuf.modtime = sbufBsc.st_mtime;
				_utime(OutputFileName, &ubuf);
			}
		}
	}
	exit(4);
}