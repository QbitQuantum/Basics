//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    POINT point;
    char buf[1024];

    if(message == g_iTaskbarCreated)	// for PCRaw (tray icon)
        loadIcons(hInst, hWnd);

    switch (message)
    {
    case WM_SHOWGUI:
        createGUI(hWnd);
        break;


    case WM_TRAYICON:
        switch((UINT)lParam)
        {
        case WM_LBUTTONDOWN:
            if (allowTrayMenu)
                SendMessage(hWnd,WM_SHOWMENU,2,0);
            SetForegroundWindow(hWnd);
            break;
        case WM_RBUTTONDOWN:
            if (allowTrayMenu)
                SendMessage(hWnd,WM_SHOWMENU,1,0);
            SetForegroundWindow(hWnd);
            break;
        case WM_LBUTTONDBLCLK:
            createGUI(hWnd);
            break;
        }
        break;

    case WM_COPYDATA:
    {
        COPYDATASTRUCT *pc = (COPYDATASTRUCT *)lParam;
        LOG_DEBUG("URL request: %s",pc->lpData);
        if (pc->dwData == WM_PLAYCHANNEL)
        {
            ChanInfo info;
            servMgr->procConnectArgs((char *)pc->lpData,info);
            chanMgr->findAndPlayChannel(info,false);
        }
        //sys->callLocalURL((const char *)pc->lpData,servMgr->serverHost.port);
    }
    break;
    case WM_GETPORTNUMBER:
    {
        int port;
        port=servMgr->serverHost.port;
        ReplyMessage(port);
    }
    break;

    case WM_SHOWMENU:
    {
        if (servMgr->saveGuiPos) {
            CheckMenuItem(trayMenu, ID_POPUP_SAVE_GUI_POS, MF_CHECKED|MF_BYCOMMAND);
        } else {
            CheckMenuItem(trayMenu, ID_POPUP_SAVE_GUI_POS, MF_UNCHECKED|MF_BYCOMMAND);
        }

        SetForegroundWindow(hWnd);
        bool skipMenu=false;

        allowTrayMenu = false;

        // check for notifications
        if (currNotify & ServMgr::NT_UPGRADE)
        {
            if (servMgr->downloadURL[0])
            {
                if ((sys->getTime()-seenNewVersionTime) > (60*60))	// notify every hour
                {
                    if (MessageBox(hWnd,"A newer version of PeerCast is available, press OK to upgrade.","PeerCast",MB_OKCANCEL|MB_APPLMODAL|MB_ICONEXCLAMATION) == IDOK)
                        sys->getURL(servMgr->downloadURL);

                    seenNewVersionTime=sys->getTime();
                    skipMenu=true;
                }
            }
        }


        if (!skipMenu)
        {
            RECT rcWnd;
            HMENU menu;
            UINT flg = 0;

            SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWnd, 0);
            GetCursorPos(&point);

            if (point.x < rcWnd.left) {
                point.x = rcWnd.left;
                flg |= TPM_LEFTALIGN;
            }
            if (point.x > rcWnd.right) {
                point.x = rcWnd.right;
                flg |= TPM_RIGHTALIGN;
            }
            if (point.y < rcWnd.top) {
                point.y = rcWnd.top;
                flg |= TPM_TOPALIGN;
            }
            if (point.y > rcWnd.bottom) {
                point.y = rcWnd.bottom;
                flg |= TPM_BOTTOMALIGN;
            }
            if (flg == 0) {
                flg = TPM_RIGHTALIGN;
            }

            switch (wParam)
            {
            case 1:
                menu = GetSubMenu(trayMenu,0);
                addAllChannelsMenu(GetSubMenu(menu,0));
                addRelayedChannelsMenu(GetSubMenu(menu,1));
                break;
            case 2:
                menu = GetSubMenu(ltrayMenu,0);
                addAllChannelsMenu(menu);
                break;
            }
            if (!TrackPopupMenu(menu,flg,point.x,point.y,0,hWnd,NULL))
            {
                LOG_ERROR("Can`t track popup menu: %d",GetLastError());
            }
            PostMessage(hWnd,WM_NULL,0,0);

        }
        allowTrayMenu = true;
    }
    break;

    case WM_CREATE:
        if (showGUI)
            createGUI(hWnd);
        break;

    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        if ((wmId >= INFO_CMD) && (wmId < INFO_CMD+MAX_CHANNELS))
        {
            int c = wmId - INFO_CMD;
            chanInfo = getChannelInfo(c);
            chanInfoIsRelayed = false;
            if (winDistinctionNT)
                DialogBox(hInst, (LPCTSTR)IDD_CHANINFO, hWnd, (DLGPROC)ChanInfoProc);
            else
            {
                HWND WKDLG; //JP-Patch
                WKDLG = CreateDialog(hInst, (LPCTSTR)IDD_CHANINFO, hWnd, (DLGPROC)ChanInfoProc); //JP-Patch
                ShowWindow(WKDLG,SW_SHOWNORMAL); //JP-Patch
            }
            return 0;
        }
        if ((wmId >= URL_CMD) && (wmId < URL_CMD+MAX_CHANNELS))
        {
            int c = wmId - URL_CMD;
            chanInfo = getChannelInfo(c);
            if (chanInfo.url.isValidURL())
                sys->getURL(chanInfo.url);
            return 0;
        }
        if ((wmId >= PLAY_CMD) && (wmId < PLAY_CMD+MAX_CHANNELS))
        {
            int c = wmId - PLAY_CMD;
            chanInfo = getChannelInfo(c);
            chanMgr->findAndPlayChannel(chanInfo,false);
            return 0;
        }
        if ((wmId >= RELAY_CMD) && (wmId < RELAY_CMD+MAX_CHANNELS))
        {
            int c = wmId - RELAY_CMD;
            chanInfo = getChannelInfo(c);
            chanMgr->findAndPlayChannel(chanInfo,true);
            return 0;
        }

        // Parse the menu selections:
        switch (wmId)
        {
        case ID_POPUP_SHOWMESSAGES_PEERCAST:
            flipNotifyPopup(ID_POPUP_SHOWMESSAGES_PEERCAST,ServMgr::NT_PEERCAST);
            break;
        case ID_POPUP_SHOWMESSAGES_BROADCASTERS:
            flipNotifyPopup(ID_POPUP_SHOWMESSAGES_BROADCASTERS,ServMgr::NT_BROADCASTERS);
            break;
        case ID_POPUP_SHOWMESSAGES_TRACKINFO:
            flipNotifyPopup(ID_POPUP_SHOWMESSAGES_TRACKINFO,ServMgr::NT_TRACKINFO);
            break;

        case ID_POPUP_ABOUT:
        case IDM_ABOUT:
            DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            break;
        case ID_POPUP_SHOWGUI:
        case IDM_SETTINGS_GUI:
        case ID_POPUP_ADVANCED_SHOWGUI:
        {
            createGUI(hWnd);
            break;
        }
        case ID_POPUP_YELLOWPAGES:
            sys->getURL("http://yp.peercast.org/");
            break;
        case ID_POPUP_YELLOWPAGES1:
            sprintf(buf, "http://%s",servMgr->rootHost.cstr());
            sys->getURL(buf);
            break;
        case ID_POPUP_YELLOWPAGES2:
            sprintf(buf, "http://%s",servMgr->rootHost2.cstr());
            sys->getURL(buf);
            break;

        case ID_POPUP_ADVANCED_VIEWLOG:
            showHTML("viewlog.html");
            break;
        case ID_POPUP_ADVANCED_SAVESETTINGS:
            servMgr->saveSettings(iniFileName.cstr());
            break;
        case ID_POPUP_ADVANCED_INFORMATION:
            showHTML("index.html");
            break;
        case ID_FIND_CHANNELS:
        case ID_POPUP_ADVANCED_ALLCHANNELS:
        case ID_POPUP_UPGRADE:
            sys->callLocalURL("admin?cmd=upgrade",servMgr->serverHost.port);
            break;
        case ID_POPUP_ADVANCED_RELAYEDCHANNELS:
        case ID_POPUP_FAVORITES_EDIT:
            showHTML("relays.html");
            break;
        case ID_POPUP_ADVANCED_BROADCAST:
            showHTML("broadcast.html");
            break;
        case ID_POPUP_SETTINGS:
            showHTML("settings.html");
            break;
        case ID_POPUP_CONNECTIONS:
            showHTML("connections.html");
            break;
        case ID_POPUP_HELP:
            sys->getURL("http://www.peercast.org/help.php");
            break;

        case ID_POPUP_SAVE_GUI_POS:
            if (servMgr->saveGuiPos) {
                servMgr->saveGuiPos = false;
                CheckMenuItem(trayMenu, ID_POPUP_SAVE_GUI_POS, MF_UNCHECKED|MF_BYCOMMAND);
            } else {
                servMgr->saveGuiPos = true;
                CheckMenuItem(trayMenu, ID_POPUP_SAVE_GUI_POS, MF_CHECKED|MF_BYCOMMAND);
            }
            peercastInst->saveSettings();
            break;

        case ID_POPUP_KEEP_DOWNSTREAMS:
            if (servMgr->keepDownstreams) {
                servMgr->keepDownstreams = false;
                CheckMenuItem(trayMenu, ID_POPUP_KEEP_DOWNSTREAMS, MF_UNCHECKED|MF_BYCOMMAND);
            } else {
                servMgr->keepDownstreams = true;
                CheckMenuItem(trayMenu, ID_POPUP_KEEP_DOWNSTREAMS, MF_CHECKED|MF_BYCOMMAND);
            }
            //peercastInst->saveSettings();
            break;

        case ID_POPUP_EXIT_CONFIRM:
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}