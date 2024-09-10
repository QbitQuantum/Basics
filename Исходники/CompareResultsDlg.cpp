void CCompareResultsDlg::OnItemRightClick(NMHDR *pNMHDR, LRESULT *pLResult)
{
  *pLResult = 0; // Perform default processing on return

  NMLISTVIEW *pNMLV = (NMLISTVIEW *)pNMHDR;

  m_LCResults.SetRow(pNMLV->iItem);

  CPoint msg_pt = ::GetMessagePos();
  CMenu menu;
  int ipopup;
  bool bTargetRO(true), bSourceRO(true);

  if (m_LCResults.GetSelectedCount() != 1) {
    // Special processing - only allow "Copy All" items to original or 
    // "Synchronise All" items to original
    // Do not allow "Synchronise All" is any selected entry does not
    // have a corresponding entry in the original DB
    // No point if original is R-O - is checked in OnItemChanging()
    m_LCResults.SetColumn(COMPARE);
    ipopup = IDR_POPCOPYALLTOORIGINAL;
    bTargetRO = m_bOriginalDBReadOnly;
    bSourceRO = m_bComparisonDBReadOnly;
    
    bool bNoSyncAll(false);
    POSITION pos = m_LCResults.GetFirstSelectedItemPosition();

    while (pos) {
      const int irow = m_LCResults.GetNextSelectedItem(pos);
      DWORD_PTR dwItemData = m_LCResults.GetItemData(irow);
      st_CompareData *pst_data = GetCompareData(dwItemData);
      ASSERT(pst_data != NULL);
      if (pst_data->uuid0 == pws_os::CUUID::NullUUID() || pst_data->indatabase != BOTH) {
        bNoSyncAll = true;
        break;
      }
    }

    if (menu.LoadMenu(ipopup)) {
      MENUINFO minfo ={0};
      minfo.cbSize = sizeof(MENUINFO);
      minfo.fMask = MIM_MENUDATA;
      minfo.dwMenuData = ipopup;
      BOOL brc = menu.SetMenuInfo(&minfo);
      ASSERT(brc != 0);

      CMenu *pPopup = menu.GetSubMenu(0);
      ASSERT(pPopup != NULL);
      
      if (bNoSyncAll)
        pPopup->RemoveMenu(ID_MENUITEM_SYNCHRONIZEALL, MF_BYCOMMAND);

      pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, msg_pt.x, msg_pt.y, this);
    }
    return;
  }

  switch (pNMLV->iSubItem) {
    case 0:
      // Column is the current database
      // Therefore: Source = Current DB, Target = Comparison DB
      m_LCResults.SetColumn(CURRENT);
      ipopup = IDR_POPEDITVIEWORIGINAL;
      bTargetRO = m_bComparisonDBReadOnly;
      bSourceRO = m_bOriginalDBReadOnly;
      break;
    case 1:
      // Column is the comparison database
      // Therefore: Source = Comparison DB, Target = Current DB
      m_LCResults.SetColumn(COMPARE);
      ipopup = IDR_POPCOPYTOORIGINAL;
      bTargetRO = m_bOriginalDBReadOnly;
      bSourceRO = m_bComparisonDBReadOnly;
      break;
    default:
      return;
  }

  DWORD_PTR dwItemData = m_LCResults.GetItemData(m_LCResults.GetRow());
  st_CompareData *pst_data = GetCompareData(dwItemData);
  ASSERT(pst_data != NULL);

  // Get where this entry is:
  // IDENTICAL means CURRENT + COMPARE but identical
  // BOTH      means CURRENT + COMPARE but with differences
  int indatabase = pst_data->indatabase;

  // If entry isn't in this database that the user click or the entry is only
  // in the other column - do nothing
  if (m_LCResults.GetColumn() != indatabase && 
      (indatabase != BOTH && indatabase != IDENTICAL))
    return;

  if (menu.LoadMenu(ipopup)) {
    MENUINFO minfo ={0};
    minfo.cbSize = sizeof(MENUINFO);
    minfo.fMask = MIM_MENUDATA;
    minfo.dwMenuData = ipopup;
    BOOL brc = menu.SetMenuInfo(&minfo);
    ASSERT(brc != 0);

    CMenu *pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    // Disable copy/sychnronize if target is read-only or entry is protected
    // Delete synchronize if not in both databases (and not already identical)
    if (m_LCResults.GetColumn() == COMPARE) {
      // User clicked on Comparison DB
      if (bTargetRO) {
        // Can't modify RO DB
        pPopup->RemoveMenu(ID_MENUITEM_COPY_TO_ORIGINAL, MF_BYCOMMAND);
        pPopup->RemoveMenu(ID_MENUITEM_SYNCHRONIZE, MF_BYCOMMAND);
      } else {
        // If it is in the current DB (i.e. BOTH as we know it is in the compare
        // column as the user has clicked on it) and is protected - don't allow copy
        if (indatabase == BOTH && pst_data->bIsProtected0)
          pPopup->RemoveMenu(ID_MENUITEM_COPY_TO_ORIGINAL, MF_BYCOMMAND);
      }
    }

    // Can't synchonize pr compare if not in both databases!
    if (indatabase != BOTH) {
      pPopup->RemoveMenu(ID_MENUITEM_SYNCHRONIZE, MF_BYCOMMAND);
      pPopup->RemoveMenu(ID_MENUITEM_COMPARE_ENTRIES, MF_BYCOMMAND);
    }

    // Change Edit to View if source read-only OR entry is protected OR if Comparison DB
    if (bSourceRO || pst_data->bIsProtected0) {
      const CString cs_View_Entry(MAKEINTRESOURCE(IDS_VIEWENTRY2));
      pPopup->ModifyMenu(ID_MENUITEM_COMPVIEWEDIT, MF_BYCOMMAND,
                         ID_MENUITEM_COMPVIEWEDIT, cs_View_Entry);
    }

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, msg_pt.x, msg_pt.y, this);
  }
}