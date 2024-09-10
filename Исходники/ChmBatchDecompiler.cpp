//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
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
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
    case WM_ACTIVATE:  // Add to enable tab stop for window, see "http://stackoverflow.com/questions/5691724/c-winapi-how-to-switch-between-controls-using-tab-key"
        if (!wParam)
            g_hDlg = NULL;
        else
            g_hDlg = hWnd;
        break;

    case WM_CREATE:
        for (size_t i = 0; i < sizeof(g_controlDatas) / sizeof(g_controlDatas[0]); i++) {
            g_controlDatas[i].hWnd = CreateWindow(g_controlDatas[i].lpszClass, g_controlDatas[i].lpszCaption, g_controlDatas[i].dwStyle, g_controlDatas[i].x, g_controlDatas[i].y, g_controlDatas[i].w, g_controlDatas[i].h, hWnd, (HMENU)g_controlDatas[i].nId, NULL, hInst);
            g_controlMap[g_controlDatas[i].nId] = g_controlDatas[i].hWnd;
        }
        SendMessage(g_controlMap[ID_PROGRESS_1], PBM_SETSTEP, (WPARAM)1, 0);

        // Create Logger
        g_logger.Set(hWnd, L"NorthBright", L"ChmBatchDecompiler", OnLog);
        g_logger.DeleteLogFile();

        break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

        case ID_BUTTON_1:
            Util::OpenSelectFolderDialog(hWnd, L"Input Folder:", g_wstrInputFolder);
            SetWindowText(g_controlMap[ID_EDIT_1], g_wstrInputFolder.c_str());
            break;

        case ID_BUTTON_2:
            Util::OpenSelectFolderDialog(hWnd, L"Output Folder:", g_wstrOutputFolder);
            SetWindowText(g_controlMap[ID_EDIT_2], g_wstrOutputFolder.c_str());
            break;

        case ID_CHECKBOX_1:
            break;

        case ID_BUTTON_3:
            if (!g_chmDecompiler.IsRunning()) {
                Util::MyGetWindowText(g_controlMap[ID_EDIT_1], g_wstrInputFolder);
                if (g_wstrInputFolder.empty())
                    break;

                Util::MyGetWindowText(g_controlMap[ID_EDIT_2], g_wstrOutputFolder);
                if (g_wstrOutputFolder.empty())
                    break;

                g_fIncludeSubFolder = (bool)SendMessage(g_controlMap[ID_CHECKBOX_1], BM_GETCHECK, 0, 0);

                g_chmDecompiler.Set(g_wstrInputFolder.c_str(), g_wstrOutputFolder.c_str(), g_fIncludeSubFolder, hWnd, 4, &g_logger);
                g_chmDecompiler.Start();
                UpdateUI(g_chmDecompiler.IsRunning());
            }else {
                g_chmDecompiler.Stop();
                UpdateUI(g_chmDecompiler.IsRunning());
            }

            break;

        case ID_STATIC_4:
            ShellExecute (NULL, _T("open"), L"http://www.northbright.com", NULL, NULL, SW_SHOW);
            break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

    case WM_THREAD_GROUP_PROGRESS_CHANGED:
        SendMessage(g_controlMap[ID_PROGRESS_1], PBM_SETPOS, (WPARAM)lParam, 0);
        if ((int)lParam == 100)
            MessageBox(hWnd, L"Decompiled Successfully!", L"ChmBatchDecompiler", MB_OK);
        break;

    case WM_THREAD_GROUP_EXITED:
        if ((int)SendMessage(g_controlMap[ID_PROGRESS_1], PBM_GETPOS, 0, 0) < 100) {
            MessageBox(hWnd, L"Failed to decompile one or more CHM files.", L"ChmBatchDecompiler", MB_OK);
            g_chmDecompiler.m_pLogger->LaunchLogFile();
        }
        UpdateUI(false);
        break;

    case WM_THREAD_GROUP_STOPPED:
        UpdateUI(false);
        break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}