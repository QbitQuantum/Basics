BOOL CSetDBID::OnInitDialog()
{
  CPWDialog::OnInitDialog();

  // Trying to get our icon to get background colour (failed when System Tray
  // icon created in ThisMafApp as too early - no main dialog HWND).
  // Windows 10 default is black but Windows 7 seems to be white
  NOTIFYICONIDENTIFIER nii = { sizeof(nii) };
  nii.hWnd = m_pParent->GetSafeHwnd();
  nii.uID = PWS_MSG_ICON_NOTIFY;
  nii.guidItem = GUID_NULL;
  RECT rcIcon;
  HRESULT hr = Shell_NotifyIconGetRect(&nii, &rcIcon);

  COLORREF clr = (COLORREF)-1;
  if (SUCCEEDED(hr)) {
    CWnd *pWnd = CWnd::GetDesktopWindow();
    CDC *pDC = pWnd->GetDC();
    clr = pDC->GetPixel(rcIcon.right + 1, rcIcon.top + 1);
    pws_os::Trace(L"clr: %06x; R=%d; G=%d; B=%d\n", clr, GetRValue(clr), GetGValue(clr), GetBValue(clr));
    clr = RGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
    ReleaseDC(pDC);
  }

  m_clrBackground = (clr != (COLORREF)-1) ? clr : GetSysColor(COLOR_BACKGROUND);

  m_Brush.CreateSolidBrush(m_clrBackground);

  VERIFY(m_bmLocked.Attach(::LoadImage(
    ::AfxFindResourceHandle(MAKEINTRESOURCE(IDB_LOCKED_TRAY_INDEX), RT_BITMAP),
    MAKEINTRESOURCE(IDB_LOCKED_TRAY_INDEX), IMAGE_BITMAP, 0, 0,
                                    (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

  VERIFY(m_bmUnlocked.Attach(::LoadImage(
    ::AfxFindResourceHandle(MAKEINTRESOURCE(IDB_UNLOCKED_TRAY_INDEX), RT_BITMAP),
    MAKEINTRESOURCE(IDB_UNLOCKED_TRAY_INDEX), IMAGE_BITMAP, 0, 0,
                                    (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

  SetBitmapBackground(m_bmLocked);
  SetBitmapBackground(m_bmUnlocked);

  m_clrLockedTextColour = m_pParent->GetLockedIndexColour();
  m_clrUnlockedTextColour = m_pParent->GetUnlockedIndexColour();

  for (int i = 0; i < 4; i++) {
    if (m_clrLockedTextOptions[i] == m_clrLockedTextColour) {
      m_iLockedTextColour = i;
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    if (m_clrUnlockedTextOptions[i] == m_clrUnlockedTextColour) {
      m_iUnLockedTextColour = i;
      break;
    }
  }

  CreateIndexBitmap(55, m_clrLockedTextColour, true);
  CreateIndexBitmap(55, m_clrUnlockedTextColour, false);

  // Index if between 1 & 99
  m_edtSBIndex.SetLimitText(2);

  UpdateData(FALSE);

  GotoDlgCtrl((CWnd *)&m_edtSBIndex);

  m_bInitDone = true;

  return FALSE;  // return TRUE unless you set the focus to a control
}