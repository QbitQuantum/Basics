// exceptions: CString for parsing errors
CProcessingPrefs::CProcessingPrefs(SFMFile* f)
:	m_pInputLang(NULL),
	m_pTargetLang(NULL),
	m_iGoal(kTargetText),
	m_iVerbosity(0)
{
	USES_CONVERSION;
	CString sMarker, sField;
	while(f->getField(sMarker, sField))
	{
		if(sMarker==A2CT(ksrcEndMarker))
			break;
		else if (sMarker == _T("Verbosity"))
		{
			m_iVerbosity = _ttoi(sField);
		}
		else checkAndReadInt(_T("Goal"), m_iGoal)

		else if(sMarker == _T("Flags"))
			m_dwFlags=_ttoi(sField);

		else if (sMarker == _T("InputLangID"))
		{
			m_pInputLang = NULL; // can't look this up yet
			m_sTempInputLangID = sField;	// save for the "finish create" cycle, when all language docs have been loaded
										// and we can look up this id and get the pointer
		}
		else if (sMarker == _T("TargetLangID"))
		{
			m_pTargetLang = NULL; // can't look this up yet
			m_sTempTargetLangID = sField;	// save for the "finish create" cycle, when all language docs have been loaded
										// and we can look up this id and get the pointer
		}
		else f->throwParseFailure(_T("ProcessingPrefs"), sMarker, sField);
	}

	if(theApp.getProject()->getHaveLanguages())
	{
		if(!m_pInputLang)
			m_pInputLang = theApp.getProject()->getLangFromIndex(0);
		if(!m_pTargetLang)
			m_pTargetLang = theApp.getProject()->getLangFromIndex(0);
	}
}