//------------------------------------------------------------------------
//! Update the subtitle in the group header
//!
//! @param nGroupId ID of the group
//! @param strSubtitle The subtitle description text
//! @return Succeeded in updating the group subtitle
//------------------------------------------------------------------------
BOOL CGridListCtrlGroups::SetGroupSubtitle(int nGroupId, const CString& strSubtitle)
{
	if (!IsGroupStateEnabled())
		return FALSE;

#if _WIN32_WINNT >= 0x0600
	LVGROUP lg = {0};
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_SUBTITLE;
#ifdef UNICODE
	lg.pszSubtitle = (LPWSTR)(LPCTSTR)strSubtitle;
	lg.cchSubtitle = strSubtitle.GetLength();
#else
	CComBSTR bstrSubtitle = strSubtitle;
	lg.pszSubtitle = bstrSubtitle;
	lg.cchSubtitle = bstrSubtitle.Length();
#endif

	if (SetGroupInfo(nGroupId, (PLVGROUP)&lg)==-1)
		return FALSE;

	return TRUE;
#else
	return FALSE;
#endif
}