INT_PTR CALLBACK
_password_change_dlg_proc(
    HWND	hwnd,
    UINT	message,
    WPARAM	wparam,
    LPARAM	lparam
)
{
    WORD code = HIWORD(wparam);
    WORD id   = LOWORD(wparam);

    wchar_t display[MAX_PATH] = { 0 };
    static  dlgpass *info;
    int     k;

    int check_init[ ] = {
        IDC_CHECK_SHOW_CURRENT, IDC_USE_KEYFILES_CURRENT,
        IDC_CHECK_SHOW_NEW, IDC_USE_KEYFILES_NEW,
        -1
    };

    _ctl_init static_head[ ] = {
        { L"# Current Password", IDC_HEAD_PASS_CURRENT, 0 },
        { L"# New Password",     IDC_HEAD_PASS_NEW,     0 },
        { L"# Password Rating",  IDC_HEAD_RATING,       0 },
        { STR_NULL, -1, -1 }
    };

    switch (message)
    {
    case WM_CTLCOLOREDIT :
        return _ctl_color(wparam, _cl(COLOR_BTNFACE, LGHT_CLR));
        break;

    case WM_CTLCOLORSTATIC :
    {
        HDC dc = (HDC)wparam;
        COLORREF bgcolor, fn = 0;

        SetBkMode(dc, TRANSPARENT);

        k = 0;
        while (pass_gr_ctls[k].id != -1)
        {
            if (pass_gr_ctls[k].hwnd == (HWND)lparam)
                fn = pass_gr_ctls[k].color;

            if (pass_pe_ctls[k].hwnd == (HWND)lparam)
                fn = pass_pe_ctls[k].color;

            k++;
        }
        SetTextColor(dc, fn);

        bgcolor = GetSysColor(COLOR_BTNFACE);
        SetDCBrushColor(dc, bgcolor);

        return (INT_PTR)GetStockObject(DC_BRUSH);

    }
    break;
    case WM_INITDIALOG :
    {
        info = (dlgpass *)lparam;

        SendMessage(GetDlgItem(hwnd, IDE_PASS_NEW_CONFIRM), EM_LIMITTEXT, MAX_PASSWORD, 0);
        SendMessage(GetDlgItem(hwnd, IDE_PASS_CURRENT),     EM_LIMITTEXT, MAX_PASSWORD, 0);
        SendMessage(GetDlgItem(hwnd, IDE_PASS_NEW),         EM_LIMITTEXT, MAX_PASSWORD, 0);

        SendMessage(hwnd, WM_COMMAND,
                    MAKELONG(IDE_PASS_NEW, EN_CHANGE), (LPARAM)GetDlgItem(hwnd, IDE_PASS_NEW));

        if (info->node) {
            _snwprintf(display, sizeof_w(display), L"[%s] - %s",
                       info->node->mnt.info.status.mnt_point, info->node->mnt.info.device);

        } else {
            wcscpy(display, L"Change password");

        }
        SetWindowText(hwnd, display);

        SendMessage(
            GetDlgItem(hwnd, IDP_BREAKABLE),
            PBM_SETBARCOLOR, 0, _cl(COLOR_BTNSHADOW, DARK_CLR-20)
        );

        SendMessage(
            GetDlgItem(hwnd, IDP_BREAKABLE),
            PBM_SETRANGE, 0, MAKELPARAM(0, 193)
        );

        k = 0;
        while (static_head[k].id != -1) {

            SetWindowText(GetDlgItem(hwnd, static_head[k].id), static_head[k].display);
            SendMessage(GetDlgItem(hwnd, static_head[k].id), (UINT)WM_SETFONT, (WPARAM)__font_bold, 0);
            k++;
        }

        k = 0;
        while (check_init[k] != -1) {

            _sub_class(GetDlgItem(hwnd, check_init[k]), SUB_STATIC_PROC, HWND_NULL);
            _set_check(hwnd, check_init[k], FALSE);
            k++;
        }
        SetForegroundWindow(hwnd);
        return 1L;

    }
    break;
    case WM_USER_CLICK :
    {
        if ( (HWND)wparam == GetDlgItem(hwnd, IDC_CHECK_SHOW_CURRENT) )
        {
            SendMessage(GetDlgItem(hwnd, IDE_PASS_CURRENT),
                        EM_SETPASSWORDCHAR, _get_check(hwnd, IDC_CHECK_SHOW_CURRENT) ? 0 : '*', 0
                       );

            InvalidateRect(GetDlgItem(hwnd, IDE_PASS_CURRENT), NULL, TRUE);
            return 1L;

        }
        if ( (HWND)wparam == GetDlgItem(hwnd, IDC_CHECK_SHOW_NEW) )
        {
            int mask = _get_check(hwnd, IDC_CHECK_SHOW_NEW) ? 0 : '*';

            SendMessage(GetDlgItem(hwnd, IDE_PASS_NEW), EM_SETPASSWORDCHAR,	mask, 0);
            SendMessage(GetDlgItem(hwnd, IDE_PASS_NEW_CONFIRM), EM_SETPASSWORDCHAR,	mask, 0);

            InvalidateRect(GetDlgItem(hwnd, IDE_PASS_NEW), NULL, TRUE);
            InvalidateRect(GetDlgItem(hwnd, IDE_PASS_NEW_CONFIRM), NULL, TRUE);
            return 1L;

        }
        if ( (HWND)wparam == GetDlgItem(hwnd, IDC_USE_KEYFILES_CURRENT) )
        {
            SendMessage(
                hwnd, WM_COMMAND, MAKELONG(IDE_PASS_CURRENT, EN_CHANGE), (LPARAM)GetDlgItem(hwnd, IDE_PASS_CURRENT)
            );
            EnableWindow(
                GetDlgItem(hwnd, IDB_USE_KEYFILES_CURRENT), _get_check(hwnd, IDC_USE_KEYFILES_CURRENT)
            );
            return 1L;
        }
        if ( (HWND)wparam == GetDlgItem(hwnd, IDC_USE_KEYFILES_NEW) )
        {
            SendMessage(
                hwnd, WM_COMMAND, MAKELONG(IDE_PASS_NEW, EN_CHANGE), (LPARAM)GetDlgItem(hwnd, IDE_PASS_NEW)
            );
            EnableWindow(
                GetDlgItem(hwnd, IDB_USE_KEYFILES_NEW), _get_check(hwnd, IDC_USE_KEYFILES_NEW
                                                                  ));
            return 1L;
        }
    }
    break;
    case WM_COMMAND :

        if ( id == IDB_USE_KEYFILES_CURRENT )
        {
            _dlg_keyfiles( hwnd, KEYLIST_CURRENT );

            SendMessage(
                hwnd, WM_COMMAND, MAKELONG(IDE_PASS_CURRENT, EN_CHANGE), (LPARAM)GetDlgItem(hwnd, IDE_PASS_CURRENT)
            );
        }
        if ( id == IDB_USE_KEYFILES_NEW )
        {
            _dlg_keyfiles( hwnd, KEYLIST_CHANGE_PASS );

            SendMessage(
                hwnd, WM_COMMAND, MAKELONG(IDE_PASS_NEW, EN_CHANGE), (LPARAM)GetDlgItem(hwnd, IDE_PASS_NEW)
            );
        }

        if ( code == EN_CHANGE )
        {
            BOOL correct_current, correct_new;
            int  id_stat_current, id_stat_new;

            dc_pass *pass;
            dc_pass *verify;

            ldr_config conf;

            int kb_layout = -1;
            int keylist;

            if ( info->node && _is_boot_device(&info->node->mnt.info) )
            {
                if (dc_get_mbr_config( -1, NULL, &conf ) == ST_OK)
                {
                    kb_layout = conf.kbd_layout;
                }
            }
            if ( id == IDE_PASS_NEW )
            {
                int entropy;
                dc_pass *pass;

                pass = _get_pass(hwnd, IDE_PASS_NEW);

                _draw_pass_rating(hwnd, pass, kb_layout, &entropy);
                secure_free(pass);

                SendMessage(
                    GetDlgItem(hwnd, IDP_BREAKABLE),
                    PBM_SETPOS,
                    (WPARAM)entropy, 0
                );
            }

            pass    = _get_pass(hwnd, IDE_PASS_CURRENT);
            keylist = _get_check(hwnd, IDC_USE_KEYFILES_CURRENT) ? KEYLIST_CURRENT : KEYLIST_NONE;

            correct_current =
                _input_verify(pass, NULL, keylist, -1, &id_stat_current
                             );

            secure_free(pass);

            pass    = _get_pass(hwnd, IDE_PASS_NEW);
            verify  = _get_pass(hwnd, IDE_PASS_NEW_CONFIRM);
            keylist = _get_check(hwnd, IDC_USE_KEYFILES_NEW) ? KEYLIST_CHANGE_PASS : KEYLIST_NONE;

            correct_new =
                _input_verify(pass, verify, keylist, kb_layout, &id_stat_new
                             );

            secure_free(pass);
            secure_free(verify);

            SetWindowText(GetDlgItem(hwnd, IDC_PASS_STATUS_CURRENT), _get_text_name(id_stat_current, pass_status));
            SetWindowText(GetDlgItem(hwnd, IDC_PASS_STATUS_NEW), _get_text_name(id_stat_new, pass_status));

            EnableWindow(GetDlgItem(hwnd, IDOK), correct_current && correct_new);

            return 1L;

        }
        if ( (id == IDCANCEL) || (id == IDOK) )
        {
            if ( id == IDOK )
            {
                info->pass     = _get_pass_keyfiles(hwnd, IDE_PASS_CURRENT, IDC_USE_KEYFILES_CURRENT, KEYLIST_CURRENT);
                info->new_pass = _get_pass_keyfiles(hwnd, IDE_PASS_NEW,     IDC_USE_KEYFILES_NEW,     KEYLIST_CHANGE_PASS);

                if ( IsWindowEnabled(GetDlgItem(hwnd, IDC_COMBO_MNPOINT)) &&
                        info->mnt_point
                   )
                {
                    GetWindowText(
                        GetDlgItem(hwnd, IDC_COMBO_MNPOINT),
                        (wchar_t *)info->mnt_point,
                        MAX_PATH
                    );
                }
            }
            EndDialog (hwnd, id);
            return 1L;

        }
        break;
    case WM_DESTROY:
    {
        _wipe_pass_control(hwnd, IDE_PASS_NEW_CONFIRM);
        _wipe_pass_control(hwnd, IDE_PASS_CURRENT);
        _wipe_pass_control(hwnd, IDE_PASS_NEW);

        _keyfiles_wipe(KEYLIST_CURRENT);
        _keyfiles_wipe(KEYLIST_CHANGE_PASS);

        return 0L;
    }
    break;
    default:
    {
        int rlt = _draw_proc(message, lparam);
        if (rlt != -1) return rlt;
    }
    }
    return 0L;

}