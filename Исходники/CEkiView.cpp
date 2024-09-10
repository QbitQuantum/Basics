void CEkiView::OnSetFocus(CWnd* pOldWnd) 
{
	//CView::OnSetFocus(pOldWnd);
	CWnd*	pControl = GetNextDlgTabItem( (CWnd*)NULL , FALSE ) ;
	pControl->SetFocus() ;
	
}