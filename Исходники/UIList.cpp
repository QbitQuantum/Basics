bool CListUI::SelectItem(int iIndex)
{
   if( iIndex == m_iCurSel ) return true;
   // We should first unselect the currently selected item
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = GetItem(m_iCurSel);
      if( pControl != NULL ) {
         IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
         if( pListItem != NULL ) pListItem->Select(false);
      }
   }
   // Now figure out if the control can be selected
   // TODO: Redo old selected if failure
   CControlUI* pControl = GetItem(iIndex);
   if( pControl == NULL ) return false;
   if( !pControl->IsVisible() ) return false;
   if( !pControl->IsEnabled() ) return false;
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem == NULL ) return false;
   m_iCurSel = iIndex;
   if( !pListItem->Select(true) ) {
      m_iCurSel = -1;
      return false;
   }
   pControl->SetFocus();
   if( m_pManager != NULL ) {
      m_pManager->SendNotify(pControl, _T("itemclick"));
      m_pManager->SendNotify(this, _T("itemselect"));
   }
   Invalidate();
   return true;
}