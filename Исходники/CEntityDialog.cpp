//---------------------------------------------------------------
// Purpose: 
//---------------------------------------------------------------
BOOL CEntityDialog::OnInitDialog()
{
	if( !CDialogEx::OnInitDialog() )
		return FALSE;

	//Create copy of editable entity
	m_oldEntity = GetActiveDocument()->GetSelectedEntity(0);
	m_newEntity = m_oldEntity->Clone();
	Assert( m_oldEntity && m_newEntity );
	GetActiveDocument()->GetEntityList()->ReplaceEntity( m_oldEntity, m_newEntity );
	GetActiveDocument()->SelectSingleEntity( m_newEntity );
	m_dialogClassInfo.SetEditEntity(m_newEntity);

	//Get Tab Control
	CTabCtrl *pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);

	//Create Tab Content dialog and adjust
	m_dialogClassInfo.Create(IDD_ENTITY_CLASS_INFO, pTabCtrl);

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT | TCIF_PARAM;
	tcItem.pszText = _T("Class Info");
	tcItem.lParam = (LPARAM)&m_dialogClassInfo;
	pTabCtrl->InsertItem(0, &tcItem);

	RECT wndrect;
	GetClientRect(&wndrect);
	wndrect.top -= 15;
	wndrect.bottom -= 30;
	pTabCtrl->AdjustRect( FALSE, &wndrect );
	pTabCtrl->MoveWindow( &wndrect );

	CRect rect;
	pTabCtrl->GetItemRect(0, &rect);
	m_dialogClassInfo.SetWindowPos(NULL, rect.left, rect.bottom + 1,
		wndrect.right-wndrect.left-10, wndrect.bottom-wndrect.top-30, /*SWP_NOSIZE |*/ SWP_NOZORDER );
	m_dialogClassInfo.ShowWindow(SW_SHOW);

	return TRUE;
}