LRESULT TStemDialog::DefStemDialogProc(HWND Win,UINT Mess,WPARAM wPar,LPARAM lPar)
{
  StemDialog_RetDefVal=0;
  TStemDialog *This;
  switch (Mess){
    case WM_SYSCOMMAND:
      switch (wPar){
        case SC_MONITORPOWER:
          if (runstate == RUNSTATE_RUNNING) return 0;
          break;
        case SC_SCREENSAVE:
          if (runstate == RUNSTATE_RUNNING || FullScreen) return 0;
          break;
      }
      break;
    case WM_MOVING:case WM_SIZING:
      if (FullScreen){
        RECT *rc=(RECT*)lPar;
        if (rc->top<MENUHEIGHT){
          if (Mess==WM_MOVING) rc->bottom+=MENUHEIGHT-rc->top;
          rc->top=MENUHEIGHT;
          StemDialog_RetDefVal=true;
          return true;
        }
        RECT LimRC={0,MENUHEIGHT+GetSystemMetrics(SM_CYFRAME),
                    GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN)};
        ClipCursor(&LimRC);
      }
      break;
    case WM_MOVE:
    {
      GET_THIS;

      RECT rc;
      GetWindowRect(Win,&rc);
      if (FullScreen){
        if (IsIconic(StemWin)==0 && IsZoomed(StemWin)==0){
          This->FSLeft=rc.left;This->FSTop=rc.top;
        }
      }else{
        if (IsIconic(Win)==0 && IsZoomed(Win)==0){
          This->Left=rc.left;This->Top=rc.top;
        }
      }
      break;
    }
    case WM_CAPTURECHANGED:   //Finished
      if (FullScreen) ClipCursor(NULL);
      break;
    case WM_ACTIVATE:
      if (wPar==WA_INACTIVE){
        GET_THIS;
        This->Focus=GetFocus();
      }else{
        if (IsWindowEnabled(Win)==0){
          PostMessage(StemWin,WM_USER,12345,(LPARAM)Win);
        }
      }
      break;
    case WM_SETFOCUS:
      GET_THIS;
      SetFocus(This->Focus);
      break;
  }
  return 0;
}