void CSynBCGPEditView::OnHtmltoblog()
{
	CWnd *pParentWnd = GetParent();
	if (pParentWnd == NULL)
	{
		return;
	}
	pParentWnd = pParentWnd->GetParent();
	if (pParentWnd == NULL)
	{
		return;
	}

	CWaitCursor wait;
	BOOL bAlreadyShow = TRUE;
	CBCGPTabView *pTabView = (CBCGPTabView *)pParentWnd;
	if (pTabView->GetTabControl().GetTabsNum() == 1)
	{
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(ID_TAB_HTML);
		ASSERT(bNameVaild);
		pTabView->AddView(RUNTIME_CLASS(CSynHtmlView), strTemp, ID_TAB_HTML);
		bAlreadyShow = FALSE;
	}
	pTabView->SetActiveView(1);
	CSynHtmlView *pHtmlView = (CSynHtmlView *)pTabView->GetActiveView();
	CString strCode;
	m_pEdit->ExportToMyHTML(strCode);
	pHtmlView->ShowCodeToHtml(strCode, m_pEdit->GetText(), m_pEdit->GetSelectLangString(), m_pEdit->GetLineCount(), bAlreadyShow);
}