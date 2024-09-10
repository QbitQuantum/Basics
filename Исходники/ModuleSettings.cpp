LRESULT CModuleSettings::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  std::wstring strWName;
  WinUTF8::UTF8string_to_wstring(m_strModuleName, strWName);
  SetWindowText(strWName.c_str());

  int iDlgWidth = 7 + CModuleControl::CAPTION_WIDTH + CModuleControl::CHILD_WIDTH + 7;
  int iTop = 7;

  for (int i(0); i < m_iCount; ++i) {
    RECT controlRect = { 7, iTop, iDlgWidth - 7, iTop + m_pControls[i]->GetHeight() };
    MapDialogRect(&controlRect);

    m_pControls[i]->Create(m_hWnd, controlRect);
    m_pControls[i]->Initialise(m_pAppSets);
    iTop += m_pControls[i]->GetHeight() + 2;
  }
  iTop += -2 + 7;

  MoveButton(IDCANCEL, iDlgWidth - 57, iTop);
  MoveButton(IDOK, iDlgWidth - 2 * (57), iTop);

  RECT size = { 0, 0, iDlgWidth, iTop + 14 + 7 };
  MapDialogRect(&size);
  ResizeClient(size.right, size.bottom);

  SendMessageToDescendants(WM_SETFONT, (WPARAM)GetFont(), true);
  return 1;
}