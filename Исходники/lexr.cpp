bool
LEXR::FOpenFile(char * sz)
	{
	errno_t		errno;

	if (sz == NULL) {
		err = errLexrNoFile;
		return fFalse;
	}
	
#if OptLexrInclude != 0
	if ((istmgCur+1) >= cstmgLexrIncludeMax) {
		err = errLexrIncludeDepth;
		return fFalse;
	}

	rgstmg[istmgCur].SetFlgCur(flg);
	rgstmg[istmgCur].SetSzFile(szFile);
	rgstmg[istmgCur].SetFhFile(fhFile);
	rgstmg[istmgCur].SetIlnCur(ilnCur);
	istmgCur += 1;
#endif

	if ((szFile = new char [strlen(sz)+1]) == NULL) {
		err = errOutOfMemory;
		return fFalse;
	}

	SzCopy(szFile, sz);
	
	if ((fopen_s(&fhFile, szFile, "rt") != 0) || (fhFile == NULL)) {
		_get_errno(&errno);
		if (errno == ENOENT) {
			err = errFileNotFound;
		}
		else {
			err = errFileSystem;
		}
		return fFalse;
	}
	
	flg.Set(flgLexrOwnFile);
	flg.Clr(flgLexrEof);
	
	return fTrue;

}