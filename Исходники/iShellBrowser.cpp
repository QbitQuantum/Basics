void CShellBrowser::QueryFullItemNameInternal(int iItemInternal,TCHAR *szFullFileName,UINT cchMax) const
{
	LPITEMIDLIST	pidlComplete = NULL;

	pidlComplete = ILCombine(m_pidlDirectory,m_pExtraItemInfo[iItemInternal].pridl);

	GetDisplayName(pidlComplete,szFullFileName,cchMax,SHGDN_FORPARSING);

	CoTaskMemFree(pidlComplete);
}