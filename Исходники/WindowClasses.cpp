HWND CWnd::HtmlHelp(UINT uCommand,DWORD_PTR dwData,LPCWSTR szHelpFile)
{
	if (szHelpFile==NULL)
		szHelpFile=GetApp()->m_szHelpFile;

	if (szHelpFile!=NULL)
	{	
		if (FirstCharIndex(szHelpFile,L'\\')!=-1)
		{
			if (IsUnicodeSystem())
				return HtmlHelpW(m_hWnd,szHelpFile,uCommand,dwData);
			else
				return HtmlHelpA(m_hWnd,W2A(szHelpFile),uCommand,dwData);
		}



		// Insert path
		if (IsUnicodeSystem())
		{
			CStringW sExeName=GetApp()->GetExeNameW();
			return HtmlHelpW(*this,sExeName.Left(sExeName.FindLast(L'\\')+1)+szHelpFile,
				uCommand,dwData);
		}
	
		CString sExeName=GetApp()->GetExeName();
		return HtmlHelpA(*this,sExeName.Left(sExeName.FindLast(L'\\')+1)+szHelpFile,
			uCommand,dwData);
	}



	if (IsUnicodeSystem())
	{
		CStringW sExeName=GetApp()->GetExeNameW();
		return HtmlHelpW(*this,sExeName.Left(sExeName.FindLast(L'.')+1)+L"chm",
			uCommand,dwData);
	}

	CString sExeName=GetApp()->GetExeName();
	return HtmlHelpA(*this,sExeName.Left(sExeName.FindLast(L'.')+1)+"chm",
		uCommand,dwData);
}