CDocument* CMyMultiDocTemplate::OpenDocumentFile(SDialingDir *psDialingDir)
{
    CDComDoc* pDocument = (CDComDoc*)CreateNewDocument();
    if (pDocument == NULL)
    {
        TRACE(traceAppMsg, 0, "CDocTemplate::CreateNewDocument returned NULL.\n");
        AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
        return NULL;
    }
    ASSERT_VALID(pDocument);

    BOOL bAutoDelete = pDocument->m_bAutoDelete;
    pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
    CFrameWnd* pFrame = CreateNewFrame(pDocument, NULL);
    pDocument->m_bAutoDelete = bAutoDelete;
    if (pFrame == NULL)
    {
        AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
        delete pDocument;       // explicit delete on error
        return NULL;
    }
    ASSERT_VALID(pFrame);

    // open an existing document
    CWaitCursor wait;
    if (!pDocument->OnOpenDocument(psDialingDir))
    {
        // user has be alerted to what failed in OnOpenDocument
        TRACE(traceAppMsg, 0, "CDocument::OnOpenDocument returned FALSE.\n");
        pFrame->DestroyWindow();
        return NULL;
    }

    InitialUpdateFrame(pFrame, pDocument, TRUE);
    return pDocument;
}