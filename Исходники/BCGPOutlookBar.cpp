//*********************************************************************************
BOOL CBCGPOutlookBar::SaveState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	CBCGPBaseTabbedBar::SaveState (lpszProfileName, nIndex, uiID);

	for (POSITION pos = m_lstCustomPages.GetHeadPosition (); pos != NULL;)
	{
		CBCGPOutlookBarPane* pPage = (CBCGPOutlookBarPane*)m_lstCustomPages.GetNext (pos);
		ASSERT_VALID (pPage);
		int nID = pPage->GetDlgCtrlID ();
		pPage->SaveState (lpszProfileName, nID, nID);
	}

	CString strProfileName = ::BCGPGetRegPath (strOutlookBarProfile, lpszProfileName);

	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, strProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, strProfileName, nIndex, uiID);
	}

	try
	{
		CMemFile file;

		{
			CArchive ar (&file, CArchive::store);

			ar << (int) m_lstCustomPages.GetCount ();
			for (POSITION pos = m_lstCustomPages.GetHeadPosition (); pos != NULL;)
			{
				CBCGPOutlookBarPane* pPage = (CBCGPOutlookBarPane*)m_lstCustomPages.GetNext (pos);
				ASSERT_VALID (pPage);

				ar << pPage->GetDlgCtrlID ();
				
				CString strName;
				if (pPage->IsTabbed ())
				{
					pPage->GetWindowText (strName);
				}
				else
				{
					pPage->GetParent ()->GetWindowText (strName);
				}

				ar << strName;
			}
			
			CBCGPOutlookWnd* pOutlookBar = (CBCGPOutlookWnd*) GetUnderlinedWindow ();
			if (pOutlookBar != NULL)
			{
				ar << pOutlookBar->GetVisiblePageButtons ();
			}
			else
			{
				ar << -1;
			}

			ar.Flush ();
		}

		UINT uiDataSize = (UINT) file.GetLength ();
		LPBYTE lpbData = file.Detach ();

		if (lpbData != NULL)
		{
			CBCGPRegistrySP regSP;
			CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

			if (reg.CreateKey (strSection))
			{
				reg.Write (strRegCustomPages, lpbData, uiDataSize);
			}

			free (lpbData);
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CBCGPOutlookBar::SaveState ()!\n"));
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Archive exception in CBCGPOutlookBar::SaveState ()!\n"));
	}

	return TRUE;
}