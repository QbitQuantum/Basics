void CAutoRepeatButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    KillTimer(IDT_TIMER);
	
	if(GetCapture() != NULL)
	{ /* release capture */
		ReleaseCapture();
	if(sent == 0 && (GetState() & BST_PUSHED) != 0)
	   GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	} /* release capture */
       
	   
    
    //CButton::OnLButtonUp(nFlags, point);
}