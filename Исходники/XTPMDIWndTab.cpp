CString CXTPMDIWndTab::GetChildWndText(HWND hWnd) const
{
	// Check to see if the user has defined a label for the tab first.
	CString strTitle;
	if (m_mapTabLabels.Lookup(hWnd, strTitle))
	{
		return strTitle;
	}

	// Get a pointer to the frame window.
	CMDIChildWnd* pChildFrame = (CMDIChildWnd*)CWnd::FromHandle(hWnd);
	if (!::IsWindow(pChildFrame->GetSafeHwnd()))
	{
		return _T("");
	}

	// Get the window text for the frame and use it for the tab label.
	pChildFrame->GetWindowText(strTitle);

	// If the string is empty the document's title.
	if (strTitle.IsEmpty())
	{
		CWnd* pChildWnd = pChildFrame->GetWindow(GW_CHILD);
		while (pChildWnd)
		{
			if (pChildWnd->IsKindOf(RUNTIME_CLASS(CView)))
			{
				// Get a pointer to the view's document.
				CDocument* pDoc = ((CView*)pChildWnd)->GetDocument();
				if (pDoc == NULL)
				{
					return _T("");
				}

				// Set the return string value
				strTitle = pDoc->GetTitle();

				// Reset the frames title
				pChildFrame->SetWindowText(strTitle);

				// Return the document title.
				return strTitle;
			}
			pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	// Return the MDI frame window's title.
	return strTitle;
}