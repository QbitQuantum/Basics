//-----------------------------------------------------------------------------
// Purpose: Called when they hit the Find, the Replace, or the Replace All button.
// Input  : uCmd - The ID of the button the user hit, IDC_FIND_NEXT or IDC_REPLACE.
// Output : Returns TRUE to indicate that the message was handled.
//-----------------------------------------------------------------------------
BOOL CSearchReplaceDlg::OnFindReplace(UINT uCmd)
{
	CMapDoc *pDoc = CMapDoc::GetActiveMapDoc();
	if (!pDoc)
	{
		return TRUE;
	}

	static FindObject_t FindObject;
	static CMapClass *pLastFound = NULL;
	static nReplaceCount = 0;

	bool bDone = false;

	do
	{
		CMapClass *pObject = NULL;

		if (m_bNewSearch)
		{
			//
			// New search. Fetch the data from the controls.
			//
			UpdateData();
			GetFindCriteria(FindObject, pDoc);

			//
			// We have to keep track of the last object in the iteration for replacement,
			// because replacement is done when me advance to the next object.
			//
			pLastFound = NULL;
			nReplaceCount = 0;

			pObject = FindFirstObject(FindObject);
		}
		else
		{
			pObject = FindNextObject(FindObject);
		}

		//
		// Replace All is undone as single operation. Mark the undo position the first time
		// we find a match during a Replace All.
		//
		if (m_bNewSearch && (uCmd == IDC_REPLACE_ALL) && pObject)
		{
			GetHistory()->MarkUndoPosition(pDoc->Selection_GetList(), "Replace Text");
		}

		//
		// If we have an object to do the replace on, do the replace.
		//
		if (pLastFound && ((uCmd == IDC_REPLACE) || (uCmd == IDC_REPLACE_ALL)))
		{
			if (uCmd == IDC_REPLACE)
			{
				// Allow for undo each time we do a Replace.
				GetHistory()->MarkUndoPosition(NULL, "Replace Text");
			}

			//
			// Do the replace on the last matching object we found. This lets the user see what
			// object will be modified before it is done.
			//
			GetHistory()->Keep(pLastFound);
			nReplaceCount += FindReplace((CMapEntity *)pLastFound, FindObject, m_strReplaceText);

			GetDlgItem(IDCANCEL)->SetWindowText("Close");
		}

		if (pObject)
		{
			//
			// We found an object that satisfies our search.
			//
			if ((uCmd == IDC_FIND_NEXT) || (uCmd == IDC_REPLACE))
			{
				//
				// Highlight the match.
				//
				pDoc->SelectObject(pObject, CMapDoc::scClear | CMapDoc::scSelect);
				pDoc->CenterSelection();
			}

			//
			// Stop after one match unless we are doing a Replace All.
			//
			if (uCmd != IDC_REPLACE_ALL)
			{
				bDone = true;
			}

			m_bNewSearch = false;
			pLastFound = pObject;
		}
		else
		{
			//
			// No more objects in the search set match our criteria.
			//
			if ((m_bNewSearch) || (uCmd != IDC_REPLACE_ALL))
			{
				CString str;
				str.Format("Finished searching for '%s'.", m_strFindText);
				MessageBox(str, "Find/Replace Text", MB_OK);

				// TODO: put the old selection back
			}
			else if (uCmd == IDC_REPLACE_ALL)
			{
				CString str;
				str.Format("Replaced %d occurrences of the string '%s' with '%s'.", nReplaceCount, m_strFindText, m_strReplaceText);
				MessageBox(str, "Find/Replace Text", MB_OK);
			}

			m_bNewSearch = true;
			bDone = true;
		}

	} while (!bDone);

	return TRUE;
}