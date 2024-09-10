CDocument* CMyDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible)
{
	if (lpszPathName == NULL)
	{
		TRACE(_T("Creating new documents is disabled.\n"));
		return NULL;
	}

	CWaitCursor wait;

	CDocument* pDocument = CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE(_T("CDocTemplate::CreateNewDocument returned NULL.\n"));
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT_VALID(pDocument);

	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = false;   // don't destroy if something goes wrong

	CWnd* pMDIChild = CreateNewMDIChild(pDocument);

	pDocument->m_bAutoDelete = bAutoDelete;
	if (pMDIChild == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		delete pDocument;       // explicit delete on error
		return NULL;
	}
	ASSERT_VALID(pMDIChild);

	// open an existing document
	if (!pDocument->OnOpenDocument(lpszPathName))
	{
		// user has be alerted to what failed in OnOpenDocument
		TRACE(_T("CDocument::OnOpenDocument returned FALSE.\n"));
		pMDIChild->DestroyWindow();
		return NULL;
	}
	pDocument->SetPathName(lpszPathName);

	InitialUpdateMDIChild(pMDIChild, pDocument, bMakeVisible);
	return pDocument;
}