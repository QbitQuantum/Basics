void ImagedButton::drawItem(LPDRAWITEMSTRUCT dis)
{
  HDC dc = dis->hDC;

  BOOL isPressed = (dis->itemState & ODS_SELECTED);
  BOOL isFocused = (dis->itemState & ODS_FOCUS);
  BOOL isDisabled = (dis->itemState & ODS_DISABLED);
  BOOL drawFocusRect = !(dis->itemState & ODS_NOFOCUSRECT);

  RECT itemRect = dis->rcItem;
  SetBkMode(dc, TRANSPARENT);

  if (m_isUsingTheme) {
    DWORD state = (isPressed) ? PBS_PRESSED : PBS_NORMAL;
    if (state == PBS_NORMAL) {
      if (isFocused) {
        state = PBS_DEFAULTED;
      } 
      if (m_mouseOver) {
        state = PBS_HOT;
      } 
      if (isDisabled) {
        state = PBS_DISABLED;
      }
    } 
    ThemeLib::DrawThemeBackground(m_theme, dc, BP_PUSHBUTTON, state, &itemRect, NULL);
  } else {
    if (isFocused) {
      HBRUSH br = CreateSolidBrush(RGB(0,0,0));
      FrameRect(dc, &itemRect, br);
      InflateRect(&itemRect, -1, -1);
      DeleteObject(br);
    } 

    HBRUSH background = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
    FillRect(dc, &itemRect, background);
    DeleteObject(background);

    if (isPressed) {
      HBRUSH shadow = CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
      FrameRect(dc, &itemRect, shadow);
      DeleteObject(shadow);
    } else {
      UINT uState = DFCS_BUTTONPUSH |
                    ((m_mouseOver) ? DFCS_HOT : 0) |
                    ((isPressed) ? DFCS_PUSHED : 0);

      DrawFrameControl(dc, &itemRect, DFC_BUTTON, uState);
    } 
  } 

  StringStorage title;
  getText(&title);

  RECT captionRect = dis->rcItem;

  TEXTMETRIC metric;
  GetTextMetrics(dc, &metric);

  RECT imageRect;

  calcRect(&itemRect, isPressed == TRUE, 0, metric.tmHeight,
           m_iconWidth, m_iconHeight, &captionRect, &imageRect);

  if (m_icon != NULL) {
    drawIcon(&dc, &imageRect, isPressed == TRUE, isDisabled == TRUE);
  }

  if (!title.isEmpty()) {
    if (isPressed && !m_isUsingTheme) {
      OffsetRect(&captionRect, 1, 1);
    }

    if (m_isUsingTheme) {
      WCHAR *unicodeString = new WCHAR[title.getLength() + 1];
      size_t len = title.getLength();
      title.toUnicodeString(unicodeString, &len);

      DWORD state = PBS_NORMAL;

      if (isDisabled) {
        state = PBS_DISABLED;
      }

      ThemeLib::DrawThemeText(m_theme, dc, BP_PUSHBUTTON, state,
                              unicodeString, len,
                              DT_CENTER | DT_VCENTER | DT_SINGLELINE,
                              0, &captionRect);
      delete[] unicodeString;
    } else {
      SetBkMode(dc, TRANSPARENT);

      if (isDisabled) {
        OffsetRect(&captionRect, 1, 1);
        SetTextColor(dc, ::GetSysColor(COLOR_3DHILIGHT));
        DrawText(dc, title.getString(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
        OffsetRect(&captionRect, -1, -1);
        SetTextColor(dc, ::GetSysColor(COLOR_3DSHADOW));
        DrawText(dc, title.getString(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
      } else {
        SetTextColor(dc, ::GetSysColor(COLOR_BTNTEXT));
        SetBkColor(dc, ::GetSysColor(COLOR_BTNFACE));
        DrawText(dc, title.getString(), -1, &captionRect, DT_WORDBREAK | DT_CENTER);
      } 
    } 
  } 

  if (isFocused && drawFocusRect) {
    RECT focusRect = itemRect;
    InflateRect(&focusRect, -3, -3);
    DrawFocusRect(dc, &focusRect);
  } 
} 