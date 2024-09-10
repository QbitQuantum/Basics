// ---------------------------------------------------------------------
FskErr FskFSFileGetSize(FskFSFile fref, FskInt64 *size) {
	FILEOFFSET	pos, end;
	FskErr err = kFskErrNone;
	int	ret;

	ret = FTELL(fref->theFile);
	if (ret < 0) goto bail;

	pos = ret;
	FSEEK(fref->theFile, 0, SEEK_END);
	ret = FTELL(fref->theFile);
	if (ret < 0) goto bail;

	end = ret;
	ret = FSEEK(fref->theFile, pos, SEEK_SET);

	fref->flushBeforeRead = false;
	fref->flushBeforeWrite = false;

	if (size)
		*size = end;

bail:
	if (ret < 0)
		err = errnoToFskErr(errno);

	return err;
}