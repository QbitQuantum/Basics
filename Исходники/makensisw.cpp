INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG:
    {
      g_sdata.hwnd=hwndDlg;
      HICON hIcon = LoadIcon(g_sdata.hInstance,MAKEINTRESOURCE(IDI_ICON));
      SetClassLongPtr(hwndDlg,GCLP_HICON,(LONG_PTR)hIcon);
      // Altered by Darren Owen (DrO) on 29/9/2003
      // Added in receiving of mouse and key events from the richedit control
      SendMessage(GetDlgItem(hwndDlg,IDC_LOGWIN),EM_SETEVENTMASK,(WPARAM)NULL,ENM_SELCHANGE|ENM_MOUSEEVENTS|ENM_KEYEVENTS);
      DragAcceptFiles(g_sdata.hwnd,FALSE);
      g_sdata.menu = GetMenu(g_sdata.hwnd);
      g_sdata.fileSubmenu = FindSubMenu(g_sdata.menu, IDM_FILE);
      g_sdata.editSubmenu = FindSubMenu(g_sdata.menu, IDM_EDIT);
      g_sdata.toolsSubmenu = FindSubMenu(g_sdata.menu, IDM_TOOLS);
      RestoreMRUList();
      CreateToolBar();
      InitTooltips(g_sdata.hwnd);
      SetDlgItemText(g_sdata.hwnd,IDC_VERSION,g_sdata.branding);
      HFONT hFont = CreateFont(14,FW_NORMAL,FIXED_PITCH|FF_DONTCARE,_T("Courier New"));
      SendDlgItemMessage(hwndDlg,IDC_LOGWIN,WM_SETFONT,(WPARAM)hFont,0);
      RestoreWindowPos(g_sdata.hwnd);
      RestoreCompressor();
      SetScript(_T(""));
      g_sdata.compressor = COMPRESSOR_NONE_SELECTED;
      g_sdata.userSelectCompressor = FALSE;

      ProcessCommandLine();

      if(g_sdata.compressor == COMPRESSOR_NONE_SELECTED) {
        SetCompressor(g_sdata.default_compressor);
      }

      if(g_sdata.userSelectCompressor) {
        if (DialogBox(g_sdata.hInstance,MAKEINTRESOURCE(DLG_COMPRESSOR),g_sdata.hwnd,(DLGPROC)CompressorProc)) {
          EnableItems(g_sdata.hwnd);
          return TRUE;
        }
      }

      CompileNSISScript();
      return TRUE;
    }
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      GetGripperPos(hwndDlg, g_resize.griprect);
      HDC hdc = BeginPaint(hwndDlg, &ps);
      DrawFrameControl(hdc, &g_resize.griprect, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
      EndPaint(hwndDlg, &ps);
      return TRUE;
    }
    case WM_DESTROY:
    {
      DragAcceptFiles(g_sdata.hwnd,FALSE);
      SaveSymbols();
      SaveCompressor();
      SaveMRUList();
      SaveWindowPos(g_sdata.hwnd);
      ImageList_Destroy(g_toolbar.imagelist);
      ImageList_Destroy(g_toolbar.imagelistd);
      ImageList_Destroy(g_toolbar.imagelisth);
      DestroyTooltips();
      PostQuitMessage(0);
      return TRUE;
    }
    case WM_CLOSE:
    {
      if (!g_sdata.thread) {
        DestroyWindow(hwndDlg);
      }
      return TRUE;
    }
    case WM_DROPFILES: {
      int num;
      TCHAR szTmp[MAX_PATH];
      num = DragQueryFile((HDROP)wParam,(UINT)-1,NULL,0);
      if (num==1) {
        DragQueryFile((HDROP)wParam,0,szTmp,MAX_PATH);
        if (lstrlen(szTmp)>0) {
          SetScript(szTmp);
          PushMRUFile(g_sdata.script);
          ResetObjects();
          CompileNSISScript();
        }
      } else {
        MessageBox(hwndDlg,MULTIDROPERROR,ERRBOXTITLE,MB_OK|MB_ICONSTOP);
      }
      DragFinish((HDROP)wParam);
      break;
    }
    case WM_GETMINMAXINFO:
    {
      ((MINMAXINFO*)lParam)->ptMinTrackSize.x=MINWIDTH;
      ((MINMAXINFO*)lParam)->ptMinTrackSize.y=MINHEIGHT;
    }
    case WM_ENTERSIZEMOVE:
    {
      GetClientRect(g_sdata.hwnd, &g_resize.resizeRect);
      return TRUE;
    }
    case WM_SIZE:
    {
      if ((wParam == SIZE_MAXHIDE)||(wParam == SIZE_MAXSHOW)) return TRUE;
      RECT rSize;
      if (hwndDlg == g_sdata.hwnd) {
        GetClientRect(g_sdata.hwnd, &rSize);
        if (((rSize.right==0)&&(rSize.bottom==0))||((g_resize.resizeRect.right==0)&&(g_resize.resizeRect.bottom==0)))  return TRUE;
        g_resize.dx = rSize.right - g_resize.resizeRect.right;
        g_resize.dy = rSize.bottom - g_resize.resizeRect.bottom;
        EnumChildWindows(g_sdata.hwnd, DialogResize, (LPARAM)0);
        g_resize.resizeRect = rSize;
      }
      return TRUE;
    }
    case WM_SIZING:
    {
      InvalidateRect(hwndDlg, &g_resize.griprect, TRUE);
      GetGripperPos(hwndDlg, g_resize.griprect);
      return TRUE;
    }
    case WM_NCHITTEST:
    {
      RECT r = g_resize.griprect;
      MapWindowPoints(hwndDlg, 0, (POINT*)&r, 2);
      POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
      if (PtInRect(&r, pt))
      {
        SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, HTBOTTOMRIGHT);
        return TRUE;
      }
      return FALSE;
    }
    case WM_MAKENSIS_PROCESSCOMPLETE:
    {
      if (g_sdata.thread) {
        CloseHandle(g_sdata.thread);
        g_sdata.thread=0;
      }
      if(g_sdata.compressor == COMPRESSOR_BEST) {
        if (g_sdata.retcode==0 && FileExists(g_sdata.output_exe)) {
          TCHAR temp_file_name[1024]; // BUGBUG: Hardcoded buffer size
          wsprintf(temp_file_name,_T("%s_makensisw_temp"),g_sdata.output_exe);
          if(!lstrcmpi(g_sdata.compressor_name,compressor_names[(int)COMPRESSOR_SCRIPT+1])) {
            SetCompressorStats();
            CopyFile(g_sdata.output_exe,temp_file_name,false);
            g_sdata.best_compressor_name = g_sdata.compressor_name;
            g_sdata.compressor_name = compressor_names[(int)COMPRESSOR_SCRIPT+2];
            ResetObjects();

            CompileNSISScript();
            return TRUE;
          }
          else {
            int this_compressor=0;
            int i;
            HANDLE hPrev, hThis;
            DWORD prevSize=0, thisSize=0;


            for(i=(int)COMPRESSOR_SCRIPT+2; i<(int)COMPRESSOR_BEST; i++) {
              if(!lstrcmpi(g_sdata.compressor_name,compressor_names[i])) {
                this_compressor = i;
                break;
              }
            }

            if(FileExists(temp_file_name)) {
              hPrev = CreateFile(temp_file_name,GENERIC_READ, FILE_SHARE_READ,
                                 NULL, OPEN_EXISTING, (DWORD)NULL, NULL);
              if(hPrev != INVALID_HANDLE_VALUE) {
                prevSize = GetFileSize(hPrev, 0);
                CloseHandle(hPrev);

                if(prevSize != INVALID_FILE_SIZE) {
                  hThis = CreateFile(g_sdata.output_exe,GENERIC_READ, FILE_SHARE_READ,
                                     NULL, OPEN_EXISTING, (DWORD)NULL, NULL);
                  if(hThis != INVALID_HANDLE_VALUE) {
                    thisSize = GetFileSize(hThis, 0);
                    CloseHandle(hThis);

                    if(thisSize != INVALID_FILE_SIZE) {
                      if(prevSize > thisSize) {
                        CopyFile(g_sdata.output_exe,temp_file_name,false);
                        SetCompressorStats();
                        g_sdata.best_compressor_name = g_sdata.compressor_name;
                      }
                    }
                  }
                }
              }
            }

            if(this_compressor == ((int)COMPRESSOR_BEST - 1)) {
              TCHAR buf[1024];

              g_sdata.compressor_name = compressor_names[(int)COMPRESSOR_SCRIPT+1];

              if(!lstrcmpi(g_sdata.best_compressor_name,compressor_names[this_compressor])) {
                wsprintf(buf,COMPRESSOR_MESSAGE,g_sdata.best_compressor_name,thisSize);
                LogMessage(g_sdata.hwnd,buf);
              }
              else {
                CopyFile(temp_file_name,g_sdata.output_exe,false);
                wsprintf(buf,RESTORED_COMPRESSOR_MESSAGE,g_sdata.best_compressor_name,prevSize);
                LogMessage(g_sdata.hwnd,buf);
                LogMessage(g_sdata.hwnd, g_sdata.compressor_stats);
              }
              DeleteFile(temp_file_name);
              lstrcpy(g_sdata.compressor_stats,_T(""));
            }
            else {
              g_sdata.compressor_name = compressor_names[this_compressor+1];
              ResetObjects();

              CompileNSISScript();
              return TRUE;
            }
          }
        }
      }
      EnableItems(g_sdata.hwnd);
      if (!g_sdata.retcode) {
        MessageBeep(MB_ICONASTERISK);
        if (g_sdata.warnings)
          SetTitle(g_sdata.hwnd,_T("Finished with Warnings"));
        else
          SetTitle(g_sdata.hwnd,_T("Finished Sucessfully"));
        // Added by Darren Owen (DrO) on 1/10/2003
        if(g_sdata.recompile_test)
          PostMessage(g_sdata.hwnd, WM_COMMAND, LOWORD(IDC_TEST), 0);
      }
      else {
        MessageBeep(MB_ICONEXCLAMATION);
        SetTitle(g_sdata.hwnd,_T("Compile Error: See Log for Details"));
      }

      // Added by Darren Owen (DrO) on 1/10/2003
      // ensures the recompile and run state is reset after use
      g_sdata.recompile_test = 0;
      DragAcceptFiles(g_sdata.hwnd,TRUE);
      return TRUE;
    }
    case MakensisAPI::QUERYHOST: {
      if (MakensisAPI::QH_OUTPUTCHARSET) {
        const UINT reqcp = 1200; // We want UTF-16LE
        SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, (LONG_PTR)(1+reqcp));
        return TRUE;
      }
      return FALSE;
    }
    case WM_NOTIFY:
      switch (((NMHDR*)lParam)->code ) {
        case EN_SELCHANGE:
          SendDlgItemMessage(hwndDlg,IDC_LOGWIN, EM_EXGETSEL, 0, (LPARAM) &g_sdata.textrange);
          {
            BOOL enabled = (g_sdata.textrange.cpMax-g_sdata.textrange.cpMin<=0?FALSE:TRUE);
            EnableMenuItem(g_sdata.menu,IDM_COPYSELECTED,(enabled?MF_ENABLED:MF_GRAYED));
            EnableToolBarButton(IDM_COPY,enabled);
          }
        // Altered by Darren Owen (DrO) on 6/10/2003
        // Allows the detection of the right-click menu when running on OSes below Windows 2000
        // and will then simulate the effective WM_CONTEXTMENU message that would be received
        // note: removed the WM_CONTEXTMENU handling to prevent a duplicate menu appearing on
        // Windows 2000 and higher
        case EN_MSGFILTER:
          #define lpnmMsg ((MSGFILTER*)lParam)
          if(WM_RBUTTONUP == lpnmMsg->msg || (WM_KEYUP == lpnmMsg->msg && lpnmMsg->wParam == VK_APPS)){
          POINT pt;
          HWND edit = GetDlgItem(g_sdata.hwnd,IDC_LOGWIN);
          RECT r;
            GetCursorPos(&pt);

            // Added and altered by Darren Owen (DrO) on 29/9/2003
            // Will place the right-click menu in the top left corner of the window
            // if the application key is pressed and the mouse is not in the window
            // from here...
            ScreenToClient(edit, &pt);
            GetClientRect(edit, &r);
            if(!PtInRect(&r, pt))
              pt.x = pt.y = 0;
            MapWindowPoints(edit, HWND_DESKTOP, &pt, 1);
            TrackPopupMenu(g_sdata.editSubmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, 0, g_sdata.hwnd, 0);
          }
        case TBN_DROPDOWN:
        {
          LPNMTOOLBAR pToolBar = (LPNMTOOLBAR) lParam;
          if(pToolBar->hdr.hwndFrom == g_toolbar.hwnd && pToolBar->iItem == IDM_COMPRESSOR) {
            ShowToolbarDropdownMenu();
            return TBDDRET_DEFAULT;
          }
          else {
            return TBDDRET_NODEFAULT;
          }
        }
      }
      return TRUE;
    case WM_COPYDATA:
    {
      PCOPYDATASTRUCT cds = PCOPYDATASTRUCT(lParam);
      switch (cds->dwData) {
        case MakensisAPI::NOTIFY_SCRIPT:
          MemSafeFree(g_sdata.input_script);
          g_sdata.input_script = (TCHAR*) MemAlloc(cds->cbData * sizeof(TCHAR));
          lstrcpy(g_sdata.input_script, (TCHAR *)cds->lpData);
          break;
        case MakensisAPI::NOTIFY_WARNING:
          g_sdata.warnings++;
          break;
        case MakensisAPI::NOTIFY_ERROR:
          break;
        case MakensisAPI::NOTIFY_OUTPUT:
          MemSafeFree(g_sdata.output_exe);
          g_sdata.output_exe = (TCHAR*) MemAlloc(cds->cbData * sizeof(TCHAR));
          lstrcpy(g_sdata.output_exe, (TCHAR *)cds->lpData);
          break;
      }
      return TRUE;
    }
    case WM_COMMAND:
    {
      switch (LOWORD(wParam)) {
        case IDM_BROWSESCR: {
          if (g_sdata.input_script) {
            TCHAR str[MAX_PATH],*str2;
            lstrcpy(str,g_sdata.input_script);
            str2=_tcsrchr(str,_T('\\'));
            if(str2!=NULL) *(str2+1)=0;
            ShellExecute(g_sdata.hwnd,_T("open"),str,NULL,NULL,SW_SHOWNORMAL);
          }
          return TRUE;
        }
        case IDM_ABOUT:
        {
          return DialogBox(g_sdata.hInstance,MAKEINTRESOURCE(DLG_ABOUT),hwndDlg,(DLGPROC)AboutProc);
        }
        case IDM_NSISHOME:
        {
          ShellExecuteA(g_sdata.hwnd,"open",NSIS_URL,NULL,NULL,SW_SHOWNORMAL);
          return TRUE;
        }
        case IDM_FORUM:
        {
          ShellExecuteA(g_sdata.hwnd,"open",NSIS_FOR,NULL,NULL,SW_SHOWNORMAL);
          return TRUE;
        }
        case IDM_NSISUPDATE:
        {
          Update();
          return TRUE;
        }
        case IDM_SELECTALL:
        {
          SendDlgItemMessage(g_sdata.hwnd, IDC_LOGWIN, EM_SETSEL, 0, -1);
          return TRUE;
        }
        case IDM_DOCS:
        {
          ShowDocs();
          return TRUE;
        }
        case IDM_LOADSCRIPT:
        {
          if (!g_sdata.thread) {
            OPENFILENAME l={sizeof(l),};
            TCHAR buf[MAX_PATH];
            l.hwndOwner = hwndDlg;
            l.lpstrFilter = _T("NSIS Script (*.nsi)\0*.nsi\0All Files (*.*)\0*.*\0");
            l.lpstrFile = buf;
            l.nMaxFile = MAX_STRING-1;
            l.lpstrTitle = _T("Load Script");
            l.lpstrDefExt = _T("log");
            l.lpstrFileTitle = NULL;
            l.lpstrInitialDir = NULL;
            l.Flags = OFN_HIDEREADONLY|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
            lstrcpy(buf,_T(""));
            if (GetOpenFileName(&l)) {
              SetScript(buf);
              PushMRUFile(g_sdata.script);
              ResetObjects();
              CompileNSISScript();
            }
          }
          return TRUE;
        }
        case IDM_MRU_FILE:
        case IDM_MRU_FILE+1:
        case IDM_MRU_FILE+2:
        case IDM_MRU_FILE+3:
        case IDM_MRU_FILE+4:
          LoadMRUFile(LOWORD(wParam)-IDM_MRU_FILE);
          return TRUE;
        case IDM_CLEAR_MRU_LIST:
          ClearMRUList();
          return TRUE;
        case IDM_COMPRESSOR:
        {
          SetCompressor((NCOMPRESSOR)(g_sdata.compressor+1));
          return TRUE;
        }
        case IDM_CLEARLOG:
        {
          if (!g_sdata.thread) {
            ClearLog(g_sdata.hwnd);
          }
          return TRUE;
        }
        case IDM_RECOMPILE:
        {
          CompileNSISScript();
          return TRUE;
        }
        // Added by Darren Owen (DrO) on 1/10/2003
        case IDM_RECOMPILE_TEST:
        {
          g_sdata.recompile_test = 1;
          CompileNSISScript();
          return TRUE;
        }
        case IDM_SETTINGS:
        {
          DialogBox(g_sdata.hInstance,MAKEINTRESOURCE(DLG_SETTINGS),g_sdata.hwnd,(DLGPROC)SettingsProc);
          return TRUE;
        }
        case IDM_TEST:
        case IDC_TEST:
        {
          if (g_sdata.output_exe) {
            ShellExecute(g_sdata.hwnd,_T("open"),g_sdata.output_exe,NULL,NULL,SW_SHOWNORMAL);
          }
          return TRUE;
        }
        case IDM_EDITSCRIPT:
        {
          if (g_sdata.input_script) {
            LPCTSTR verb = _T("open"); // BUGBUG: Should not force the open verb?
            HINSTANCE hi = ShellExecute(g_sdata.hwnd,verb,g_sdata.input_script,NULL,NULL,SW_SHOWNORMAL);
            if ((UINT_PTR)hi <= 32) {
              TCHAR path[MAX_PATH];
              if (GetWindowsDirectory(path,sizeof(path))) {
                lstrcat(path,_T("\\notepad.exe"));
                ShellExecute(g_sdata.hwnd,verb,path,g_sdata.input_script,NULL,SW_SHOWNORMAL);
              }
            }
          }
          return TRUE;
        }
        case IDCANCEL:
        case IDM_EXIT:
        {
          if (!g_sdata.thread) {
            DestroyWindow(g_sdata.hwnd);
          }
          return TRUE;
        }
        case IDM_CANCEL:
        {
          SetEvent(g_sdata.sigint_event);
          SetEvent(g_sdata.sigint_event_legacy);
          return TRUE;
        }
        case IDM_COPY:
        {
          CopyToClipboard(g_sdata.hwnd);
          return TRUE;
        }
        case IDM_COPYSELECTED:
        {
          SendDlgItemMessage(g_sdata.hwnd,IDC_LOGWIN, WM_COPY, 0, 0);
          return TRUE;
        }
        case IDM_SAVE:
        {
          OPENFILENAME l={sizeof(l),};
          TCHAR buf[MAX_STRING];
          l.hwndOwner = hwndDlg;
          l.lpstrFilter = _T("Log Files (*.log)\0*.log\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
          l.lpstrFile = buf;
          l.nMaxFile = MAX_STRING-1;
          l.lpstrTitle = _T("Save Output");
          l.lpstrDefExt = _T("log");
          l.lpstrInitialDir = NULL;
          l.Flags = OFN_HIDEREADONLY|OFN_EXPLORER|OFN_PATHMUSTEXIST;
          lstrcpy(buf,_T("output"));
          if (GetSaveFileName(&l)) {
            HANDLE hFile = CreateFile(buf,GENERIC_WRITE,0,0,CREATE_ALWAYS,0,0);
            if (INVALID_HANDLE_VALUE != hFile) {
              int len=SendDlgItemMessage(g_sdata.hwnd,IDC_LOGWIN,WM_GETTEXTLENGTH,0,0);
              TCHAR *existing_text=(TCHAR*) MemAlloc(len * sizeof(TCHAR));
              if (existing_text) { // BUGBUG:TODO: Error message for bad hFile and existing_text?
                existing_text[0]=0;
                GetDlgItemText(g_sdata.hwnd, IDC_LOGWIN, existing_text, len);
                DWORD dwWritten = 0;
                WriteFile(hFile,existing_text,len,&dwWritten,0);
                MemFree(existing_text);
              }
              CloseHandle(hFile);
            }
          }
          return TRUE;
        }
        case IDM_FIND:
        {
          if (!g_find.uFindReplaceMsg) g_find.uFindReplaceMsg = RegisterWindowMessage(FINDMSGSTRING);
          memset(&g_find.fr, 0, sizeof(FINDREPLACE));
          g_find.fr.lStructSize = sizeof(FINDREPLACE);
          g_find.fr.hwndOwner = hwndDlg;
          g_find.fr.Flags = FR_NOUPDOWN;
          g_find.fr.lpstrFindWhat = g_findbuf;
          g_find.fr.wFindWhatLen = COUNTOF(g_findbuf);
          g_find.hwndFind = FindText(&g_find.fr);
          return TRUE;
        }
        default:
          {
            int i;
            DWORD command = LOWORD(wParam);
            for(i=(int)COMPRESSOR_SCRIPT; i<=(int)COMPRESSOR_BEST; i++) {
              if(command == compressor_commands[i]) {
                SetCompressor((NCOMPRESSOR)i);
                return TRUE;
              }
            }
          }
      }
    }
  }
  if (g_find.uFindReplaceMsg && msg == g_find.uFindReplaceMsg) {
    LPFINDREPLACE lpfr = (LPFINDREPLACE)lParam;
    if (lpfr->Flags & FR_FINDNEXT) {
      WPARAM flags = FR_DOWN;
      if (lpfr->Flags & FR_MATCHCASE) flags |= FR_MATCHCASE;
      if (lpfr->Flags & FR_WHOLEWORD) flags |= FR_WHOLEWORD;
      FINDTEXTEX ft;
      SendDlgItemMessage(hwndDlg, IDC_LOGWIN, EM_EXGETSEL, 0, (LPARAM)&ft.chrg);
      if (ft.chrg.cpMax == ft.chrg.cpMin) ft.chrg.cpMin = 0;
      else ft.chrg.cpMin = ft.chrg.cpMax;
      ft.chrg.cpMax = SendDlgItemMessage(hwndDlg, IDC_LOGWIN, WM_GETTEXTLENGTH, 0, 0);
      ft.lpstrText = lpfr->lpstrFindWhat;
      ft.chrg.cpMin = SendDlgItemMessage(hwndDlg, IDC_LOGWIN, EM_FINDTEXTEX, flags, (LPARAM)&ft);
      if (ft.chrg.cpMin != -1) SendDlgItemMessage(hwndDlg, IDC_LOGWIN, EM_SETSEL, ft.chrgText.cpMin, ft.chrgText.cpMax);
      else MessageBeep(MB_ICONASTERISK);
    }
    if (lpfr->Flags & FR_DIALOGTERM) g_find.hwndFind = 0;
    return TRUE;
  }
  return 0;
}