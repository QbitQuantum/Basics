FskErr KplFileGetFileInfo(const char *fullPath, KplFileInfo *itemInfo) {
	int err;
	STATTYPE statbuf;

	err = sCheckFullPath(fullPath, kKplPathIsAny);
	if (err) return err;

	err = STAT(fullPath, &statbuf);
	if (err == -1) return errnoToFskErr(errno);

	GetFileInfoFromStat(&statbuf, itemInfo);

	itemInfo->flags = 0;

	return kFskErrNone;
}