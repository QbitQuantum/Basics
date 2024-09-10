INT_PTR CALLBACK PinCtrlDlgProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_CLOSE:
    {
        RECT rc;
        GetWindowRect(hWndDlg, &rc);
        axisx = rc.left;
        axisy = rc.top;
        hWndPinCtrl = NULL;
        EndDialog(hWndDlg, 0);
        return 0;
    }
    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_PINCTRL_OK:
            if(HIWORD(wParam) != BN_CLICKED)
                return 0;
            if(msg.hComPort == INVALID_HANDLE_VALUE)
            {
                MessageBox(hWndDlg, "没有串口设备被打开!", COMMON_NAME, MB_ICONINFORMATION);
                return 0;
            }
            cconfig.dcb.fDtrControl = dtr[ComboBox_GetCurSel(hDtr)];
            cconfig.dcb.fRtsControl = rts[ComboBox_GetCurSel(hRts)];
            if(!SetCommConfig(msg.hComPort, &cconfig, sizeof(cconfig)))
            {
                utils.msgerr("设置DTR/RTS时错误!");
                return 0;
            }
            EnableWindow(GetDlgItem(hWndDlg, IDC_PINCTRL_OK), FALSE);
            break;
        case IDC_CBO_PINCTRL_DTR:
        case IDC_CBO_PINCTRL_RTS:
            if(HIWORD(wParam) == CBN_SELENDOK)
            {
                EnableWindow(GetDlgItem(hWndDlg, IDC_PINCTRL_OK), TRUE);
                return 0;
            }
            break;
        }
        return 0;
    }
    case WM_INITDIALOG:
    {
        DWORD size = sizeof(cconfig);
        if(msg.hComPort == INVALID_HANDLE_VALUE)
        {
            utils.msgbox(MB_ICONEXCLAMATION, COMMON_NAME, "请先打开一个串口设备!");
            EndDialog(hWndDlg, 0);
            return 0;
        }
        if(!GetCommConfig(msg.hComPort, &cconfig, &size))
        {
            utils.msgerr("获取串口配置时错误");
            EndDialog(hWndDlg, 0);
            return 0;
        }
        hDtr = GetDlgItem(hWndDlg, IDC_CBO_PINCTRL_DTR);
        hRts = GetDlgItem(hWndDlg, IDC_CBO_PINCTRL_RTS);
        for(;;)
        {
            int i;
            for(i = 0; i < 3; i++)
            {
                ComboBox_AddString(hDtr, sdtr[i]);
                ComboBox_AddString(hRts, srts[i]);
            }
            ComboBox_SetCurSel(hDtr, cconfig.dcb.fDtrControl);
            ComboBox_SetCurSel(hRts, cconfig.dcb.fRtsControl);
            break;
        }
        //...
        hWndPinCtrl = hWndDlg;
        SetWindowPos(hWndDlg, 0, axisx, axisy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        return 0;
    }
    }
    UNREFERENCED_PARAMETER(lParam);
    return 0;
}