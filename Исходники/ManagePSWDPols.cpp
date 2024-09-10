void CManagePSWDPols::OnPolicyRightClick(NMHDR * /*pNotifyStruct*/, LRESULT *pLResult)
{
  *pLResult = 0; // Perform default processing on return
  POSITION pos = m_PolicyNames.GetFirstSelectedItemPosition();

  if (pos == NULL)
    return;

  int nItem = m_PolicyNames.GetNextSelectedItem(pos);

  // Ignore is default policy (first entry)
  if (nItem == 0)
    return;

  const StringX sxPolicyName = m_PolicyNames.GetItemText(nItem, 0);

  // Ignore if no entries using this policy
  if (m_MapPSWDPLC[sxPolicyName].usecount == 0)
    return;

  PWScore *pcore = (PWScore *)GetMainDlg()->GetCore();
  m_ventries.clear();
  // Ignore if can't find any even if there should be!
  if (!pcore->GetEntriesUsingNamedPasswordPolicy(sxPolicyName, m_ventries))
    return;

  CPoint msg_pt = ::GetMessagePos();
  CMenu menu;
  int ipopup = IDR_POPLISTENTRIES;

  if (menu.LoadMenu(ipopup)) {
    MENUINFO minfo = { 0 };
    minfo.cbSize = sizeof(MENUINFO);
    minfo.fMask = MIM_MENUDATA;
    minfo.dwMenuData = ipopup;
    BOOL brc = menu.SetMenuInfo(&minfo);
    ASSERT(brc != 0);

    CMenu *pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, msg_pt.x, msg_pt.y, this);
  }
}