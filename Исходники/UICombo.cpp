bool CUIComboBox::SetCurSel(int iIndex)
{
   if( iIndex == m_iCurSel ) return true;
   if( m_iCurSel >= 0 ) {
      CUIControl* pControl = static_cast<CUIControl*>(m_items[m_iCurSel]);
      IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pListItem != NULL ) pListItem->Select(false);
      m_iCurSel = -1;
   }
   if( m_items.GetSize() == 0 ) return false;
   if( iIndex < 0 ) iIndex = 0;
   if( iIndex >= m_items.GetSize() ) iIndex = m_items.GetSize() - 1;
   CUIControl* pControl = static_cast<CUIControl*>(m_items[iIndex]);
   if( !pControl->IsVisible() ) return false;
   if( !pControl->IsEnabled() ) return false;
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem == NULL ) return false;
   m_iCurSel = iIndex;
   pControl->SetFocus();
   pListItem->Select(true);

   CUIContainer* pContainer = dynamic_cast<CUIContainer*>(pListItem->GetOwner());
   if (pContainer)
   {
	   RECT rcItem = pControl->GetPos();
	   RECT rcList = pContainer->GetPos();
	   int iPos = pContainer->GetScrollPos();
	   if( rcItem.top < rcList.top || rcItem.bottom > rcList.bottom )
	   {
		   int dx = 0;
		   if( rcItem.top < rcList.top ) dx = rcItem.top - rcList.top;
		   if( rcItem.bottom > rcList.bottom ) dx = rcItem.bottom - rcList.bottom;
			pContainer->SetScrollPos(pContainer->GetScrollPos() + dx);
	   }

   }

   Invalidate();
   return true;
}