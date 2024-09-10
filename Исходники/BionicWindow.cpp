HICON CBionicWindow::RefreshIcon()
  {
          //If window is closed, return the default icon.
      if(!IsWindow(m_hWinHwnd))
          return AfxGetApp()->LoadIcon(IDR_MAINFRAME);

      if(m_hIcon)
          return m_hIcon;

      if((m_hIcon = CopyIcon((HICON)::SendMessage(m_hWinHwnd,WM_GETICON,ICON_BIG,0))))
          return m_hIcon;

      if((m_hIcon = CopyIcon((HICON)::SendMessage(m_hWinHwnd,WM_GETICON,ICON_SMALL,0))))
          return m_hIcon;

      if((m_hIcon = CopyIcon((HICON)::GetClassLong(m_hWinHwnd,GCL_HICON))))
          return m_hIcon;

      if((m_hIcon = CopyIcon((HICON)::GetClassLong(m_hWinHwnd,GCL_HICONSM))))
          return m_hIcon;

//    if((m_hIcon = CopyIcon((HICON)::SendMessage(m_hWinHwnd,WM_GETICON,ICON_BIG,0)))   ||
//       (m_hIcon = CopyIcon((HICON)::SendMessage(m_hWinHwnd,WM_GETICON,ICON_SMALL,0))) ||
//       (m_hIcon = CopyIcon((HICON)::GetClassLong(m_hWinHwnd,GCL_HICON)))              ||
//       (m_hIcon = CopyIcon((HICON)::GetClassLong(m_hWinHwnd,GCL_HICONSM))))
//        return m_hIcon;

      m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); //If all else fails, use the default icon.
      m_bIconDefault = TRUE;
      return m_hIcon;
  }