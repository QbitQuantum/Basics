void COptionsStats::OnRemoveAll() 
{
	if(MessageBox(theApp.m_Language.GetString("Remove_All", "This will remove all Copy Entries!\n\nContinue?"), _T("Warning"), MB_YESNO) == IDYES)
	{
		if( DeleteAllIDs() )
		{
			m_eSavedCopies.Empty();
			m_eSavedCopyData.Empty();

			struct _stat buf;
			int nResult;
			nResult = STAT(GetDBName(), &buf);
			if(nResult == 0)
				m_eDatabaseSize.Format(_T("%d KB"), (buf.st_size/1024));

			UpdateData(FALSE);
		}
	}
}