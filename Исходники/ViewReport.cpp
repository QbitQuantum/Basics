BOOL CViewReport::OnInitDialog()
{
  std::vector<UINT> vibottombtns;
  vibottombtns.push_back(IDOK);
  vibottombtns.push_back(IDC_REPORT2CLIPBOARD);
  vibottombtns.push_back(IDCANCEL);

  AddMainCtrlID(IDC_EDITREPORT);
  AddBtnsCtrlIDs(vibottombtns, 2);

  UINT statustext[1] = {IDS_BLANK};
  SetStatusBar(&statustext[0], 1, false);

  CPWResizeDialog::OnInitDialog();

  if (GetParent() == NULL)
    GetDlgItem(IDC_REPORT2CLIPBOARD)->EnableWindow(FALSE);

  // Get new edit string (as per MS doc.)
  HLOCAL h = ::LocalAlloc(LHND, m_dwDatasize + sizeof(wchar_t));
  if (h == NULL) {
    pws_os::Trace(L"ViewReport: Unable to allocate memory.  Can't do this properly!\n");
    m_editreport.SetWindowText(m_pString.c_str());
    return FALSE;
  }
  m_bMemoryAllocOK = true;

  LPCWSTR lpszText = (LPCWSTR)::LocalLock(h);
  memcpy((void *)lpszText, m_pString.c_str(), m_dwDatasize);

  // Now work out maximum size of dialog
  CClientDC dc(GetDlgItem(IDC_EDITREPORT));

  //get the size of the text
  CRect textRect(0, 0, 32767, 32767);
  CFont *pOldFont = dc.SelectObject(m_editreport.GetFont());

  // Get Height
  dc.DrawText(lpszText, (int)m_pString.length(), &textRect, DT_CALCRECT | DT_NOCLIP);

  // Get width of longest line - ignores tabs - but no issue as edit control has
  // horizontal scroll bars
  wchar_t pSeps[] = L"\r\n";
  int iMaxWidth(-1);
  // Capture individual lines:
  wchar_t *next_token;
  wchar_t *token = wcstok_s((LPWSTR)lpszText, pSeps, &next_token);
  while(token) {
    CSize sz = dc.GetTextExtent(token, (int)wcslen(token));
    if (sz.cx > iMaxWidth)
      iMaxWidth = sz.cx;
    token = wcstok_s(NULL, pSeps, &next_token);
  }

  dc.SelectObject(pOldFont);

  //get the size of the edit control and the dialog
  CRect editRect, dlgRect;
  m_editreport.GetClientRect(&editRect);
  GetClientRect(&dlgRect);

  // Get height and width of characters
  TEXTMETRIC tm;
  dc.GetTextMetrics(&tm);

  // Set size based on current size (add spare in case)
  int iAdditionalHeight(0), iAdditionalWidth(0);
  if (iMaxWidth > editRect.Width())
    iAdditionalWidth = (iMaxWidth - editRect.Width()) + 2 * tm.tmMaxCharWidth;
  if (textRect.Height() > editRect.Height())
    iAdditionalHeight = (textRect.Height() - editRect.Height()) + 2 * tm.tmHeight;

  // Set it
  SetMaxHeightWidth(dlgRect.Height() + iAdditionalHeight, 
                    dlgRect.Width()  + iAdditionalWidth);

  // Refresh data as _wcstok trashes it!
  memcpy((void *)lpszText, m_pString.c_str(), m_dwDatasize);
  ::LocalUnlock(h);

  // Free original handle
  ::LocalFree(m_editreport.GetHandle());
  // Set ours
  m_editreport.SetHandle(h);

  return FALSE;
}