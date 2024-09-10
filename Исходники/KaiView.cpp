void CKaiView::OnKillFocus (CWnd* pNewWnd) 
{
    CView::OnKillFocus(pNewWnd);
    
    // TODO: Add your message handler code here    
    BOOL mfcb_ = DestroyCaret(); // MSDN says this is required

}