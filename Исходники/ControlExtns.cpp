void CButtonExtn::DrawButton(HWND hWnd, HDC hDC, RECT *pRect, BOOL fChecked, BOOL fHot, BOOL fFocus)
{
  // Code originally by Nikita Leontiev in answer to "Change checkBox text color Win32"
  // in MS's Forum: "Visual Studio Developer Center > Visual Studio vNext Forums > Visual C++ General"
  // Modified for MFC, Checkbox and Radio buttons by DK

  int nWidth = pRect -> right - pRect -> left;
  int nHeight = pRect -> bottom - pRect -> top;

  HDC hMemDC = CreateCompatibleDC(hDC);
  HBITMAP hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
  SelectObject(hMemDC, hBitmap);

  RECT rFillRect = {0, 0, nWidth, nHeight};

  HTHEME hTheme = OpenThemeData(hWnd, L"BUTTON");
  int nStateID(0);

  if (m_type == BS_AUTOCHECKBOX) {
    nStateID = (fChecked) ? CBS_CHECKEDNORMAL : CBS_UNCHECKEDNORMAL;
    if (fHot)
      nStateID = (fChecked) ? CBS_CHECKEDHOT : CBS_UNCHECKEDHOT;
  } else {
    nStateID = (fChecked) ? RBS_CHECKEDNORMAL : RBS_UNCHECKEDNORMAL;
    if (fHot)
      nStateID = (fChecked) ? RBS_CHECKEDHOT : RBS_UNCHECKEDHOT;
  }

  //If bg color isn't set, try get backgroung color from current theme
  if (m_bUseBkgColour) {
    FillRect(hMemDC, &rFillRect, CreateSolidBrush(GetSysColor(m_icolour)));
  }
  else { 
    // Don't check IsThemeBackgroundPartiallyTransparent because it return false for BP_CHECKBOX
    DrawThemeParentBackground(hWnd, hMemDC, &rFillRect);
  }

  RECT rIconRect = {0, 0, 13, nHeight};
  DrawThemeBackground(hTheme, hMemDC, m_type == BS_AUTOCHECKBOX ? BP_CHECKBOX : BP_RADIOBUTTON,
                      nStateID, &rIconRect, NULL);
  CloseThemeData(hTheme);

  RECT rTextRect = {16, 0, nWidth - 16, nHeight};
  SetBkMode(hMemDC, TRANSPARENT);
  if (m_bUseTextColour)
    SetTextColor(hMemDC, m_crfText);

  SelectObject(hMemDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));

  if (m_caption.IsEmpty()) {
    GetWindowText(m_caption);
    SetWindowText(L"");
  }

  DrawText(hMemDC, m_caption, m_caption.GetLength(), &rTextRect, DT_SINGLELINE | DT_VCENTER);

  if (fFocus){
    DrawText(hMemDC, m_caption, m_caption.GetLength(), &rTextRect, DT_SINGLELINE | DT_VCENTER | DT_CALCRECT);
    rTextRect.left--;
    rTextRect.right++;
    DrawFocusRect(hMemDC, &rTextRect);
  }

  BitBlt(hDC, 0, 0, nWidth, nHeight, hMemDC, 0, 0, SRCCOPY);

  DeleteObject(hBitmap);
  DeleteDC(hMemDC);
}