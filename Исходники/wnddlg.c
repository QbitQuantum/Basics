INT_PTR CALLBACK WepWindowsDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    PWINDOWS_CONTEXT context;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PWINDOWS_CONTEXT)lParam;
        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PWINDOWS_CONTEXT)GetProp(hwndDlg, L"Context");

        if (uMsg == WM_DESTROY)
            RemoveProp(hwndDlg, L"Context");
    }

    if (!context)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            PPH_STRING windowTitle;
            PH_RECTANGLE windowRectangle;

            context->TreeNewHandle = GetDlgItem(hwndDlg, IDC_LIST);
            WeInitializeWindowTree(hwndDlg, context->TreeNewHandle, &context->TreeContext);

            PhRegisterDialog(hwndDlg);

            PhInitializeLayoutManager(&context->LayoutManager, hwndDlg);
            PhAddLayoutItem(&context->LayoutManager, GetDlgItem(hwndDlg, IDC_LIST), NULL, PH_ANCHOR_ALL);

            if (MinimumSize.left == -1)
            {
                RECT rect;

                rect.left = 0;
                rect.top = 0;
                rect.right = 160;
                rect.bottom = 100;
                MapDialogRect(hwndDlg, &rect);
                MinimumSize = rect;
                MinimumSize.left = 0;
            }

            // Set up the window position and size.

            windowRectangle.Position = PhGetIntegerPairSetting(SETTING_NAME_WINDOWS_WINDOW_POSITION);
            windowRectangle.Size = PhGetIntegerPairSetting(SETTING_NAME_WINDOWS_WINDOW_SIZE);
            PhAdjustRectangleToWorkingArea(hwndDlg, &windowRectangle);

            MoveWindow(hwndDlg, windowRectangle.Left, windowRectangle.Top,
                windowRectangle.Width, windowRectangle.Height, FALSE);

            // Implement cascading by saving an offsetted rectangle.
            windowRectangle.Left += 20;
            windowRectangle.Top += 20;
            PhSetIntegerPairSetting(SETTING_NAME_WINDOWS_WINDOW_POSITION, windowRectangle.Position);

            windowTitle = WepGetWindowTitleForSelector(&context->Selector);
            SetWindowText(hwndDlg, windowTitle->Buffer);
            PhDereferenceObject(windowTitle);

            WepRefreshWindows(context);
        }
        break;
    case WM_DESTROY:
        {
            PhSaveWindowPlacementToSetting(SETTING_NAME_WINDOWS_WINDOW_POSITION, SETTING_NAME_WINDOWS_WINDOW_SIZE, hwndDlg);

            PhDeleteLayoutManager(&context->LayoutManager);
            PhUnregisterDialog(hwndDlg);

            WeDeleteWindowTree(&context->TreeContext);
            WepDeleteWindowSelector(&context->Selector);
            PhFree(context);
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDCANCEL:
            //case IDOK:
                DestroyWindow(hwndDlg);
                break;
            case IDC_REFRESH:
                WepRefreshWindows(context);
                break;
            case ID_SHOWCONTEXTMENU:
                {
                    POINT point;
                    PWE_WINDOW_NODE *windows;
                    ULONG numberOfWindows;
                    HMENU menu;
                    HMENU subMenu;

                    point.x = (SHORT)LOWORD(lParam);
                    point.y = (SHORT)HIWORD(lParam);

                    WeGetSelectedWindowNodes(
                        &context->TreeContext,
                        &windows,
                        &numberOfWindows
                        );

                    if (numberOfWindows != 0)
                    {
                        menu = LoadMenu(PluginInstance->DllBase, MAKEINTRESOURCE(IDR_WINDOW));
                        subMenu = GetSubMenu(menu, 0);
                        SetMenuDefaultItem(subMenu, ID_WINDOW_PROPERTIES, FALSE);

                        if (numberOfWindows == 1)
                        {
                            WINDOWPLACEMENT placement = { sizeof(placement) };
                            BYTE alpha;
                            ULONG flags;
                            ULONG i;
                            ULONG id;

                            // State

                            GetWindowPlacement(windows[0]->WindowHandle, &placement);

                            if (placement.showCmd == SW_MINIMIZE)
                                PhEnableMenuItem(subMenu, ID_WINDOW_MINIMIZE, FALSE);
                            else if (placement.showCmd == SW_MAXIMIZE)
                                PhEnableMenuItem(subMenu, ID_WINDOW_MAXIMIZE, FALSE);
                            else if (placement.showCmd == SW_NORMAL)
                                PhEnableMenuItem(subMenu, ID_WINDOW_RESTORE, FALSE);

                            // Visible

                            CheckMenuItem(subMenu, ID_WINDOW_VISIBLE,
                                (GetWindowLong(windows[0]->WindowHandle, GWL_STYLE) & WS_VISIBLE) ? MF_CHECKED : MF_UNCHECKED);

                            // Enabled

                            CheckMenuItem(subMenu, ID_WINDOW_ENABLED,
                                !(GetWindowLong(windows[0]->WindowHandle, GWL_STYLE) & WS_DISABLED) ? MF_CHECKED : MF_UNCHECKED);

                            // Always on Top

                            CheckMenuItem(subMenu, ID_WINDOW_ALWAYSONTOP,
                                (GetWindowLong(windows[0]->WindowHandle, GWL_EXSTYLE) & WS_EX_TOPMOST) ? MF_CHECKED : MF_UNCHECKED);

                            // Opacity

                            if (GetLayeredWindowAttributes(windows[0]->WindowHandle, NULL, &alpha, &flags))
                            {
                                if (!(flags & LWA_ALPHA))
                                    alpha = 255;
                            }
                            else
                            {
                                alpha = 255;
                            }

                            if (alpha == 255)
                            {
                                id = ID_OPACITY_OPAQUE;
                            }
                            else
                            {
                                id = 0;

                                // Due to integer division, we cannot use simple arithmetic to calculate which menu item to check.
                                for (i = 0; i < 10; i++)
                                {
                                    if (alpha == (BYTE)(255 * (i + 1) / 10))
                                    {
                                        id = ID_OPACITY_10 + i;
                                        break;
                                    }
                                }
                            }

                            if (id != 0)
                            {
                                CheckMenuRadioItem(subMenu, ID_OPACITY_10, ID_OPACITY_OPAQUE, id, MF_BYCOMMAND);
                            }
                        }
                        else
                        {
                            PhEnableAllMenuItems(subMenu, FALSE);
                            PhEnableMenuItem(subMenu, ID_WINDOW_COPY, TRUE);
                        }

                        TrackPopupMenu(
                            subMenu,
                            TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
                            point.x,
                            point.y,
                            0,
                            hwndDlg,
                            NULL
                            );

                        DestroyMenu(menu);
                    }
                }
                break;
            case ID_WINDOW_BRINGTOFRONT:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        WINDOWPLACEMENT placement = { sizeof(placement) };

                        GetWindowPlacement(selectedNode->WindowHandle, &placement);

                        if (placement.showCmd == SW_MINIMIZE)
                            ShowWindowAsync(selectedNode->WindowHandle, SW_RESTORE);
                        else
                            SetForegroundWindow(selectedNode->WindowHandle);
                    }
                }
                break;
            case ID_WINDOW_RESTORE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        ShowWindowAsync(selectedNode->WindowHandle, SW_RESTORE);
                    }
                }
                break;
            case ID_WINDOW_MINIMIZE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        ShowWindowAsync(selectedNode->WindowHandle, SW_MINIMIZE);
                    }
                }
                break;
            case ID_WINDOW_MAXIMIZE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        ShowWindowAsync(selectedNode->WindowHandle, SW_MAXIMIZE);
                    }
                }
                break;
            case ID_WINDOW_CLOSE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        PostMessage(selectedNode->WindowHandle, WM_CLOSE, 0, 0);
                    }
                }
                break;
            case ID_WINDOW_VISIBLE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        if (IsWindowVisible(selectedNode->WindowHandle))
                        {
                            selectedNode->WindowVisible = FALSE;
                            ShowWindowAsync(selectedNode->WindowHandle, SW_HIDE);
                        }
                        else
                        {
                            selectedNode->WindowVisible = TRUE;
                            ShowWindowAsync(selectedNode->WindowHandle, SW_SHOW);
                        }

                        PhInvalidateTreeNewNode(&selectedNode->Node, TN_CACHE_COLOR);
                        TreeNew_InvalidateNode(context->TreeNewHandle, &selectedNode->Node);
                    }
                }
                break;
            case ID_WINDOW_ENABLED:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        EnableWindow(selectedNode->WindowHandle, !IsWindowEnabled(selectedNode->WindowHandle));
                    }
                }
                break;
            case ID_WINDOW_ALWAYSONTOP:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        LOGICAL topMost;

                        topMost = GetWindowLong(selectedNode->WindowHandle, GWL_EXSTYLE) & WS_EX_TOPMOST;
                        SetWindowPos(selectedNode->WindowHandle, topMost ? HWND_NOTOPMOST : HWND_TOPMOST,
                            0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
                    }
                }
                break;
            case ID_OPACITY_10:
            case ID_OPACITY_20:
            case ID_OPACITY_30:
            case ID_OPACITY_40:
            case ID_OPACITY_50:
            case ID_OPACITY_60:
            case ID_OPACITY_70:
            case ID_OPACITY_80:
            case ID_OPACITY_90:
            case ID_OPACITY_OPAQUE:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        ULONG opacity;

                        opacity = ((ULONG)LOWORD(wParam) - ID_OPACITY_10) + 1;

                        if (opacity == 10)
                        {
                            // Remove the WS_EX_LAYERED bit since it is not needed.
                            PhSetWindowExStyle(selectedNode->WindowHandle, WS_EX_LAYERED, 0);
                            RedrawWindow(selectedNode->WindowHandle, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                        }
                        else
                        {
                            // Add the WS_EX_LAYERED bit so opacity will work.
                            PhSetWindowExStyle(selectedNode->WindowHandle, WS_EX_LAYERED, WS_EX_LAYERED);
                            SetLayeredWindowAttributes(selectedNode->WindowHandle, 0, (BYTE)(255 * opacity / 10), LWA_ALPHA);
                        }
                    }
                }
                break;
            case ID_WINDOW_HIGHLIGHT:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        if (context->HighlightingWindow)
                        {
                            if (context->HighlightingWindowCount & 1)
                                WeInvertWindowBorder(context->HighlightingWindow);
                        }

                        context->HighlightingWindow = selectedNode->WindowHandle;
                        context->HighlightingWindowCount = 10;
                        SetTimer(hwndDlg, 9, 100, NULL);
                    }
                }
                break;
            case ID_WINDOW_GOTOTHREAD:
                {
                    PWE_WINDOW_NODE selectedNode;
                    PPH_PROCESS_ITEM processItem;
                    PPH_PROCESS_PROPCONTEXT propContext;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                    {
                        if (processItem = PhReferenceProcessItem(selectedNode->ClientId.UniqueProcess))
                        {
                            if (propContext = PhCreateProcessPropContext(WE_PhMainWndHandle, processItem))
                            {
                                PhSetSelectThreadIdProcessPropContext(propContext, selectedNode->ClientId.UniqueThread);
                                PhShowProcessProperties(propContext);
                                PhDereferenceObject(propContext);
                            }

                            PhDereferenceObject(processItem);
                        }
                        else
                        {
                            PhShowError(hwndDlg, L"The process does not exist.");
                        }
                    }
                }
                break;
            case ID_WINDOW_PROPERTIES:
                {
                    PWE_WINDOW_NODE selectedNode;

                    if (selectedNode = WeGetSelectedWindowNode(&context->TreeContext))
                        WeShowWindowProperties(WE_PhMainWndHandle, selectedNode->WindowHandle);
                }
                break;
            case ID_WINDOW_COPY:
                {
                    PPH_STRING text;

                    text = PhGetTreeNewText(context->TreeNewHandle, 0);
                    PhSetClipboardStringEx(hwndDlg, text->Buffer, text->Length);
                    PhDereferenceObject(text);
                }
                break;
            }
        }
        break;
    case WM_TIMER:
        {
            switch (wParam)
            {
            case 9:
                {
                    WeInvertWindowBorder(context->HighlightingWindow);

                    if (--context->HighlightingWindowCount == 0)
                        KillTimer(hwndDlg, 9);
                }
                break;
            }
        }
        break;
    case WM_SIZE:
        {
            PhLayoutManagerLayout(&context->LayoutManager);
        }
        break;
    case WM_SIZING:
        {
            PhResizingMinimumSize((PRECT)lParam, wParam, MinimumSize.right, MinimumSize.bottom);
        }
        break;
    case WM_WE_PLUSMINUS:
        {
            PWE_WINDOW_NODE node = (PWE_WINDOW_NODE)lParam;

            if (!node->Opened)
            {
                TreeNew_SetRedraw(context->TreeNewHandle, FALSE);
                WepAddChildWindows(context, node, node->WindowHandle, NULL, NULL);
                node->Opened = TRUE;
                TreeNew_SetRedraw(context->TreeNewHandle, TRUE);
            }
        }
        break;
    }

    return FALSE;
}