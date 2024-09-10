void CButtonEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDialogEx* pParent = (CDialogEx*)GetParent();
	if (pParent->GetFocusButton() != this)
	{
		// Change the help text
		if(m_HelpTextCtrl != NULL)
		{
			CRect rcCtrl;
			m_HelpTextCtrl->GetWindowRect(&rcCtrl);
			pParent->ScreenToClient(&rcCtrl);
			m_HelpTextCtrl->SetWindowText(m_csHelpText);
			pParent->InvalidateRect(&rcCtrl);
		}

		pParent->SetFocusButton(this);
		if(m_bitmapFocus.m_hObject != NULL)
			PlaySound(IDR_SELECT);

	}
	
	CBitmapButton::OnMouseMove(nFlags, point);
}