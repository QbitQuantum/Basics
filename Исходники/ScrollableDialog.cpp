void CScrollableDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* /*pScrollBar*/)
{
  // calc new y position
  int y = GetScrollPos(SB_VERT);
  int yOrig = y;

  switch (nSBCode)
  {
  case SB_TOP:
    y = 0;
    break;
  case SB_BOTTOM:
    y = INT_MAX;
    break;
  case SB_LINEUP:
    y -= 10;
    break;
  case SB_LINEDOWN:
    y += 10;
    break;
  case SB_PAGEUP:
    y -= 100;
    break;
  case SB_PAGEDOWN:
    y += 100;
    break;
  case SB_THUMBTRACK:
    y = nPos;
    break;
  }

  SetScrollPos(SB_VERT, y);

  y = GetScrollPos(SB_VERT);
  if (y != yOrig) {
    /* Now ScrollWindow(0, yOrig-y) is SUPPOSED to move all the child windows
       and in normal Win32 it does, but in WinCE it doesn't. All documentation
       says that it does, but to damn well DOESN'T. */
    for (CWnd * pChild = GetWindow(GW_CHILD); pChild != NULL; pChild = pChild->GetNextWindow(GW_HWNDNEXT)) {
      CRect rect;
      pChild->GetWindowRect(&rect);
	  ScreenToClient(&rect);
	  pChild->SetWindowPos(NULL, rect.left, rect.top+(yOrig-y), 0, 0, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
    }
  }
}