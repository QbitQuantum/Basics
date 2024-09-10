void CEsmRefCellPage::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pPopup;
  BOOL   Result;
  CCmdUI MenuState;
  int    Index;

	/* Get the popup menu to display */
  Result = Menu.LoadMenu(IDR_CELLREF_MENU);
  if (!Result) return;
  pPopup = Menu.GetSubMenu(0);
  if (pPopup == NULL) return;

  	/* Force the update of the menu commands */
  for (Index = 0; Index < (int) pPopup->GetMenuItemCount(); Index++) {
    MenuState.m_nID = pPopup->GetMenuItemID(Index);
    MenuState.m_nIndex = Index;
    MenuState.m_pMenu = pPopup;
    MenuState.m_pOther = NULL;
    MenuState.m_pSubMenu = NULL;
    MenuState.m_nIndexMax = pPopup->GetMenuItemCount();

    if (MenuState.m_nID != 0) {
      OnCmdMsg(MenuState.m_nID, CN_UPDATE_COMMAND_UI, &MenuState, NULL);
     }
   }
  
  if (pWnd->GetDlgCtrlID() == IDC_OBJECTLIST) {
    pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, Point.x, Point.y, this);
   }

 }