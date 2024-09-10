bool CGroupsUI::SelectItem(int iIndex, bool bTakeFocus)
{
	if( iIndex == m_iCurSel ) return true;

	// We should first unselect the currently selected item
	if( m_iCurSel >= 0 ) {
		CControlUI* pControl = GetItemAt(m_iCurSel);
		if( pControl != NULL) {
			IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
			if( pListItem != NULL )
			{
				CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
				Node* node = (Node*)pControl->GetTag();
				if ((pFriendListItem != NULL) && (node != NULL) && !node->folder())
				{
// 					pFriendListItem->SetFixedHeight(kFriendListItemNormalHeight);
// 					CContainerUI* pOperatorPannel = static_cast<CContainerUI*>(paint_manager_.FindSubControlByName(pFriendListItem, kOperatorPannelControlName));
// 					if (pOperatorPannel != NULL)
// 					{
// 						pOperatorPannel->SetVisible(false);
// 					}
				}
				pListItem->Select(false);
			}
		}

		m_iCurSel = -1;
	}

	if( iIndex < 0 )
		return false;

	if (!__super::SelectItem(iIndex, bTakeFocus))
		return false;

	CControlUI* pControl = GetItemAt(m_iCurSel);
	if( pControl != NULL) {
		CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
		Node* node = (Node*)pControl->GetTag();
		if ((pFriendListItem != NULL) && (node != NULL) && !node->folder())
		{
// 			pFriendListItem->SetFixedHeight(kFriendListItemSelectedHeight);
// 			CContainerUI* pOperatorPannel = static_cast<CContainerUI*>(paint_manager_.FindSubControlByName(pFriendListItem, kOperatorPannelControlName));
// 			if (pOperatorPannel != NULL)
// 			{
// 				pOperatorPannel->SetVisible(true);
// 			}
			//pFriendListItem->SetBkImage()
		}
	}
	return true;
}