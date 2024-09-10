void ProceedingDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CButton *bp = (CButton *)GetDlgItem( IDCANCEL );
        bp->ShowWindow( SW_HIDE );
    }
}