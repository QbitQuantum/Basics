CFileMatcher::CFileMatcher(LPTSTR pszMask)
{
	m_pszDirBuffer = NULL;

	if (pszMask == NULL)
	{
		ASSERT(FALSE);
		// I am not sure if this is possible - but I better check for it just in case!

		m_fMatchAll    = TRUE;
		m_fMatchAllDir = TRUE;

		// There is no point in initialising m_pszMask and m_pszMultiple - as they will not be used!

		return;
	}

	m_pszMask        = pszMask;
	m_pszMaskDir     = NULL;
	m_pszMultiple    = NULL;
	m_pszMultipleDir = NULL;

	// Parse the mask to see if it contains multiple/dual masks (ie, look for ",;!")

	TCHAR  ch;
	int    nDir   = 0;
	int    nChars = 0;
	LPTSTR pszDir = NULL;
	LPTSTR psz    = pszMask;

	while (ch = *psz++)
	{
		if ((ch == ',') || (ch == ';'))
		{
			if (pszDir)
			{
				if (m_pszMultipleDir == NULL)
					m_pszMultipleDir = pszDir;		// We need to re-point this to the mask buffer when we create it later on
			}
			else
			{
				if (m_pszMultiple == NULL)
				{
					// We will be modifying the multiple mask string - so copy it into m_szMultiple
					m_pszMultiple = m_szMultiple;
					STRNCPY(m_pszMultiple, pszMask, MAX_PATH);
				}
			}
		}
		else

		if ((ch == '|') && !pszDir)
		{
			pszDir = psz;
			nDir   = nChars;
		}

		nChars++;
	}

	BOOL fNoDirs = FALSE;

	if (pszDir)
	{
		// We have a second mask - we will need to assign m_pszDirBuffer so it can hold it
		// We also need to copy the original mask into its own buffer (we will use m_szMultiple) as we will need to replace the | with a nul!

		if (nDir)
		{
			if (m_pszMultiple == NULL)
				STRNCPY(m_szMultiple, pszMask, MAX_PATH);
				
			m_pszMask = m_szMultiple;

			ASSERT(m_szMultiple[nDir] == '|');
			m_szMultiple[nDir] = 0;
		}
		else
		{
			// We have an *empty* mask - we will display *no* files!
			m_pszMask = NULL;
			ASSERT(m_pszMultiple == NULL);
		}

		// If the directory mask contains anything - create a buffer for it - otherwise we will use the same buffers as the "file"
		int nLen = STRLEN(pszDir);

		if (nLen)
		{
			m_pszDirBuffer = new TCHAR[nLen+2];		// We may need to add 2 nuls to the end - this will be done when we parse the buffer later on
			STRCPY(m_pszDirBuffer, pszDir);
			m_pszMaskDir = m_pszDirBuffer;

			if (m_pszMultipleDir)
				m_pszMultipleDir = m_pszMaskDir;
		}
		else
		{
			// The dir mask is empty - display *no* dirs!
			fNoDirs = TRUE;
		}
	}

	if (m_pszMask)
		m_fMatchAll = (!STRCMP(m_pszMask, _T("*.*")) ||! STRCMP(m_pszMask, _T("*"))) ? TRUE : FALSE;
	else
		m_fMatchAll = FALSE;

	if (m_pszMaskDir)
		m_fMatchAllDir = (!STRCMP(m_pszMaskDir, _T("*.*")) ||! STRCMP(m_pszMaskDir, _T("*"))) ? TRUE : FALSE;
	else
		m_fMatchAllDir = !fNoDirs;
    
	if (m_pszMultiple)
		ParseMultiple(m_pszMultiple);
	
	if (m_pszMultipleDir && (m_pszMultipleDir != m_pszMultiple))
		ParseMultiple(m_pszMultipleDir);
}