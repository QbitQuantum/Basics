void GEUIDialog::GEResize()
{
      LogDebugMessage(_T("GE resize requested"));
      //while ( m_bbusy ) ;
      if ( m_bbusy )
      {
            LogDebugMessage(_T("GE resize request discarded, busy"));
            return;
      }
      m_bbusy = true;
      if(NULL != app && m_bgeisuseable) 
      {
            LogDebugMessage(_T("Resizing GE"));
            try
            {
                  this->Layout();
                  //Calculate the window extents
                  RECT rect;
                  GetWindowRect((HWND) LongToHandle(app->GetMainHwnd()), &rect);
                  int mwidth, mheight, mx, my;
                  mwidth = rect.right - rect.left - 1;
                  mheight = rect.bottom - rect.top - 1;
                  mx = rect.left;
                  my = rect.top;
                  GetWindowRect((HWND) LongToHandle(app->GetRenderHwnd()), &rect);
                  int rwidth, rheight, rx, ry;
                  rwidth = rect.right - rect.left - 1;
                  rheight = rect.bottom - rect.top - 1;
                  rx = rect.left;
                  ry = rect.top;
                  int deltawidth = mwidth - rwidth;
                  int deltaheight = mheight - rheight;
                  wxSize panelsize = this->m_panel1->GetSize();
                  //Resize
                  SendMessage((HWND) LongToHandle(app->GetMainHwnd()), WM_COMMAND, WM_PAINT, 0);
                  PostMessage((HWND) LongToHandle(app->GetMainHwnd()), WM_QT_PAINT, 0, 0);

                  SetWindowPos(
                        (HWND) LongToHandle(app->GetMainHwnd()),
                        HWND_TOP,
                        0,
                        0,
                        panelsize.GetX() + deltawidth,
                        panelsize.GetY() + deltaheight,
                        SWP_FRAMECHANGED);

                  SendMessage((HWND) LongToHandle(app->GetRenderHwnd()), WM_COMMAND, WM_SIZE, 0);
                  LogDebugMessage(_T("GE resized"));
            }
            catch(...) {
                  LogDebugMessage(_T("Error resizing GE window"));
            }
      }
      m_bbusy = false;
}