void CVisualADSDoc::MyOnClose()
{
	// TODO: 在此添加命令处理程序代码
	if (!SaveModified())
		return;
	
	BOOL bAutoDelete = m_bAutoDelete;
	m_bAutoDelete = FALSE; // don't destroy document while closing views
	while (!m_viewList.IsEmpty())
	{
		// get view attached to the document
		CView* pView = (CView*)m_viewList.GetHead();
		ASSERT_VALID(pView);
		pView->DestroyWindow();
	}
	m_bAutoDelete = bAutoDelete;
	
	// clean up contents of document before destroying the document itself
	DeleteContents();
	
	// delete the document if necessary
	if (m_bAutoDelete)
		delete this;
}