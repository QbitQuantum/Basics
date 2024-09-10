LRESULT CTransfersView::OnNmRClick(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
{
  /*
  int MenuID = -1;

  LVHITTESTINFO ht = {0};
  DWORD dwpos = GetMessagePos();
  POINT pt;
  pt.x = GET_X_LPARAM(dwpos);
  pt.y = GET_Y_LPARAM(dwpos);
  ht.pt.x = pt.x;
  ht.pt.y = pt.y;
  ::MapWindowPoints(HWND_DESKTOP, m_TransfersListCtrl.m_hWnd, &ht.pt, 1);
  m_TransfersListCtrl.HitTest(&ht);

  if(LVHT_ONITEM & ht.flags)
  {
    CDCCTransfer *pDCCTransfer = (CDCCTransfer *)m_TransfersListCtrl.GetItemData(ht.iItem);
    if (pDCCTransfer)
    {
      if (pDCCTransfer->m_Type == DCC_RECEIVE)
        MenuID = IDR_DCCRECEIVE_CONTEXT;
      else
        MenuID = IDR_DCCSEND_CONTEXT;
    }
  }

  // Display the menu at the current mouse location.
	CMenuHandle menuContext;
	menuContext.LoadMenu(MenuID);
	CMenuHandle menuPopup(menuContext.GetSubMenu(0));
  //menuPopup.SetMenuDefaultItem(0,TRUE);
  g_pMainWnd->m_CmdBar.TrackPopupMenu(menuPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y);
  */

  CDCCTransfer *pDCCTransfer;

  CMenuHandle Menu;
  Menu.CreatePopupMenu();

  // count how many selected items we have and make a note of
  // what type all the slected items are, and if we have more than
  // one type selected. (e.g. all DCC Sends, or mixed Sends and Receives)
  // and if they're all the same status, and what that status is.
  // and if they can all be retried.

  BOOL First = TRUE;
  int DCCType = DCC_ANY;
  int DCCStatus = DCCT_STATUS_UNKNOWN;
  BOOL DCCCanRetry = FALSE;

  int SelectedCount = 0;
  for (int i = 0 ; i < m_TransfersListCtrl.GetItemCount(); i ++)  
  {
    if (LVIS_SELECTED & m_TransfersListCtrl.GetItemState(i,LVIS_SELECTED))
    {
      SelectedCount++;
      pDCCTransfer = (CDCCTransfer *)m_TransfersListCtrl.GetItemData(i);

      if (!pDCCTransfer)
        continue;

      if (First)
      {
        // make a note of the first selected type
        DCCType = pDCCTransfer->m_Type;
        DCCStatus = pDCCTransfer->m_Status;
        DCCCanRetry = pDCCTransfer->m_CanRetry;
        First = FALSE;
      }
      else
      {
        // can they all be retried?
        if (pDCCTransfer->m_CanRetry != DCCCanRetry)

        // more than one type selected?
        if (pDCCTransfer->m_Type != DCCType)
        {
          DCCType = DCC_ANY;
          DCCStatus = DCCT_STATUS_UNKNOWN; 
        }
        else
        {
          // same type, but more than one status selected?
          if (pDCCTransfer->m_Status != DCCStatus)
            DCCStatus = DCCT_STATUS_UNKNOWN; 
        }
      }
    }
  }

  // Build the menu adding items based on what's selected
  if (SelectedCount > 0)
  {
//+ <gliptic> Accept option
    if (pDCCTransfer->m_Status == DCCT_STATUS_PENDING)
      Menu.AppendMenu(MF_STRING,TRMI_Accept,_T("&Accept"));
// </gliptic>

    if (!((pDCCTransfer->m_Status == DCCT_STATUS_ERROR) ||
         (pDCCTransfer->m_Status == DCCT_STATUS_COMPLETE)))
      Menu.AppendMenu(MF_STRING,TRMI_Cancel,_T("&Cancel"));

    if (DCCCanRetry)
      Menu.AppendMenu(MF_STRING,TRMI_Retry,_T("&Retry\tR"));

    Menu.AppendMenu(MF_STRING,TRMI_Remove,_T("R&emove"));

    Menu.AppendMenu(MF_SEPARATOR);
  }

  Menu.AppendMenu(MF_STRING,TRMI_CancelAllSends,    _T("Cancel All Sends"));
  Menu.AppendMenu(MF_STRING,TRMI_CancelAllReceives, _T("Cancel All Receives"));
  Menu.AppendMenu(MF_STRING,TRMI_CancelAll,         _T("Cancel All"));
  Menu.AppendMenu(MF_SEPARATOR);

  Menu.AppendMenu(MF_STRING,TRMI_RemoveAll,         _T("Remove All"));
  Menu.AppendMenu(MF_STRING,TRMI_RemoveAllCompleted,_T("Remove All Completed"));
  Menu.AppendMenu(MF_STRING,TRMI_RemoveAllFailed,   _T("Remove All Failed"));
  Menu.AppendMenu(MF_SEPARATOR);

  Menu.AppendMenu(MF_STRING,TRMI_SelectAll,         _T("Select All\tCtrl+A"));
  Menu.AppendMenu(MF_STRING,TRMI_SelectOnlyCompleted,_T("Select Only Completed"));
  Menu.AppendMenu(MF_STRING,TRMI_SelectOnlyFailed,   _T("Select Only Failed"));
  Menu.AppendMenu(MF_STRING,TRMI_SelectNone,        _T("Select &None"));

  POINT pt;
  ::GetCursorPos(&pt);      
  g_pMainWnd->m_CmdBar.TrackPopupMenu(Menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y);
  //::TrackPopupMenu(Menu, 0, pt.x, pt.y, 0, m_hWnd, NULL);

  return bHandled ? 1 : 0; // NM_RCLICK - Return nonzero to not allow the default processing, or zero to allow the default processing
  // or in otherwords, return zero to allow the default processing
  // or 1 if handled.
}