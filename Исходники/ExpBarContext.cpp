BOOL CExpBarContext::CreateControlWndEx(CWnd* pParent)
{
	if (!m_pDoc)
	{
		BOOL bSuccess = m_pExpBar->Create(CRect(0,0,50,100), pParent, 0);
		if (bSuccess)
		{
			m_EventManager.SetEvents(CEBCtrlEvents, ebLastEvent, "", CBLModule::GetExecutedModule(), this, m_pUDC);
		}
		return bSuccess;
	}else{
		CControlID* pControlID = m_pField->GetCtrlInfo();
		CWnd* pControlWnd = m_pDoc->GetFieldWnd(m_pField);
		CRect rect;
		pControlWnd->GetWindowRect(&rect);
		pParent->ScreenToClient(rect);
		
		BOOL bSuccess = m_pExpBar->Create(rect, pParent, m_pField->GetCtrlID());
		if (bSuccess)
		{
			pControlWnd->DestroyWindow();
			m_EventManager.SetEvents(CEBCtrlEvents, ebLastEvent, pControlID, m_pDoc->m_pBLModule, this, m_pUDC);
		}
		
		return bSuccess;
	}
}