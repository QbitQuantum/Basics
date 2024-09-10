void SourceEdit::MoveShowSelect(CWnd* child)
{
  // Get the screen position of the selected word
  CRect wordR = GetSelectRect();

  // Get the size and position of the dialog
  CRect wndR;
  child->GetWindowRect(wndR);

  CRect extWndR;
  if (theOS.DwmGetWindowAttribute(child,
    DWMWA_EXTENDED_FRAME_BOUNDS,(LPRECT)extWndR,sizeof (RECT)))
  {
    // If Aero Glass or similar means that the windows frame extends
    // beyond the window bounds, work out by how much, and make sure that
    // the window is moved to avoid overlap by the extended frame.
    wordR.InflateRect(
      (extWndR.Width()-wndR.Width())/2,(extWndR.Height()-wndR.Height())/2);
  }

  // If the dialog is over the word, move it
  CRect intersectR;
  if (intersectR.IntersectRect(wordR,wndR))
  {
    // Get the size of the display
    MONITORINFO monInfo;
    ::ZeroMemory(&monInfo,sizeof monInfo);
    monInfo.cbSize = sizeof monInfo;
    HMONITOR mon = ::MonitorFromWindow(child->GetSafeHwnd(),MONITOR_DEFAULTTOPRIMARY);
    ::GetMonitorInfo(mon,&monInfo);

    // Try moving the dialog, but keep it on-screen
    if (wordR.top-wndR.Height() >= 0)
    {
      child->SetWindowPos(&CWnd::wndTop,wndR.left,wordR.top-wndR.Height(),0,0,
        SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_NOSIZE);
    }
    else if (wordR.bottom+wndR.Height() < monInfo.rcWork.bottom)
    {
      child->SetWindowPos(&CWnd::wndTop,wndR.left,wordR.bottom,0,0,
        SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_NOSIZE);
    }
  }
}