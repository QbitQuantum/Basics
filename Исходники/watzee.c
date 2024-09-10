long _EXPORT FAR PASCAL WndProc( HWND hwnd, UINT message, WPARAM wparam,
                                  LPARAM lparam )
/*********************************************************************/
{
    static HANDLE   hdlginstance;
    static BOOL     got_watzee_bonus;
    PAINTSTRUCT     ps;
    FARPROC         dlg_proc;
    HDC             hdc;
    POINT           point;
    short           x;
    short           y;
    short           dy;
    short           i;

    switch( message ) {
    case WM_CREATE :
        hdlginstance = ((CREATESTRUCT far *) MK_FP32((void*)lparam))->hInstance;
        x = CharWidth * 22 + CharWidth / 2;
        y = CharHeight * 3;
        dy = CharHeight * 3;
        dy += dy / 7;
       /*  create the check marks for the dice bitmaps, and the ROLL and
           OK buttons  */
        for( i = 0; i < 5; i++, y += dy ) {
            CreateWindow( "BUTTON", "", WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
                          x, y, CharWidth, CharHeight, hwnd,
                          (HMENU)(IDW_DICE1+i),
                          hdlginstance,
                          NULL );
        }
        CreateWindow( "BUTTON", "ROLL", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
                      x, CharHeight * 19, 9 * CharWidth / 2 ,
                      CharHeight * 2, hwnd, (HMENU)IDW_ROLL,
                      hdlginstance, NULL );
        CreateWindow( "BUTTON", "OK", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
                      x, 43 * CharHeight / 2, 9 * CharWidth / 2,
                      CharHeight * 2, hwnd, (HMENU)IDW_OK,
                      hdlginstance, NULL );
        return( 0 );
    case WMW_START_NEW_GAME :
        dlg_proc = MakeProcInstance( (FARPROC)GetNumPlayersDialogProc, hdlginstance );
        DialogBox( hdlginstance, "GetNumPlayers", hwnd, (DLGPROC)dlg_proc );
        FreeProcInstance( dlg_proc );
        dlg_proc = MakeProcInstance( (FARPROC)GetInitialsDialogProc, hdlginstance );
        DialogBox( hdlginstance, "GetPlayersInitials", hwnd, (DLGPROC)dlg_proc );
        FreeProcInstance( dlg_proc );
        EnableWindow( GetDlgItem( hwnd, IDW_OK ), FALSE );
        EnableWindow( GetDlgItem( hwnd, IDW_ROLL ), TRUE );
        PlayingGameYet = TRUE;
        InvalidateRect( hwnd, NULL, FALSE );
        for( i = 0; i < NumberOfPlayers; i++ ) {
            if( Player[i][IS_COMPUTER] ) break;
        }
        if( i < NumberOfPlayers && !GotTimer ) {
            while( !SetTimer( hwnd, ID_TIMER, TIMER_INTERVAL, NULL ) ) {
                if( MessageBox( hwnd, "Too many clocks or timers are active",
                 AppName, MB_ICONEXCLAMATION|MB_RETRYCANCEL ) == IDCANCEL ) {
                    DestroyWindow( hwnd );
                    return( 0 );
                }
            }
            GotTimer = TRUE;
        }
        if( i == 0 ) {
            PCTurn = TRUE;
            EnableWindow( GetDlgItem( hwnd, IDW_ROLL ), FALSE );
        }
        hdc = GetDC( hwnd );
        RollDice( hwnd, hdc );
        GetDiceInfo();
        ReleaseDC( hwnd, hdc );
//      SetFocus( hwnd );
        return( 0 );
    case WM_COMMAND :
        switch( LOWORD( wparam ) ) {
        case IDM_NEWGAME :
            if( GotTimer ) {
                KillTimer( hwnd, ID_TIMER );
            }
            if( MessageBox( hwnd, "Start New Game:  Are you sure?", "WATZEE",
                            MB_YESNO | MB_ICONEXCLAMATION ) == IDYES ) {
                InitializeGameData();
                InvalidateRect( hwnd, NULL, TRUE );
                SendMessage( hwnd, WMW_START_NEW_GAME, 0, 0 );
            } else if( GotTimer ) {
                SetTimer( hwnd, ID_TIMER, TIMER_INTERVAL, NULL );
            }
            break;
        case IDM_OPTIONS :
            if( GotTimer ) {
                KillTimer( hwnd, ID_TIMER );
            }
            dlg_proc = MakeProcInstance( (FARPROC)OptionsDialogProc, hdlginstance );
            DialogBox( hdlginstance, "Options", hwnd, (DLGPROC)dlg_proc );
            FreeProcInstance( dlg_proc );
            if( GotTimer ) {
                SetTimer( hwnd, ID_TIMER, TIMER_INTERVAL, NULL );
            }
            break;
        case IDM_EXIT :
            DestroyWindow( hwnd );
            break;
        case IDM_SCORING :
            if( GotTimer ) {
                KillTimer( hwnd, ID_TIMER );
            }
            dlg_proc = MakeProcInstance( (FARPROC)HelpDialogProc, hdlginstance );
            DialogBox( hdlginstance, "WatzeeHelp", hwnd, (DLGPROC)dlg_proc );
            FreeProcInstance( dlg_proc );
            if( GotTimer ) {
                SetTimer( hwnd, ID_TIMER, TIMER_INTERVAL, NULL );
            }
            break;
        case IDM_ABOUT :
            if( GotTimer ) {
                KillTimer( hwnd, ID_TIMER );
            }
            dlg_proc = MakeProcInstance( (FARPROC)AboutDialogProc, hdlginstance );
            DialogBox( hdlginstance, "AboutWatzee", hwnd, (DLGPROC)dlg_proc );
            FreeProcInstance( dlg_proc );
            if( GotTimer ) {
                SetTimer( hwnd, ID_TIMER, TIMER_INTERVAL, NULL );
            }
            break;
        case IDW_DICE1 :
        case IDW_DICE2 :
        case IDW_DICE3 :
        case IDW_DICE4 :
        case IDW_DICE5 :
            if( !PCTurn && CurrentRoll < 2 ) {
                SendMessage( hwnd, WMW_DIE_CHECK, wparam, 0 );
            }
            break;
        case IDW_ROLL :
            SendMessage( hwnd, WMW_ROLL, 0, 0 );
            break;
        case IDW_OK :
            SendMessage( hwnd, WMW_OK, 0, 0 );
            break;
        }
        return( 0 );
    case WM_LBUTTONUP :
        if( !PCTurn ) {
            MAKE_POINT( point, lparam );
            if( point.x > CharWidth * 24
             && point.y < CharHeight * 20 ) {
                wparam = GetDieCheck( hwnd, point );
                if( wparam && CurrentRoll < 2 ) {
                    SendMessage( hwnd, WMW_DIE_CHECK, wparam, 0 );
                }
            } else {
                wparam = GetScoreCheck( point );
                if( wparam && Player[CurrentPlayer][wparam] == UNDEFINED ) {
                     SendMessage( hwnd, WMW_SCORE_CHECK, wparam, 0 );
                }
            }
        }
        return( 0 );
    case WMW_DIE_CHECK :
        i = LOWORD( wparam ) - IDW_DICE1;
        Dice[i].is_checked = !Dice[i].is_checked;
        CheckDlgButton( hwnd, wparam, (BOOL)Dice[i].is_checked );
//      SetFocus( hwnd );
        return( 0 );
    case WMW_SCORE_CHECK :
        hdc = GetDC( hwnd );
        if( wparam != LastScoreSelection ) {
            DoScore( hdc, wparam );
            EnableWindow( GetDlgItem( hwnd, IDW_OK ), TRUE );
        }
        ReleaseDC( hwnd, hdc );
//      SetFocus( hwnd );
        return( 0 );
    case WMW_ROLL :
        hdc = GetDC( hwnd );
        if( DieCheckMeansRoll ) {
            for( i = 0; i < 5; i++ ) {
                if( Dice[i].is_checked ) break;
            }
        } else {
            for( i = 0; i < 5; i++ ) {
                if( !Dice[i].is_checked ) break;
            }
        }
        if( i < 5 ) {
            if( LastScoreSelection ) {
                Player[CurrentPlayer][LastScoreSelection] = UNDEFINED;
                WriteScore( hdc, CurrentPlayer, LastScoreSelection );
                DoScoreTotals( hdc );
                LastScoreSelection = 0;
            }
            got_watzee_bonus = FALSE;
            CurrentRoll++;
            RollDice( hwnd, hdc );
            GetDiceInfo();
            if( DiceInfo.got_watzee && Player[CurrentPlayer][WATZEE] == 50 ) {
                got_watzee_bonus = TRUE;
            }
            if( CurrentRoll == 2 ) {
                EnableWindow( GetDlgItem( hwnd, IDW_ROLL ), FALSE );
            }
        }
        ReleaseDC( hwnd, hdc );
//      SetFocus( hwnd );
        return( 0 );
    case WMW_OK :
        hdc = GetDC( hwnd );
        LastScoreSelection = 0;
        if( got_watzee_bonus ) {
            DoScore( hdc, WATZEE_BONUS );
            LastScoreSelection = 0;
            got_watzee_bonus = FALSE;
        }
        NextPlayer( hwnd, hdc );
        ReleaseDC( hwnd, hdc );
//      SetFocus( hwnd );
        return( 0 );
    case WMW_GAME_OVER :
        hdc = GetDC( hwnd );
        WriteScoreOptions( hdc );
        ReleaseDC( hwnd, hdc );
        if( GotTimer ) {
            KillTimer( hwnd, ID_TIMER );
            GotTimer = FALSE;
        }
        if( MessageBox( hwnd, "Another Game ?", "WATZEE", MB_YESNO ) == IDYES ) {
            InitializeGameData();
            InvalidateRect( hwnd, NULL, TRUE );
            SendMessage( hwnd, WMW_START_NEW_GAME, 0, 0 );
        } else {
            DestroyWindow( hwnd );
        }
        return( 0 );
    case WM_TIMER :
        if( PCTurn ) {
            PCPlay( hwnd );
        }
        return( 0 );
    case WM_PAINT :
        hdc = BeginPaint( hwnd, &ps );
        DrawDice( hwnd, hdc );
        DrawScoreCard( hdc );
        WriteScoreOptions( hdc );
        if( PlayingGameYet ) {
            WriteInitials( hdc );
            HighliteName( hdc, CurrentPlayer );
            WriteScores( hdc );
        }
        EndPaint( hwnd, &ps );
        return( 0 );
    case WM_DESTROY :
        {
            HBITMAP     hbm;

            if( GotTimer ) {
                KillTimer( hwnd, ID_TIMER );
            }
            for( i = 0; i < 6; i++ ) {
                hbm = (HBITMAP)GetWindowLong( hwnd, i * sizeof( DWORD ) );
                DeleteObject( hbm );
            }
            PostQuitMessage( 0 );
            return( 0 );
        }
    }
    return( DefWindowProc( hwnd, message, wparam, lparam ) );
}