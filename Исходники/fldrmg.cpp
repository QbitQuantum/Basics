bool
FLDS::FProcessDirectory(char * szDir)
	{
	bool		fStat;
	FLDS *		pflds;
	HANDLE		fh;
	char 		szSrc[MAX_PATH];
	char 		szDst[MAX_PATH];
	char		szMsg[cchLogMsgMax];
	DWORD		err;

	fStat = fFalse;

	/* Don't add the '.' and '..' directories to the list.
	*/
	if ((CompareSz(szDir, ".") == 0) || (CompareSz(szDir, "..") == 0)) {
		return fTrue;
	}

	/* Set the source path string
	*/
	if ((CchOfSz(szPathSrc)+CchOfSz(szDir)+1) > MAX_PATH) {
		apst.SetErrLast(errPathLength);
		sprintf_s(szMsg, cchLogMsgMax, "Path name too long: %s\\%s\n", szPathSrc, szDir);
		app.PrintMessage(idMsgError, szMsg);
		cmdx.LogMessage(idMsgError, szMsg);
		goto lErrorExit;
	}
	SzCopy(szSrc, szPathSrc);
	SzAppendPathSeparator(SzEnd(szSrc));
	SzAppend(szSrc, szDir);

	/* Set up the destination path string.
	*/	
	if ((CchOfSz(szPathDst)+CchOfSz(szDir)+1) > MAX_PATH) {
		apst.SetErrLast(errPathLength);
		sprintf_s(szMsg, cchLogMsgMax, "Path name too long: %s\\%s\n", szPathDst, szDir);
		app.PrintMessage(idMsgError, szMsg);
		cmdx.LogMessage(idMsgError, szMsg);
		goto lErrorExit;
	}
	SzCopy(szDst, szPathDst);
	SzAppendPathSeparator(SzEnd(szDst));
	SzAppend(szDst, szDir);

	/* Check if this directory is one that is being excluded.
	*/	
	if (fldrmg.FMatchXclPath(szSrc)) {
		if (apst.FPrintXclDir() || apst.FLogXclDir()) {
			sprintf_s(szMsg, cchLogMsgMax, "Skipping: %s\n", szSrc);
			app.PrintMessage(idMsgSkipDir, szMsg);
			cmdx.LogMessage(idMsgSkipDir, szMsg);
		}
		fldrmg.DirExcluded();
		return fTrue;
	}

	/* Check that the destination directory exists, and create it if
	** it doesn't
	*/
	fh = CreateFile(szDst, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_READONLY|FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (fh == INVALID_HANDLE_VALUE) {

		err = GetLastError();
		if ((err != ERROR_FILE_NOT_FOUND) && (err != ERROR_PATH_NOT_FOUND)) {
			apst.SetStProg(stFileSystemError);
			goto lErrorExit;
		}

		if (apst.FPrintDir() || apst.FLogDir()) {
			sprintf_s(szMsg, cchLogMsgMax, "Creating: %s\n", szDst);
			app.PrintMessage(idMsgCreateDir, szMsg);
			cmdx.LogMessage(idMsgCreateDir, szMsg);
		}

		if (!apst.FNoCopyDir()) {
			fldrmg.DirCreated();
			if (!FCreatePath(szDst)) {
				apst.SetErrLast(errFileSystem);
				sprintf_s(szMsg, cchLogMsgMax, "Error creating directory: %s", szDst);
				app.PrintMessage(idMsgError, szMsg);
				cmdx.LogMessage(idMsgError, szMsg);
				goto lErrorExit;
			}
		}
	}
	else {
		CloseHandle(fh);
	}

	/* Create the new folder object.
	*/
	pflds = new FLDS;
	if (pflds == NULL) {
		apst.SetErrLast(errOutOfMemory);
		goto lErrorExit;
	}

	/* Set the path names into the FLDR object and add it to the list
	** of directories to be processed.
	*/
	pflds->SetPathSrc(szSrc);
	pflds->SetPathDst(szDst);

	fldrmg.AddPfldr(pflds);
	fStat = fTrue;

lErrorExit:
	return fStat;

}