// This seems pure front end
LRESULT CALLBACK EngineOutputProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    static SnapData sd;

    switch (message) {
    case WM_INITDIALOG:
        if( engineOutputDialog == NULL ) {
            engineOutputDialog = hDlg;

            Translate(hDlg, DLG_EngineOutput);
            RestoreWindowPlacement( hDlg, &wpEngineOutput ); /* Restore window placement */

            ResizeWindowControls( windowMode );

            SendDlgItemMessage( hDlg, IDC_EngineMemo1, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS );
            SendDlgItemMessage( hDlg, IDC_EngineMemo2, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS );

	    /* Set font */
	    SendDlgItemMessage( engineOutputDialog, IDC_EngineMemo1, WM_SETFONT, (WPARAM)font[boardSize][MOVEHISTORY_FONT]->hf, MAKELPARAM(TRUE, 0 ));
	    SendDlgItemMessage( engineOutputDialog, IDC_EngineMemo2, WM_SETFONT, (WPARAM)font[boardSize][MOVEHISTORY_FONT]->hf, MAKELPARAM(TRUE, 0 ));

            SetEngineState( 0, STATE_IDLE, "" );
            SetEngineState( 1, STATE_IDLE, "" );
        }

        return FALSE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
          EndDialog(hDlg, TRUE);
          return TRUE;

        case IDCANCEL:
          EndDialog(hDlg, FALSE);
          return TRUE;

        default:
          break;
        }

        break;

    case WM_MOUSEMOVE:
        MovePV(LOWORD(lParam) - boardRect.left, HIWORD(lParam) - boardRect.top, boardRect.bottom - boardRect.top);
        break;

    case WM_RBUTTONUP:
        ReleaseCapture();
        SendMessage( outputField[currentPV][nMemo], EM_SETSEL, 0, 0 );
        highTextStart[currentPV] = highTextEnd[currentPV] = 0;
        UnLoadPV();
        break;

    case WM_NOTIFY:
        if( wParam == IDC_EngineMemo1 || wParam == IDC_EngineMemo2 ) {
            MSGFILTER * lpMF = (MSGFILTER *) lParam;
            if( lpMF->msg == WM_RBUTTONDOWN && (lpMF->wParam & (MK_CONTROL | MK_SHIFT)) == 0 ) {
                currentPV = (wParam == IDC_EngineMemo2);
                GetMemoLine(hDlg, LOWORD(lpMF->lParam), HIWORD(lpMF->lParam));
            }
        }
        break;

    case WM_GETMINMAXINFO:
        {
            MINMAXINFO * mmi = (MINMAXINFO *) lParam;
        
            mmi->ptMinTrackSize.x = 100;
            mmi->ptMinTrackSize.y = 160;
        }
        break;

    case WM_CLOSE:
        EngineOutputPopDown();
        break;

    case WM_SIZE:
        ResizeWindowControls( windowMode );
        break;

    case WM_ENTERSIZEMOVE:
        return OnEnterSizeMove( &sd, hDlg, wParam, lParam );

    case WM_SIZING:
        return OnSizing( &sd, hDlg, wParam, lParam );

    case WM_MOVING:
        return OnMoving( &sd, hDlg, wParam, lParam );

    case WM_EXITSIZEMOVE:
        return OnExitSizeMove( &sd, hDlg, wParam, lParam );
    }

    return FALSE;
}