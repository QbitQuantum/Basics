void vmsHttpFlvTrafficAnalyzer5::LogMainCall (int iCall, LPCSTR pszHtmlPageUrl, LPCSTR pszFrameUrl, LPCSTR pszSwfUrl, LPCSTR pszFlashVars, vector <string> &vOtherSwfUrls, vector <string> &vOtherFlashVars, const vmsWinSockHttpDlgTree *pDlgTree, HTTPDLGTREEITEM pWebPage, HTTPDLGTREEITEM pFrame)
{
	TCHAR tszFile [MAX_PATH] = _T ("");
	GetTempPath (MAX_PATH, tszFile);
	_tcscat (tszFile, _T ("\\fdmflvsniff\\onDownloadIt-"));
	
	_stprintf (tszFile + _tcslen (tszFile), _T ("%03d.html"), iCall);

	HANDLE hFile = CreateFile (tszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	assert (hFile != INVALID_HANDLE_VALUE);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	char szTmp [100] = "";

	string strHtml = "<html><body><h3>vmsHttpFlvTrafficAnalyzer5 onGetItButtonClicked</h3>"; 

	strHtml += "<b>Web page URL:</b><br>"; 
	strHtml += pszHtmlPageUrl ? pszHtmlPageUrl : "";
	assert (pWebPage != NULL);
	if (pWebPage)
	{
		strHtml += "<br>[<a href="; strHtml += itoa (pWebPage->spDlg->nID, szTmp, 16);
		strHtml += "-tree.html>tree</a>][<a href=webfiles\\";
		strHtml += szTmp; strHtml += ".txt>file</a>]";
	}
	strHtml += "<br><br>";

	strHtml += "<b>Frame URL:</b><br>";
	strHtml += pszFrameUrl && *pszFrameUrl && strcmp (pszHtmlPageUrl, pszFrameUrl) ? pszFrameUrl : "Not specified (none)";
	if (pFrame && pFrame != pWebPage)
	{
		strHtml += "<br>[<a href="; strHtml += itoa (pFrame->spDlg->nID, szTmp, 16);
		strHtml += "-tree.html>tree</a>][<a href=webfiles\\";
		strHtml += szTmp; strHtml += ".txt>file</a>]";
	}
	strHtml += "<br><br>";

	strHtml += "<b>Target SWF URL:</b><br>";
	strHtml += pszSwfUrl && *pszSwfUrl ? pszSwfUrl : "";
	strHtml += "<br><br>";

	strHtml += "<b>Target SWF FlashVars:</b><br>";
	strHtml += pszFlashVars ? pszFlashVars : "";
	strHtml += "<br><br>";

	assert (vOtherSwfUrls.size () == vOtherFlashVars.size ());

	if (vOtherSwfUrls.size () != vOtherFlashVars.size ())
		strHtml += "<b>ARGS ERROR: vOtherSwfUrls.size () != vOtherFlashVars.size ()</b><br><br>";
	else for (size_t i = 0; i < vOtherSwfUrls.size (); i++)
	{
		char sz [10] = ""; itoa (i, sz, 10);

		strHtml += "<b>Other SWF #"; strHtml += sz; strHtml += " URL:</b><br>";
		strHtml += vOtherSwfUrls [i].c_str ();
		strHtml += "<br><br>";
		
		strHtml += "<b>Other SWF #"; strHtml += sz; strHtml += " FlashVars:</b><br>";
		strHtml += vOtherFlashVars [i].c_str ();
		strHtml += "<br><br>";
	}
	
	DWORD dw = 0;
	WriteFile (hFile, strHtml.c_str (), strHtml.length (), &dw, NULL);

	CloseHandle (hFile);
}