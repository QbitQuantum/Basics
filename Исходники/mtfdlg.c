/*
 * OnInitDialog()
 */
BOOL mfd_OnInitDialog(HWND mtfDlg, HWND focusCtrl, LPARAM lParam)
{
    HWND ctrl;
    int i;
    SPECIALLCDINIT noteLcdInit = { IDC_MT_NOTE_1,  3, 13, 109
        , Prog_keyNameStrings[13], NULL };
    NUMLCDINIT fineLcdInit = { IDC_MT_FINE_1,  3,  0,   63, -31, NULL };
    NUMLCDINIT fullLcdInit = { IDC_MT_FULL_1,  4,  0, 6143,   0, NULL };
    _TUCHAR noteName[5];

    mfd_dlgData.wnd = Prog_mtfDlg = mtfDlg;
    /*
     * Adjust the window position.
     */
    if (IsRectEmpty(&Prog_mtfDlgPlacement.rcNormalPosition)) {
        Window_Center(mtfDlg, mfd_parentWnd);
        GetWindowPlacement(mtfDlg, &Prog_mtfDlgPlacement);
    }
    /*
     * Set up dialog controls.
     */
    for (i = 0; i < mfd_initCnt; i++) {
        int topOffset = 34 * i;

        /*
         * Create note label.
         */
        KybdCtrl_KeyToText(i, noteName);
        ctrl = CreateWindow(
                _T("Static")                           /* window class */
                , noteName                             /* caption text */
                , WS_CHILD | WS_GROUP | WS_VISIBLE     /* styles */
                    | SS_LEFT
                , 3, 7 + topOffset                    /* left, top */
                , 26, 13                               /* width, height */
                , mtfDlg                               /* parent window */
                , (HMENU) IDC_STATIC                   /* control ID */
                , Prog_instance                        /* program instance */
                , NULL                                 /* creation data */
            );
        if (!ctrl) {
            Error_LastErrorF(_T("Error creating %s note label"), noteName);
            return FALSE;
        }
        SetWindowFont(ctrl, Prog_tahomaFont, FALSE);
        /*
         * Create Note LCD.
         */
        ctrl = CreateWindow(
                _T("LcdCtrl")                          /* window class */
                , NULL                                 /* caption text */
                , WS_CHILD | WS_TABSTOP | WS_VISIBLE   /* styles */
                    | LCS_SMALL | LCS_TEXT | LCS_LEFT_SB
                , 32, topOffset                        /* left, top */
                , 324, 13                              /* width, height */
                , mtfDlg                               /* parent window */
                , (HMENU) (IDC_MT_NOTE_1 + (i << 1))   /* control ID */
                , Prog_instance                        /* program instance */
                , NULL                                 /* creation data */
            );
        if (!ctrl) {
            Error_LastErrorF(_T("Error creating %s note LCD"), noteName);
            return FALSE;
        }
        LcdCtrl_SpecialInit(ctrl, &noteLcdInit);
        KeyNav_SubclassLcdCtrl(ctrl);
        /*
         * Create fine LCD.
         */
        ctrl = CreateWindow(
                _T("LcdCtrl")                          /* window class */
                , NULL                                 /* caption text */
                , WS_CHILD | WS_TABSTOP | WS_VISIBLE   /* styles */
                    | LCS_SMALL | LCS_NUMERIC | LCS_SHOWPLUS | LCS_LEFT_SB
                , 360, topOffset                       /* left, top */
                , 143, 13                              /* width, height */
                , mtfDlg                               /* parent window */
                , (HMENU) (IDC_MT_FINE_1 + (i << 1))   /* control ID */
                , Prog_instance                        /* program instance */
                , NULL                                 /* creation data */
            );
        if (!ctrl) {
            Error_LastErrorF(_T("Error creating %s fine LCD"), noteName);
            return FALSE;
        }
        LcdCtrl_NumInit(ctrl, &fineLcdInit);
        KeyNav_SubclassLcdCtrl(ctrl);
        /*
         * Create full range LCD.
         */
        ctrl = CreateWindow(
                _T("LcdCtrl")                          /* window class */
                , NULL                                 /* caption text */
                , WS_CHILD | WS_TABSTOP | WS_VISIBLE   /* styles */
                    | LCS_SMALL | LCS_NUMERIC | LCS_LEFT_SB
                , 32, 15 + topOffset                   /* left, top */
                , 471, 13                              /* width, height */
                , mtfDlg                               /* parent window */
                , (HMENU) (IDC_MT_FULL_1 + i)          /* control ID */
                , Prog_instance                        /* program instance */
                , NULL                                 /* creation data */
            );
        if (!ctrl) {
            Error_LastErrorF(_T("Error creating %s full range LCD"), noteName);
            return FALSE;
        }
        LcdCtrl_NumInit(ctrl, &fullLcdInit);
        KeyNav_SubclassLcdCtrl(ctrl);
        /*
         * Create frequency static control.
         */
        ctrl = CreateWindow(
                _T("Static")                           /* window class */
                , NULL                                 /* caption text */
                , WS_CHILD | WS_VISIBLE | SS_RIGHT     /* styles */
                    | SS_SUNKEN
                , 508, 7 + topOffset                   /* left, top */
                , 40, 16                               /* width, height */
                , mtfDlg                               /* parent window */
                , (HMENU) (IDC_MT_FREQ_1 + i)          /* control ID */
                , Prog_instance                        /* program instance */
                , NULL                                 /* creation data */
            );
        if (!ctrl) {
            Error_LastErrorF(_T("Error creating %s frequency display"), noteName);
            return FALSE;
        }
        SetWindowFont(ctrl, Prog_tahomaFont, FALSE);
    }
    /*
     * Set up the undo infrastructure.
     */
    mfd_dlgData.menu = GetMenu(mtfDlg);
    mfd_dlgData.undo = Undo_Create();
    /*
     * Init control values.
     */
    MTGen_InitControlValues(&mfd_dlgData);
    /*
     * Set up the scrolling dialog module.
     */
    if (!(mfd_dialog = Dialog_Create(mtfDlg)))
        return FALSE;
    Dialog_UpdateScrollBars(mfd_dialog);
    /*
     * Adjust and display the window.
     */
#define RC Prog_mtfDlgPlacement.rcNormalPosition
    MoveWindow(mtfDlg, RC.left, RC.top
            , RECT_W(RC) + GetSystemMetrics(SM_CXHSCROLL)
            , RECT_H(RC) + GetSystemMetrics(SM_CYVSCROLL), TRUE);
    MoveWindow(mtfDlg, RC.left, RC.top, RECT_W(RC), RECT_H(RC), TRUE);
#undef RC
    ShowWindow(mtfDlg, SW_SHOWNORMAL);

    return TRUE;
}