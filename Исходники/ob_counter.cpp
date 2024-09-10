LRESULT CALLBACK CounterDlgHandler( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    static int init;
    COUNTEROBJ * st;

    st = (COUNTEROBJ *) actobject;
    if ((st==NULL)||(st->type!=OB_COUNTER)) return(FALSE);

    switch( message )
    {
    case WM_INITDIALOG:
        SCROLLINFO lpsi;
        lpsi.cbSize=sizeof(SCROLLINFO);
        lpsi.fMask=SIF_RANGE|SIF_POS;
        lpsi.nMin=4;
        lpsi.nMax=300;
        SetScrollInfo(GetDlgItem(hDlg,IDC_FONTSIZEBAR),SB_CTL,&lpsi, TRUE);
        SetScrollPos(GetDlgItem(hDlg,IDC_FONTSIZEBAR), SB_CTL,st->fontsize, TRUE);
        SetDlgItemInt(hDlg, IDC_FONTSIZE, st->fontsize, FALSE);
        SetDlgItemText(hDlg, IDC_CAPTION, st->wndcaption);


        SetDlgItemInt(hDlg, IDC_RESETVALUE, (int)st->resetvalue,TRUE);
        switch (st->mode)
        {
        case 0:
            CheckDlgButton(hDlg, IDC_COUNTFT,TRUE);
            break;
        case 1:
            CheckDlgButton(hDlg, IDC_COUNTTF,TRUE);
            break;
        case 2:
            CheckDlgButton(hDlg, IDC_COUNTIV,TRUE);
            break;
        case 3:
            CheckDlgButton(hDlg, IDC_COUNTFREQ,TRUE);
            break;
        }
        CheckDlgButton(hDlg, IDC_SHOWCOUNTER,st->showcounter);
        CheckDlgButton(hDlg, IDC_INTEGER,st->integer);

        return TRUE;

    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_COUNTFT:
            st->mode=0;
            break;
        case IDC_COUNTTF:
            st->mode=1;
            break;
        case IDC_COUNTIV:
            st->mode=2;
            break;
        case IDC_COUNTFREQ:
            st->mode=3;
            break;

        case IDC_RESETCOUNTER:
            st->countervalue=st->resetvalue;
            break;
        case IDC_RESETVALUE:
            st->resetvalue=(float)GetDlgItemInt(hDlg, IDC_RESETVALUE,NULL, 1);
            break;

        case IDC_FONTCOLOR:
            st->fontcolor=select_color(hDlg);
            InvalidateRect(hDlg,NULL,FALSE);
            InvalidateRect(st->displayWnd,NULL,TRUE);
            break;
        case IDC_BKCOLOR:
            st->bkcolor=select_color(hDlg);
            InvalidateRect(hDlg,NULL,FALSE);
            InvalidateRect(st->displayWnd,NULL,TRUE);
            break;
        case IDC_CAPTION:
            GetDlgItemText(hDlg,IDC_CAPTION,st->wndcaption,50);
            SetWindowText(st->displayWnd,st->wndcaption);
            break;

        case IDC_INTEGER:
            st->integer=IsDlgButtonChecked(hDlg,IDC_INTEGER);
            InvalidateRect(st->displayWnd,NULL,TRUE);
            break;

        case IDC_SHOWCOUNTER:
        {   int i;
            i=IsDlgButtonChecked(hDlg,IDC_SHOWCOUNTER);
            if ((st->showcounter)&&(!i)&&(st->displayWnd))  {
                DestroyWindow(st->displayWnd);
                st->displayWnd=NULL;
            }
            if ((!st->showcounter)&&(i))
            {
                if(!(st->displayWnd=CreateWindow("Counter_Class", "Counter", WS_THICKFRAME| WS_CLIPCHILDREN,st->left, st->top, st->right-st->left, st->bottom-st->top, NULL, NULL, hInst, NULL)))
                    report_error("can't create Counter Window");
                else {
                    ShowWindow( st->displayWnd, TRUE );
                    UpdateWindow( st->displayWnd );
                }
            }
            st->showcounter=i;
        }
        break;

        }
        return TRUE;

    case WM_HSCROLL:
        if (lParam == (long) GetDlgItem(hDlg,IDC_FONTSIZEBAR))
        {
            int nNewPos=get_scrollpos(wParam,lParam);
            SetDlgItemInt(hDlg, IDC_FONTSIZE, nNewPos, TRUE);
            st->fontsize=nNewPos;
            if (st->font) DeleteObject(st->font);
            if (!(st->font = CreateFont(-MulDiv(st->fontsize, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Arial")))
                report_error("Font creation failed!");

            InvalidateRect(st->displayWnd, NULL, TRUE);
        }
        break;

    case WM_SIZE:
    case WM_MOVE:
        update_toolbox_position(hDlg);
    case WM_PAINT:
        color_button(GetDlgItem(hDlg,IDC_FONTCOLOR),st->fontcolor);
        color_button(GetDlgItem(hDlg,IDC_BKCOLOR),st->bkcolor);
        break;
    }
    return FALSE;
}