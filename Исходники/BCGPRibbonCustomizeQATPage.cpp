//**********************************************************************
void CBCGPRibbonCustomizeQATPage::OnOK() 
{
	UpdateData ();

	ASSERT_VALID (m_pRibbonBar);

	CList<UINT,UINT> lstQACommands;

	for (int i = 0; i < m_wndQATList.GetCount (); i++)
	{
		lstQACommands.AddTail (m_wndQATList.GetCommand (i)->GetID ());
	}

	m_pRibbonBar->OnCancelMode ();
	m_pRibbonBar->m_QAToolbar.ReplaceCommands (lstQACommands);
	m_pRibbonBar->SetQuickAccessToolbarOnTop (!m_bQAToolbarOnBottom);

	m_pRibbonBar->RecalcLayout ();

	CFrameWnd* pParentFrame = m_pRibbonBar->GetParentFrame ();
	
	if (pParentFrame->GetSafeHwnd () != NULL)
	{
		pParentFrame->RecalcLayout ();
		pParentFrame->RedrawWindow ();
	}

	CBCGPPropertyPage::OnOK();
}