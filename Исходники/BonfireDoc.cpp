BOOL CBonfireDoc::ExistsSourceView(LPCTSTR lpszPathName)
{
	CStringList pTabList;
	CString ext = (lpszPathName == NULL) 
				? GetFileExtension(GetPathName()) 
				: GetFileExtension(lpszPathName);
	
	// generate tabs based on the file extension
	CString strViews	= theApp.m_opOptions.views.vAssociations[0].strViews; // init to default views
	CString strExtList	= "";
	size_t nExt			= theApp.m_opOptions.views.vAssociations.size();
	
	// see if the current file's extension is in the list
	while (nExt-- > 0) // 0 is the default file extension
	{
		strExtList = (CString)theApp.m_opOptions.views.vAssociations[nExt].strExtensions;
		strExtList.Remove(' ');

		if (IsStringPresent(strExtList, ext))
		{
			strViews = theApp.m_opOptions.views.vAssociations[nExt].strViews;
			break;
		}
	}

	return (strViews[0] != '-' || strViews[0] == 's');
}