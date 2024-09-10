void CHexEdit::OnSetFocus(CWnd* pOldWnd) 
{
	if(m_pData && !IsSelected())
	{
		if(m_editPos.x == 0 && m_bShowAddress)
			CreateAddressCaret();
		else
			CreateEditCaret();
		SetCaretPos(m_editPos);
		ShowCaret();
	}
	CWnd::OnSetFocus(pOldWnd);
}