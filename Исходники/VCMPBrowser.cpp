LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static uint32_t lanLastPing = 0;
	static HFONT _hFont = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		HFONT hFont = 0;

		NONCLIENTMETRICS ncm = { sizeof(ncm) };
		if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0))
		{
			hFont = CreateFontIndirect(&ncm.lfMessageFont);
			_hFont = hFont;
		}
		if (!hFont)
			hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		RECT rcClient;
		GetClientRect(hWnd, &rcClient);

		g_hWndListViewServers = CreateWindow(WC_LISTVIEW, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_AUTOARRANGE | LVS_OWNERDATA, 1, 21, rcClient.right - UI_PLAYERLIST_WIDTH - 4, rcClient.bottom - UI_SERVERINFO_HEIGHT - 21 - 2, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndListViewServers)
		{
			SetWindowTheme(g_hWndListViewServers, L"Explorer", nullptr);
			ListView_SetExtendedListViewStyle(g_hWndListViewServers, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

			LVCOLUMN lvc;
			lvc.mask = LVCF_WIDTH;
			lvc.cx = 30;
			ListView_InsertColumn(g_hWndListViewServers, 0, &lvc);

			lvc.mask = LVCF_WIDTH | LVCF_TEXT;
			lvc.cx = 240;
			lvc.pszText = LoadStr(L"Server Name", IDS_SERVERNAME);
			ListView_InsertColumn(g_hWndListViewServers, 1, &lvc);

			lvc.cx = 60;
			lvc.pszText = LoadStr(L"Ping", IDS_PING);
			ListView_InsertColumn(g_hWndListViewServers, 2, &lvc);

			lvc.cx = 80;
			lvc.pszText = LoadStr(L"Players", IDS_PLAYERS);
			ListView_InsertColumn(g_hWndListViewServers, 3, &lvc);

			lvc.cx = 70;
			lvc.pszText = LoadStr(L"Version", IDS_VERSION);
			ListView_InsertColumn(g_hWndListViewServers, 4, &lvc);

			lvc.cx = 120;
			lvc.pszText = LoadStr(L"Gamemode", IDS_GAMEMODE);
			ListView_InsertColumn(g_hWndListViewServers, 5, &lvc);

			lvc.cx = 100;
			lvc.pszText = LoadStr(L"Map Name", IDS_MAPNAME);
			ListView_InsertColumn(g_hWndListViewServers, 6, &lvc);
		}

		g_hWndListViewHistory = CreateWindow(WC_LISTVIEW, nullptr, WS_CHILD | WS_CLIPSIBLINGS | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_AUTOARRANGE | LVS_OWNERDATA, 1, 21, rcClient.right - UI_PLAYERLIST_WIDTH - 4, rcClient.bottom - UI_SERVERINFO_HEIGHT - 21 - 2, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndListViewHistory)
		{
			SetWindowTheme(g_hWndListViewHistory, L"Explorer", nullptr);
			ListView_SetExtendedListViewStyle(g_hWndListViewHistory, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

			LVCOLUMN lvc;
			lvc.mask = LVCF_WIDTH;
			lvc.cx = 30;
			ListView_InsertColumn(g_hWndListViewHistory, 0, &lvc);

			lvc.mask = LVCF_WIDTH | LVCF_TEXT;
			lvc.cx = 220;
			lvc.pszText = LoadStr(L"Server Name", IDS_SERVERNAME);
			ListView_InsertColumn(g_hWndListViewHistory, 1, &lvc);

			lvc.cx = 60;
			lvc.pszText = LoadStr(L"Ping", IDS_PING);
			ListView_InsertColumn(g_hWndListViewHistory, 2, &lvc);

			lvc.cx = 80;
			lvc.pszText = LoadStr(L"Players", IDS_PLAYERS);
			ListView_InsertColumn(g_hWndListViewHistory, 3, &lvc);

			lvc.cx = 70;
			lvc.pszText = LoadStr(L"Version", IDS_VERSION);
			ListView_InsertColumn(g_hWndListViewHistory, 4, &lvc);

			lvc.cx = 100;
			lvc.pszText = LoadStr(L"Gamemode", IDS_GAMEMODE);
			ListView_InsertColumn(g_hWndListViewHistory, 5, &lvc);

			lvc.cx = 160;
			lvc.pszText = LoadStr(L"Last Played", IDS_LASTPLAYED);
			ListView_InsertColumn(g_hWndListViewHistory, 6, &lvc);
		}

		g_hWndTab = CreateWindow(WC_TABCONTROL, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, rcClient.right - UI_PLAYERLIST_WIDTH, rcClient.bottom - UI_SERVERINFO_HEIGHT, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndTab)
		{
			SetWindowFont(g_hWndTab, hFont, FALSE);

			HIMAGELIST hTabIml = ImageList_Create(16, 16, ILC_COLOR32, 0, 0);
			if (hTabIml)
			{
				for (int i = IDI_FAVORITE; i <= IDI_HISTORY; ++i)
					ImageList_AddIcon(hTabIml, LoadIcon(g_hInst, MAKEINTRESOURCE(i)));
				TabCtrl_SetImageList(g_hWndTab, hTabIml);
			}

			TCITEM tie;
			tie.mask = TCIF_TEXT | TCIF_IMAGE;
			tie.iImage = 0;
			tie.pszText = LoadStr(L"Favorites", IDS_FAVORITES);
			TabCtrl_InsertItem(g_hWndTab, 0, &tie);

			tie.iImage = 1;
			tie.pszText = LoadStr(L"Internet", IDS_INTERNET);
			TabCtrl_InsertItem(g_hWndTab, 1, &tie);

			tie.iImage = 1;
			tie.pszText = LoadStr(L"Official", IDS_OFFICIAL);
			TabCtrl_InsertItem(g_hWndTab, 2, &tie);

			tie.iImage = 2;
			tie.pszText = LoadStr(L"Lan", IDS_LAN);
			TabCtrl_InsertItem(g_hWndTab, 3, &tie);

			tie.iImage = 3;
			tie.pszText = LoadStr(L"History", IDS_HISTORY);
			TabCtrl_InsertItem(g_hWndTab, 4, &tie);
		}

		g_hWndListViewPlayers = CreateWindowEx(0, WC_LISTVIEW, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOCOLUMNHEADER | LVS_SINGLESEL | LVS_OWNERDATA, rcClient.right - UI_PLAYERLIST_WIDTH + 1, 18, UI_PLAYERLIST_WIDTH - 2, rcClient.bottom - UI_SERVERINFO_HEIGHT - 18 - 2, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndListViewPlayers)
		{
			SetWindowTheme(g_hWndListViewPlayers, L"Explorer", nullptr);
			ListView_SetExtendedListViewStyle(g_hWndListViewPlayers, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

			LVCOLUMN lvc;
			lvc.mask = LVCF_WIDTH;
			lvc.cx = UI_PLAYERLIST_WIDTH - 2;
			ListView_InsertColumn(g_hWndListViewPlayers, 0, &lvc);
		}

		g_hWndGroupBox1 = CreateWindow(WC_BUTTON, LoadStr(L"Players", IDS_PLAYERSLIST), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | BS_GROUPBOX, rcClient.right - UI_PLAYERLIST_WIDTH, 0, UI_PLAYERLIST_WIDTH, rcClient.bottom - UI_SERVERINFO_HEIGHT, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndGroupBox1)
		{
			SetWindowFont(g_hWndGroupBox1, hFont, FALSE);
		}

		g_hWndGroupBox2 = CreateWindow(WC_BUTTON, LoadStr(L"Server Info", IDS_SERVERINFO), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | BS_GROUPBOX, 0, rcClient.bottom - UI_SERVERINFO_HEIGHT, rcClient.right, 118, hWnd, nullptr, g_hInst, nullptr);
		if (g_hWndGroupBox2)
		{
			SetWindowFont(g_hWndGroupBox2, hFont, FALSE);

			int y = 18;
#define LINE_GAP 20

			HWND hStatic = CreateWindow(WC_STATIC, LoadStr(L"Server Name:", IDS_SERVERNAME_), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SS_RIGHT, 10, y, 100, 16, g_hWndGroupBox2, nullptr, g_hInst, nullptr);
			if (hStatic) SetWindowFont(hStatic, hFont, FALSE);

			HWND hEdit = CreateWindow(WC_EDIT, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | ES_READONLY, 112, y, 300, 16, g_hWndGroupBox2, (HMENU)1001, g_hInst, nullptr);
			if (hEdit) SetWindowFont(hEdit, hFont, FALSE);
			y += LINE_GAP;

			hStatic = CreateWindow(WC_STATIC, LoadStr(L"Server IP:", IDS_SERVERIP), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SS_RIGHT, 10, y, 100, 16, g_hWndGroupBox2, nullptr, g_hInst, nullptr);
			if (hStatic) SetWindowFont(hStatic, hFont, FALSE);

			hEdit = CreateWindow(WC_EDIT, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | ES_READONLY, 112, y, 300, 16, g_hWndGroupBox2, (HMENU)1002, g_hInst, nullptr);
			if (hEdit) SetWindowFont(hEdit, hFont, FALSE);
			y += LINE_GAP;

			hStatic = CreateWindow(WC_STATIC, LoadStr(L"Server Players:", IDS_SERVERPLAYERS), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SS_RIGHT, 10, y, 100, 16, g_hWndGroupBox2, nullptr, g_hInst, nullptr);
			if (hStatic) SetWindowFont(hStatic, hFont, FALSE);

			hEdit = CreateWindow(WC_EDIT, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | ES_READONLY, 112, y, 300, 16, g_hWndGroupBox2, (HMENU)1003, g_hInst, nullptr);
			if (hEdit) SetWindowFont(hEdit, hFont, FALSE);
			y += LINE_GAP;

			hStatic = CreateWindow(WC_STATIC, LoadStr(L"Server Ping:", IDS_SERVERPING), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SS_RIGHT, 10, y, 100, 16, g_hWndGroupBox2, nullptr, g_hInst, nullptr);
			if (hStatic) SetWindowFont(hStatic, hFont, FALSE);

			hEdit = CreateWindow(WC_EDIT, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | ES_READONLY, 112, y, 300, 16, g_hWndGroupBox2, (HMENU)1004, g_hInst, nullptr);
			if (hEdit) SetWindowFont(hEdit, hFont, FALSE);
			y += LINE_GAP;

			hStatic = CreateWindow(WC_STATIC, LoadStr(L"Server Gamemode:", IDS_SERVERGAMEMODE), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SS_RIGHT, 10, y, 100, 16, g_hWndGroupBox2, nullptr, g_hInst, nullptr);
			if (hStatic) SetWindowFont(hStatic, hFont, FALSE);

			hEdit = CreateWindow(WC_EDIT, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | ES_READONLY, 112, y, 300, 16, g_hWndGroupBox2, (HMENU)1005, g_hInst, nullptr);
			if (hEdit) SetWindowFont(hEdit, hFont, FALSE);
		}

		g_hWndStatusBar = CreateWindow(STATUSCLASSNAME, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hWnd, nullptr, g_hInst, nullptr);

		do {
			g_UDPSocket = socket(AF_INET, SOCK_DGRAM, 0);
			if (g_UDPSocket == INVALID_SOCKET)
				break;

			uint32_t timeout = 2000;
			setsockopt(g_UDPSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

			struct sockaddr_in bindaddr = { AF_INET };
			if (bind(g_UDPSocket, (sockaddr *)&bindaddr, 16) != NO_ERROR)
			{
				closesocket(g_UDPSocket);
				break;
			}

			if (WSAAsyncSelect(g_UDPSocket, hWnd, WM_SOCKET, FD_READ) == SOCKET_ERROR)
			{
				closesocket(g_UDPSocket);
				break;
			}

			return 0;
		} while (0);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_TOOLS_SETTINGS:
			ShowSettings();
			break;
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE:
		{
			g_currentTab = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
			switch (g_currentTab)
			{
			case 0: // Favorites
			case 1: // Internet
			case 2: // Official
			case 3: // Lan
				ListView_DeleteAllItems(g_hWndListViewServers);
				ListView_DeleteAllItems(g_hWndListViewPlayers);
				g_serversList.clear();
				ShowWindow(g_hWndListViewServers, SW_SHOW);
				ShowWindow(g_hWndListViewHistory, SW_HIDE);
				UpdateWindow(g_hWndListViewServers);
				if (g_currentTab == 1 || g_currentTab == 2)
				{
					HWND hDialog = CreateDialog(g_hInst, MAKEINTRESOURCEW(IDD_LOADING), hWnd, nullptr);
					SetWindowPos(hDialog, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					UpdateWindow(hDialog);

					if (g_serversMasterList)
					{
						delete g_serversMasterList;
						g_serversMasterList = nullptr;
					}

					std::string data;
					data.reserve(2048);

					const char *url;
					if (g_currentTab == 1)
						url = (g_browserSettings.masterlistURL + "/servers").c_str();
					else
						url = (g_browserSettings.masterlistURL + "/official").c_str();
					CURLcode curlRet = CurlRequset(url, data, "VCMP/0.4");
					if (curlRet == CURLE_OK)
					{
						serverMasterList serversList;
						if (ParseJson(data.data(), serversList))
						{
							for (auto it = serversList.begin(); it != serversList.end(); ++it)
							{
								SendQuery(it->address, 'i');
								it->lastPing = GetTickCount();
							}
							g_serversMasterList = new serverMasterList(serversList);
						}
						else
						{
							MessageBox(hWnd, LoadStr(L"Can't parse master list data.", IDS_MASTERLISTDATA), LoadStr(L"Error", IDS_ERROR), MB_ICONWARNING);
						}
					}
					else
					{
						wchar_t message[512];
						swprintf_s(message, LoadStr(L"Can't get information from master list.\n%hs", IDS_MASTERLISTFAILED), curl_easy_strerror(curlRet));
						MessageBox(hWnd, message, LoadStr(L"Error", IDS_ERROR), MB_ICONWARNING);
					}

					DestroyWindow(hDialog);
				}
				else if (g_currentTab == 3)
				{
					BOOL broadcast = TRUE;
					setsockopt(g_UDPSocket, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof(broadcast));

					for (uint16_t port = 8000; port <= 8200; ++port)
					{
						serverAddress address = { INADDR_BROADCAST, port };
						SendQuery(address, 'i');
					}

					broadcast = FALSE;
					setsockopt(g_UDPSocket, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof(broadcast));

					lanLastPing = GetTickCount();
				}
				break;
			case 4: // History
				ShowWindow(g_hWndListViewHistory, SW_SHOW);
				ShowWindow(g_hWndListViewServers, SW_HIDE);
				break;
			}
		}
		break;
		case LVN_GETDISPINFO:
		{
			LPNMLVDISPINFOW di = (LPNMLVDISPINFOW)lParam;
			if (di->hdr.hwndFrom == g_hWndListViewServers)
			{
				size_t i = di->item.iItem;
				if (g_serversList.size() > i)
				{
					if (di->item.iSubItem == 0 && di->item.mask & LVIF_IMAGE)
						di->item.iImage = 0;

					if (di->item.mask & LVIF_TEXT)
					{
						switch (di->item.iSubItem)
						{
						case 0: // Icon
							break;
						case 1: // Server Name
							if (di->item.cchTextMax > 0 && di->item.pszText)
							{
								MultiByteToWideChar(CP_ACP, 0, g_serversList[i].info.serverName.c_str(), -1, di->item.pszText, di->item.cchTextMax);
							}
							break;
						case 2: // Ping
						{
							uint32_t ping = g_serversList[i].lastRecv - g_serversList[i].lastPing[1];
							_itow_s(ping, di->item.pszText, di->item.cchTextMax, 10);
						}
						break;
						case 3: // Players
							swprintf_s(di->item.pszText, di->item.cchTextMax, L"%hu/%hu", g_serversList[i].info.players, g_serversList[i].info.maxPlayers);
							break;
						case 4: // Version
						{
							MultiByteToWideChar(CP_ACP, 0, g_serversList[i].info.versionName, -1, di->item.pszText, di->item.cchTextMax);
						}
						break;
						case 5: // Gamemode
						{
							MultiByteToWideChar(CP_ACP, 0, g_serversList[i].info.gameMode.c_str(), -1, di->item.pszText, di->item.cchTextMax);
						}
						break;
						case 6: // Map name
						{
							MultiByteToWideChar(CP_ACP, 0, g_serversList[i].info.mapName.c_str(), -1, di->item.pszText, di->item.cchTextMax);
						}
						break;
						}
					}
				}
			}
			else if (di->hdr.hwndFrom == g_hWndListViewHistory) // FIXME
			{

			}
			else if (di->hdr.hwndFrom == g_hWndListViewPlayers)
			{
				size_t i = ListView_GetSelectionMark(g_hWndListViewServers);
				if (g_serversList.size() > i)
				{
					serverPlayers &players = g_serversList[i].players;

					size_t j = di->item.iItem;
					if (players.size() > j)
					{
						if (di->item.mask & LVIF_TEXT)
						{
							MultiByteToWideChar(CP_ACP, 0, players[j].name, -1, di->item.pszText, di->item.cchTextMax);
						}
					}
				}
			}
		}
		break;
		case NM_CUSTOMDRAW:
		{
			LPNMLVCUSTOMDRAW nmcd = (LPNMLVCUSTOMDRAW)lParam;
			if (nmcd->nmcd.hdr.hwndFrom == g_hWndListViewServers)
			{
				switch (nmcd->nmcd.dwDrawStage)
				{
				case CDDS_PREPAINT:
					return CDRF_NOTIFYITEMDRAW;
				case CDDS_ITEMPREPAINT:
				{
					COLORREF crText;
					size_t i = nmcd->nmcd.dwItemSpec;
					if (g_serversList.size() > i && g_serversList[i].isOfficial)
						crText = g_browserSettings.officialColor;
					else
						crText = 0;

					nmcd->clrText = crText;
					return CDRF_DODEFAULT;
				}
				}
			}
		}
		break;
		case LVN_ITEMCHANGED:
		{
			LPNMITEMACTIVATE nmitem = (LPNMITEMACTIVATE)lParam;
			if (nmitem->hdr.hwndFrom == g_hWndListViewServers)
			{
				size_t i = nmitem->iItem;
				if (i != -1 && g_serversList.size() > i)
				{
					if (g_serversList[i].info.players == 0)
						ListView_DeleteAllItems(g_hWndListViewPlayers);

					std::wstring wstr;

					ConvertCharset(g_serversList[i].info.serverName.c_str(), wstr);
					SetDlgItemText(g_hWndGroupBox2, 1001, wstr.c_str()); // Server Name

					wchar_t ipstr[22];
					char *ip = (char *)&(g_serversList[i].address.ip);
					swprintf_s(ipstr, L"%hhu.%hhu.%hhu.%hhu:%hu", ip[0], ip[1], ip[2], ip[3], g_serversList[i].address.port);
					SetDlgItemText(g_hWndGroupBox2, 1002, ipstr); // Server IP

					wchar_t playersstr[12];
					swprintf_s(playersstr, L"%hu/%hu", g_serversList[i].info.players, g_serversList[i].info.maxPlayers);
					SetDlgItemText(g_hWndGroupBox2, 1003, playersstr); // Server Players

					wchar_t pingsstr[12];
					uint32_t ping = g_serversList[i].lastRecv - g_serversList[i].lastPing[1];
					_itow_s(ping, pingsstr, 10);
					SetDlgItemText(g_hWndGroupBox2, 1004, pingsstr); // Server Ping

					ConvertCharset(g_serversList[i].info.gameMode.c_str(), wstr);
					SetDlgItemText(g_hWndGroupBox2, 1005, wstr.c_str()); // Server Gamemode

					SendQuery(g_serversList[i].address, 'i');
					SendQuery(g_serversList[i].address, 'c');
					g_serversList[i].lastPing[0] = GetTickCount();
				}
				else
				{
					ListView_DeleteAllItems(g_hWndListViewPlayers);
					for (int i = 1001; i <= 1005; ++i)
						SetDlgItemText(g_hWndGroupBox2, i, nullptr);
				}
			}
		}
		break;
		case LVN_ITEMACTIVATE:
		{
			LPNMITEMACTIVATE nmia = (LPNMITEMACTIVATE)lParam;
			if (nmia->hdr.hwndFrom == g_hWndListViewServers)
			{
				size_t i = nmia->iItem;
				if (i != -1 && g_serversList.size() > i)
				{
					char ipstr[16];
					char *ip = (char *)&(g_serversList[i].address.ip);
					snprintf(ipstr, sizeof(ipstr), "%hhu.%hhu.%hhu.%hhu", ip[0], ip[1], ip[2], ip[3]);
					char vcmpDll[MAX_PATH];
					snprintf(vcmpDll, sizeof(vcmpDll), "%ls%s\\vcmp-game.dll", g_exePath, g_serversList[i].info.versionName);
					LaunchVCMP(ipstr, g_serversList[i].address.port, g_browserSettings.playerName, nullptr, g_browserSettings.gamePath, vcmpDll);
				}
			}
		}
		break;
		}
	}
	break;
	case WM_SIZE:
	{
		int clientWidth = GET_X_LPARAM(lParam), clientHeight = GET_Y_LPARAM(lParam);
		SetWindowPos(g_hWndTab, 0, 0, 0, clientWidth - UI_PLAYERLIST_WIDTH, clientHeight - UI_SERVERINFO_HEIGHT, SWP_NOZORDER);
		SetWindowPos(g_hWndListViewServers, 0, 1, 21, clientWidth - UI_PLAYERLIST_WIDTH - 4, clientHeight - UI_SERVERINFO_HEIGHT - 21 - 2, SWP_NOZORDER);
		SetWindowPos(g_hWndListViewHistory, 0, 1, 21, clientWidth - UI_PLAYERLIST_WIDTH - 4, clientHeight - UI_SERVERINFO_HEIGHT - 21 - 2, SWP_NOZORDER);
		SetWindowPos(g_hWndGroupBox1, 0, clientWidth - UI_PLAYERLIST_WIDTH, 0, UI_PLAYERLIST_WIDTH, clientHeight - UI_SERVERINFO_HEIGHT, SWP_NOZORDER);
		SetWindowPos(g_hWndListViewPlayers, 0, clientWidth - UI_PLAYERLIST_WIDTH + 1, 18, UI_PLAYERLIST_WIDTH - 2, clientHeight - UI_SERVERINFO_HEIGHT - 18 - 2, SWP_NOZORDER);
		SetWindowPos(g_hWndGroupBox2, 0, 0, clientHeight - UI_SERVERINFO_HEIGHT, clientWidth, 118, SWP_NOZORDER);
		SendMessage(g_hWndStatusBar, WM_SIZE, 0, 0);
	}
	break;
	case WM_GETMINMAXINFO:
		((LPMINMAXINFO)lParam)->ptMinTrackSize = { 750, 500 };
		break;
	case WM_DESTROY:
		if (_hFont)
			DeleteObject(_hFont);
		PostQuitMessage(0);
		break;
	case WM_SOCKET:
	{
		if (WSAGETSELECTEVENT(lParam) == FD_READ)
		{
			char *recvBuf = (char *)calloc(1024, sizeof(char));
			if (recvBuf)
			{
				struct sockaddr_in recvAddr;
				int addrLen = sizeof(recvAddr);
				int recvLen = recvfrom(g_UDPSocket, recvBuf, 1024, 0, (sockaddr *)&recvAddr, &addrLen);
				if (recvLen != -1 && recvLen >= 11)
				{
					if (recvLen > 1024)
						recvLen = 1024;

					if (*(int *)recvBuf == 0x3430504D) // MP04
					{
						char opcode = recvBuf[10];
						if (opcode == 'i' || opcode == 'c')
						{
							uint32_t ip = recvAddr.sin_addr.s_addr;
							uint16_t port = ntohs(recvAddr.sin_port);

							bool found = false;
							serverMasterListInfo masterInfo;
							if (g_currentTab == 1 || g_currentTab == 2)
							{
								for (auto it = g_serversMasterList->begin(); it != g_serversMasterList->end(); ++it)
								{
									if (it->address.ip == ip && it->address.port == port)
									{
										found = true;
										masterInfo = *it;
										break;
									}
								}
							}
							else if (g_currentTab == 3) // Lan
							{
								found = true;
								masterInfo.address = { ip, port };
								masterInfo.isOfficial = false;
								masterInfo.lastPing = lanLastPing;
							}

							if (found)
							{
								switch (opcode)
								{
								case 'i':
								{
									serverInfo info;
									if (GetServerInfo(recvBuf, recvLen, info))
									{
										bool inList = false;
										for (auto it = g_serversList.begin(); it != g_serversList.end(); ++it)
										{
											if (it->address.ip == ip && it->address.port == port)
											{
												inList = true;
												it->lastRecv = GetTickCount();
												it->lastPing[1] = it->lastPing[0];
												it->info = info;
												auto i = it - g_serversList.begin();
												ListView_Update(g_hWndListViewServers, i);
												break;
											}
										}
										if (!inList)
										{
											serverAllInfo allInfo;
											allInfo.address = masterInfo.address;
											allInfo.info = info;
											allInfo.isOfficial = masterInfo.isOfficial;
											allInfo.lastPing[0] = masterInfo.lastPing;
											allInfo.lastPing[1] = masterInfo.lastPing;
											allInfo.lastRecv = GetTickCount();
											g_serversList.push_back(allInfo);

											LVITEM lvi = { 0 };
											ListView_InsertItem(g_hWndListViewServers, &lvi);
										}
									}
								}
								break;
								case 'c':
								{
									serverPlayers players;
									if (GetServerPlayers(recvBuf, recvLen, players))
									{
										for (auto it = g_serversList.begin(); it != g_serversList.end(); ++it)
										{
											if (it->address.ip == ip && it->address.port == port)
											{
												it->lastRecv = GetTickCount();
												it->lastPing[1] = it->lastPing[0];
												it->players = players;
												auto i = it - g_serversList.begin();
												ListView_SetItemCount(g_hWndListViewPlayers, players.size());
												break;
											}
										}
									}
								}
								break;
								}
							}
						}
					}
				}
				free(recvBuf);
			}
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}