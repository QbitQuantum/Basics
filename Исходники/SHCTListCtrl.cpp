void CSHCTListCtrl::OnRButtonDown(UINT , CPoint point)
{
  CMenu PopupMenu;
  MapMenuShortcutsIter iter;
  CString str;
  CPoint pt;
  int iSubItem = -1;

  SaveHotKey();

  LVHITTESTINFO lvhti;
  lvhti.pt = point;
  SubItemHitTest(&lvhti);

  m_item = lvhti.iItem;
  iSubItem = lvhti.iSubItem;

  if (m_item < 0 || iSubItem < 0) {
    // CListCtrl::OnRButtonDown(nFlags, point);
    goto exit;
  }

  m_id = (UINT)LOWORD(GetItemData(m_item));
  if (!m_pParent->GetMapMenuShortcutsIter(m_id, iter)) {
     goto exit;
  }

  PopupMenu.LoadMenu(IDR_POPRESETSHORTCUT);
  CMenu* pContextMenu = PopupMenu.GetSubMenu(0);
  if (iter->second.siVirtKey == 0)
    pContextMenu->RemoveMenu(ID_MENUITEM_REMOVESHORTCUT, MF_BYCOMMAND);

  if (iter->second.siVirtKey   == iter->second.siDefVirtKey &&
      iter->second.cModifier  == iter->second.cDefModifier)
    pContextMenu->RemoveMenu(ID_MENUITEM_RESETSHORTCUT, MF_BYCOMMAND);

  if (pContextMenu->GetMenuItemCount() == 0)
    goto exit;

  pt = point;
  ClientToScreen(&pt);

  int nID = pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD,
                                         pt.x, pt.y, this);

  if (nID == ID_MENUITEM_REMOVESHORTCUT) {
    iter->second.siVirtKey = 0;
    iter->second.cModifier = 0;
    str = L"";
    goto update;
  }

  if (nID != ID_MENUITEM_RESETSHORTCUT)
    goto exit;

  iter->second.siVirtKey = iter->second.siDefVirtKey;
  iter->second.cModifier = iter->second.cDefModifier;

  str = CMenuShortcut::FormatShortcut(iter);

update:
  SetItemText(m_item, SHCT_SHORTCUTKEYS, str);
  RedrawItems(m_item, m_item);
  UpdateWindow();

exit:
  if (m_pParent != NULL)
    m_pParent->ClearWarning();

  if (m_item >= 0)
    SetItemState(m_item, SHCT_SHORTCUTKEYS, LVIS_SELECTED | LVIS_DROPHILITED);
}