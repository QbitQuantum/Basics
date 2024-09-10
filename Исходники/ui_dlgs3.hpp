int CALLBACK LongDialogProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam) {
    sDIALOG_long * dlg;
    HWND hwnd2;

    switch (message)
    {
    case WM_INITDIALOG:
        SetWindowPos(hwnd , HWND_TOP , 0 , 0 , 0 , 0 , SWP_NOMOVE | SWP_NOSIZE);
        dlg = (sDIALOG_long*)lParam;
        dlg->cancel = false;
        dlg->handle = hwnd;
        LongDialogProc(hwnd , MYWM_DLGLONGSET , 0 , lParam);
//                SetTimer(hwnd , 1 , 500 , (TIMERPROC)LongTimerProc);
//                SetProp(hwnd , "DLGTIMER" , timer);
        SendMessage(GetDlgItem(hwnd , IDC_PROGRESS) , PBM_SETRANGE32 , 0 , dlg->progress>0 ? dlg->progress : 100);
        if (dlg->progress > 0) dlg->progress = 0;
        break;
    case WM_CLOSE:
//                KillTimer(hwnd , 1);
//                timer = GetProp(hwnd , "DLGTIMER");
//                CancelWaitableTimer(timer);
//                CloseHandle(timer);
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        RemoveProp(hwnd , "DLG");
//                RemoveProp(hwnd , "DLGTIMER");
        break;
    case MYWM_DLGLONGSET:
        if (!wParam) wParam = -1;
        dlg = (sDIALOG_long*)lParam;
        SetProp(hwnd , "DLG" , dlg);
        if (wParam & DSET_TITLE) SetWindowText(hwnd , dlg->title);
        if (wParam & DSET_INFO ) SetDlgItemText(hwnd , IDC_STATIC , dlg->info);
        if (wParam & DSET_BUTTONS) ShowWindow(GetDlgItem(hwnd , IDCANCEL) , dlg->flag & DLONG_CANCEL ? SW_SHOW:SW_HIDE);

        if (wParam & DSET_ANIM)
            switch (dlg->flag & 0xFF0) {
            case DLONG_ASEND:
                Animate_Open(GetDlgItem(hwnd , IDC_ANIMATE) , MAKEINTRESOURCE(IDA_LONGSEND));
            case DLONG_ARECV:
                Animate_Open(GetDlgItem(hwnd , IDC_ANIMATE) , MAKEINTRESOURCE(IDA_LONGRECV));
            case DLONG_AINET:
                Animate_Open(GetDlgItem(hwnd , IDC_ANIMATE) , MAKEINTRESOURCE(IDA_LONGINET));
            case 0:
                Animate_Open(GetDlgItem(hwnd , IDC_ANIMATE) , MAKEINTRESOURCE(IDA_LONG));
//                      HINSTANCE hlib = LoadLibrary("shell32.dll");
//                      Animate_OpenEx(GetDlgItem(hwnd , IDC_ANIMATE) , hlib , MAKEINTRESOURCE(152));
//                      FreeLibrary(hlib);
                break;
            }
        if (wParam & DSET_PROGRESS) {
            hwnd2 = GetDlgItem(hwnd , IDC_PROGRESS);
            if (dlg->progress>=0 && !IsWindowVisible(hwnd2)) ShowWindow(hwnd2 , SW_SHOW);
            else if (dlg->progress<0 && IsWindowVisible(hwnd2)) ShowWindow(hwnd2 , SW_HIDE);
            SendMessage(hwnd2 , PBM_SETPOS , dlg->progress , 0);
        }
        break;
    case WM_COMMAND:
        dlg = (sDIALOG_long*) GetProp(hwnd , "DLG");
        if (HIWORD(wParam)!=BN_CLICKED) return 0;
        switch (LOWORD(wParam))
        {
        case IDCANCEL:
            IMLOG("- Cancel@LongProc pressed");
            if (!dlg->cancelProc) {
                dlg->cancel = true;
                ShowWindow(hwnd , SW_HIDE);
            }
            else if (dlg->cancelProc(dlg))
                dlg->cancel = true;
            return TRUE;
        }

    }
    return 0;
}