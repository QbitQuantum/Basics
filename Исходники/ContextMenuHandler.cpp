STDMETHODIMP CContextMenuHandler::GetCommandString(UINT_PTR idCmd, UINT uType, UINT *pReserved, LPSTR pszName,UINT cchMax)
{
#ifdef DEBUG_TO_LOG_FILES
	char	tbuf[200];
	sprintf_s(tbuf,200,__FUNCTION__ ": cmd=%lu, type=%u, name=%s",(DWORD)idCmd,uType,pszName);
	f_log(tbuf);
#endif

	HRESULT  hr = E_INVALIDARG;

	const char *aHelp = "";
	size_t aHelpSize = 0;
	const wchar_t *wHelp = L"";
	size_t wHelpSize = 0;

	const char *aVerb = "";
	size_t aVerbSize = 0;
	const wchar_t *wVerb = L"";
	size_t wVerbSize = 0;

	if (idCmd == m_idCmdFirst + eMC_RunConsole) {
		aHelp = szDescrRunConsoleA;
		aHelpSize = sizeof(szDescrRunConsoleA);

		wHelp = szDescrRunConsoleW;
		wHelpSize = sizeof(szDescrRunConsoleW);

		aVerb = szVerbRunConsoleA;
		aVerbSize = sizeof(szVerbRunConsoleA);

		wVerb = szVerbRunConsoleW;
		wVerbSize = sizeof(szVerbRunConsoleW);
	}
	else if (idCmd == m_idCmdFirst + eMC_PostConsole) {
		aHelp = szDescrPostConsoleA;
		aHelpSize = sizeof(szDescrPostConsoleA);

		wHelp = szDescrPostConsoleW;
		wHelpSize = sizeof(szDescrPostConsoleW);

		aVerb = szVerbPostConsoleA;
		aVerbSize = sizeof(szVerbPostConsoleA);

		wVerb = szVerbPostConsoleW;
		wVerbSize = sizeof(szVerbPostConsoleW);
	}
	if (idCmd == m_idCmdFirst + eMC_RunConsoleWithTabFake) {
		aHelp = szDescrRunConsoleWithTabA;
		aHelpSize = sizeof(szDescrRunConsoleWithTabA);

		wHelp = szDescrRunConsoleWithTabW;
		wHelpSize = sizeof(szDescrRunConsoleWithTabW);

		aVerb = szVerbRunConsoleWithTabA;
		aVerbSize = sizeof(szVerbRunConsoleWithTabA);

		wVerb = szVerbRunConsoleW;
		wVerbSize = sizeof(szVerbRunConsoleWithTabW);
	}
	if (idCmd == m_idCmdFirst + eMC_PostConsoleWithTabFake) {
		aHelp = szDescrPostConsoleWithTabA;
		aHelpSize = sizeof(szDescrPostConsoleWithTabA);

		wHelp = szDescrPostConsoleWithTabW;
		wHelpSize = sizeof(szDescrPostConsoleWithTabW);

		aVerb = szVerbPostConsoleWithTabA;
		aVerbSize = sizeof(szVerbPostConsoleWithTabA);

		wVerb = szVerbPostConsoleWithTabW;
		wVerbSize = sizeof(szVerbPostConsoleWithTabW);
	}
	else {
	}

	switch(uType) {
	case GCS_HELPTEXTA:
		hr = StringCbCopyNA(pszName, cchMax, aHelp, aHelpSize);
		break; 

	case GCS_HELPTEXTW:
		hr = StringCbCopyNW((LPWSTR)pszName, cchMax * sizeof(wchar_t), wHelp, wHelpSize);
		break; 

	case GCS_VERBA:
		hr = StringCbCopyNA(pszName, cchMax, aVerb, aVerbSize);
		break; 

	case GCS_VERBW:
		hr = StringCbCopyNW((LPWSTR)pszName, cchMax * sizeof(wchar_t), wVerb, wVerbSize);
		break; 

	default:
		hr = S_OK;
		break; 
	}
	return hr;
}