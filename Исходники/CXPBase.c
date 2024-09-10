////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取窗口状态
BOOL CXPGetState(PCLASSXP pCxp)
{
    PCLASSXP p;
    UINT uCheck;

    // 设置禁用和焦点状态
    pCxp->lState = _CXPGetStyle(WS_DISABLED) ? CXPS_DISABLED : 0;
    _ExIf(pCxp->hWnd == GetFocus(), _CXPSetState(CXPS_FOCUS));

    switch (pCxp->uClass)
    {
    case CXPC_BUTTON:
        switch (_CXPGetStyle(BS_TYPEMASK))
        {
        case BS_DEFPUSHBUTTON:		// 默认按钮
            _CXPSetState(CXPS_DEFAULT);

        case BS_PUSHBUTTON:			// 普通按钮
            break;

        case BS_CHECKBOX:			// 复选框
        case BS_AUTOCHECKBOX:		// 自动复选框
        case BS_3STATE:				// 三状态复选框
        case BS_AUTO3STATE:			// 自动三状态复选框

        case BS_RADIOBUTTON:		// 单选框
        case BS_AUTORADIOBUTTON:	// 自动单选框
            if (!_CXPGetStyle(BS_PUSHLIKE))
            {
                pCxp->pDraw = CXPDrawCheckBox;
            }
            break;

        default:					// 自绘按钮、组合框和其它未知类型
            return FALSE;
        }
        uCheck = (LONG) SendMessage(pCxp->hWnd, BM_GETCHECK, 0, 0);
        if (uCheck == BST_CHECKED)
        {
            _CXPSetState(CXPS_CHECKED);
        }
        else if (uCheck == BST_INDETERMINATE)
        {
            _CXPSetState(CXPS_INDETERMINATE);
        }
        break;

    case CXPC_EDITBOX:
        if (!_CXPGetStyle(WS_BORDER) && !(GetWindowLong(pCxp->hWnd, GWL_EXSTYLE) & (WS_EX_CLIENTEDGE | WS_EX_STATICEDGE)))
        {
            return FALSE;
        }
        _ExIf(_CXPGetStyle(ES_READONLY), _CXPSetState(CXPS_READONLY));
        break;

    case CXPC_COMBOBOX:
        if (_CXPGetStyle(CBS_TYPEMASK) == CBS_SIMPLE)
        {
            _CXPSetState(CXPS_SIMPLECMB);
        }
        break;

    case CXPC_SPINBOX:
        _ExIf(_CXPGetStyle(UDS_HORZ), _CXPSetState(CXPS_HORIZON));
        _ExIf(_CXPGetStyle(UDS_ARROWKEYS), _CXPSetState(CXPS_ACCELSPIN));
        _ExIf(_CXPGetStyle(UDS_ALIGNLEFT), _CXPSetState(CXPS_LEFTSPIN));
        _ExIf(_CXPGetStyle(UDS_ALIGNRIGHT), _CXPSetState(CXPS_RIGHTSPIN));

        // 设置旧伙伴
        p = (PCLASSXP) pCxp->lParam;
        _ExIf(p, p->lParam = 0);

        p = (PCLASSXP) GetProp((HWND) SendMessage(pCxp->hWnd, UDM_GETBUDDY, 0, 0), TEXT("ClassXP"));
        if (p && (p->uClass == CXPC_EDITBOX))
        {
            // 设置新伙伴
            p->lParam = (LPARAM) pCxp;
            pCxp->lParam = (LPARAM) p;
        }
        break;
    }

    return TRUE;
}