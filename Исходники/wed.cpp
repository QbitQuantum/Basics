CDocument* CWedApp::OpenDocumentFile(LPCTSTR lpszFileName)

{
	CDocument* ret = NULL;
	ret = CWinApp::OpenDocumentFile(lpszFileName);

	if(!ret)
		return ret;

	// See if window creation failed
	if( ((CWedDoc*)ret)->ssel.m_err)
		{
		//Close this one
		pDocTemplate->RemoveDocument(ret);

		//Close some more
		POSITION pos = pDocTemplate->GetFirstDocPosition();

		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));
		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));
		pDocTemplate->RemoveDocument(pDocTemplate->GetNextDoc(pos));

		AfxMessageBox("Windows ran out of windows", MB_ICONSTOP);
		ret = NULL;
		}

	// Maximize it
	// Open up in demonstration/full screen mode:
	POSITION pos = ret->GetFirstViewPosition();
	CView *pView = ret->GetNextView(pos);
	if (pView)
		{
		pView->GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
		ret->UpdateAllViews(NULL);
		}

	return ret;
}