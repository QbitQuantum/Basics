void CG2XPrintHelper::OnDialogPrintPreview()
{
	CFrameWnd* pOldFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	pOldFrame->ShowWindow(SW_HIDE);
	if (!m_pTemplate)
	{
		UINT nResID = 0;
#ifdef IDR_MAINFRAME
		nResID = IDR_MAINFRAME;
#endif
		m_pTemplate = new CSingleDocTemplate(
			nResID,					// so load fram is happy. This matches the IDR_MAINFRAME value from your application!
			NULL,
			RUNTIME_CLASS(CG2XPrintFrameWnd),
			RUNTIME_CLASS(CG2XPrintDummyView));
		//AfxGetApp()->AddDocTemplate(m_pTemplate);
	}
	CFrameWnd* pFrameWnd = m_pTemplate->CreateNewFrame(NULL, NULL);

	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	// must not create this on the frame.  Must outlive this function
	//CPrintPreviewState* pState = new CPrintPreviewState;
	m_pTemplate->InitialUpdateFrame(pFrameWnd, NULL, FALSE);
	m_pView = (CG2XPrintDummyView*)pFrameWnd->GetActiveView();
	AfxGetApp()->m_pMainWnd = pFrameWnd;
	pFrameWnd->SetWindowText(_T("打印预览"));
	pFrameWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pView->SetPrintDialog(this);
	m_pView->m_pOldFrame = pOldFrame;
	m_pView->OnDoPrintPreview();
}