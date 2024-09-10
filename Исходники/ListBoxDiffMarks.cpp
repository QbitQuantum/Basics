void CListBoxDiffMarks::substituteControl(CWnd *parent, int id) {
  DEFINEMETHODNAME;
  CListBox *oldCtrl = (CListBox*)parent->GetDlgItem(id);
  if(oldCtrl == NULL) {
    showError(_T("%s:Control with id=%d does not exist"), method, id);
    return;
  }
  CRect wr;
  oldCtrl->GetWindowRect(&wr);
  parent->ScreenToClient(&wr);
  DWORD style   = oldCtrl->GetStyle();
  const DWORD exStyle = oldCtrl->GetExStyle();
  style |= LBS_OWNERDRAWFIXED | WS_BORDER;
  style &= ~(LBS_SORT);

  CFont *font = oldCtrl->GetFont();
  if(font == NULL) {
    font = parent->GetFont();
  }
  const CompactIntArray tabOrder = getTabOrder(parent);
  oldCtrl->DestroyWindow();

  if(!Create(style, wr, parent, id)) {
    showError(_T("%s:Create failed"), method);
    return;
  }
  setTabOrder(parent, tabOrder);
  ModifyStyleEx(0, exStyle);
  SetFont(font);
  m_charSize.cx = m_charSize.cy = 0;
  setEqualSelected(::GetSysColor(COLOR_HIGHLIGHTTEXT),::GetSysColor(COLOR_HIGHLIGHT   ));
  setDiffSelected( ::GetSysColor(COLOR_HIGHLIGHT    ),::GetSysColor(COLOR_HIGHLIGHTTEXT));
}