BOOL CDurableFileController::Init(char* szDirectory, char* szRewriteDirectory)
{
	CChars		szStart;
	CChars		szRewrite;
	CFileUtil	cFileUtil;

	if (StrEmpty(szDirectory))
	{
		return gcLogger.Error2(__METHOD__, " Controller directory must be supplied.", NULL);
	}

	mbDurable = FALSE;
	if (!StrEmpty(szRewriteDirectory))
	{
		mbDurable = TRUE;
	}

	if (mbDurable && (StrICmp(szDirectory, szRewriteDirectory) == 0))
	{
		return gcLogger.Error2(__METHOD__, " Controller directory and rewrite directory must be different.", NULL);
	}

	mszDirectory.Init(szDirectory);
	szStart.Init(szDirectory);
	cFileUtil.AppendToPath(&szStart, "Mark1.Write");

	if (szRewriteDirectory && mbDurable)
	{
		mszRewriteDirectory.Init(szRewriteDirectory);
		szRewrite.Init(szRewriteDirectory);
	}
	else
	{
		mszRewriteDirectory.Init();
		szRewrite.Init(szDirectory);
	}
	cFileUtil.AppendToPath(&szRewrite, "Mark2.Rewrite");

	mcDurableSet.Init(szStart.Text(), szRewrite.Text());

	szRewrite.Kill();
	szStart.Kill();

	return TRUE;
}