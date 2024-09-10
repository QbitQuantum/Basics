/**  Get shortcut info on current file
 *
 *	 @param[in]		pszPathShortcut	path to shortcut file
 *	 @param[out]	pszPathTarget	variable to be set to shortcut's target path
 *	 @param[in]		cchMaxPath		length of pszPathTarget buffer, in characters
 *	 @param[out]	psFd			shortcut's target info
 *
 *	 @returns successful @b HRESULT on success, else failing @b HRESULT on 
 *			  on error or if the current file is not a link.
 */
HRESULT CFileIterator::GetShortcutInfo(LPCTSTR pszPathShortcut, LPTSTR pszPathTarget, int cchMaxPath, WIN32_FIND_DATA* psFd) const
{
	// try opening the link...
	IShellLink* piLink;
	HRESULT hr = OpenLink(pszPathShortcut, &piLink);
	if (SUCCEEDED(hr))
	{
		// Get the path to the link target. 
	    hr = piLink->GetPath(pszPathTarget, cchMaxPath, psFd, SLGP_UNCPRIORITY);
		piLink->Release();
	}
	return hr;
}