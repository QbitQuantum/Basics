//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK cGameApplication::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pGameMgr->MsgProc(hWnd, message, wParam, lParam, _hInst);
	
	char buf[4096];
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;	
	//HWND hWndChild;

	switch (message)
	{		
	case WM_CREATE:{
		//SetTimer(hWnd, TIMER, 50, NULL);

		//CreateButton(L"Send", 10, 62, 50, 20, BUTTON1, hWnd, _hInst);
		//CreateButton(L"Start", 10, 42, 50, 20, BUTTON2, hWnd, _hInst);

		FILE *fp = fopen("server.ini", "r");
		if (fp == NULL)
		{
			//MessageBox(hWnd, L"Unable to open server.ini. Please specify server IPsddress in server.ini", L"Warning", MB_OK);
			//PostQuitMessage(NULL);
			cChatManager::GetInstance().addToChatLog("서버 파일 로드 불가");
			break;
		}

		while ((fgets(buf, 4096, fp)) != NULL)
		{
			if (buf[0] == '#')
				continue;
			sServerAddress = buf;

		}
		fclose(fp);

		if (sServerAddress.size() == 0)
		{
			cChatManager::GetInstance().addToChatLog("서버파일내에서 주소 로드 불가");
			break;
			//MessageBox(hWnd, L"Unable to find server IPaddress in server.ini", L"Warning", MB_OK);
			//PostQuitMessage(NULL);
		}

		TCHAR szProxyAddr[16];
		_tcscpy_s(szProxyAddr, CA2T(sServerAddress.c_str()));
		//
		//CreateEdit(szProxyAddr, 70, 42, 180, 20, EDIT2, hWnd, _hInst); // ip
		//CreateEdit(L"8084", 260, 42, 90, 20, EDIT3, hWnd, _hInst); // port
		//
		_hwMemo = CreateEdit(L"", 738, 686+1000, 254, 20+1000, EDIT1, hWnd, _hInst);
		CreateEdit(L"ID", 260, 62, 90, 20, EDIT4, hWnd, _hInst);		
		CreateMemo(L"Info.\n", 2-800, 85, 350, 120, MEMO1, hWnd, _hInst);

		//SetFocus(GetDlgItem(hWnd, BUTTON1));
		//EnableWindow(GetDlgItem(hWnd, BUTTON1), FALSE);
		EnableWindow(GetDlgItem(hWnd, EDIT1), FALSE);
		EnableWindow(GetDlgItem(hWnd, BUTTON2), TRUE);
		EnableWindow(GetDlgItem(hWnd, BUTTON2), FALSE);
		//EnableWindow(GetDlgItem(hWnd, BUTTON1), TRUE);
		EnableWindow(GetDlgItem(hWnd, EDIT2), FALSE);
		EnableWindow(GetDlgItem(hWnd, EDIT3), FALSE);

		MyMessObj.Init(sServerAddress, 8084);
		MyCharMessObj.Init(sServerAddress, 8085);

		if (!MyMessObj.IsConnected())
		{
			//MessageBox(hWnd, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
			cChatManager::GetInstance().addToChatLog("채팅 서버접속불가");
			EnableWindow(GetDlgItem(hWnd, EDIT1), FALSE);

			if (!MyCharMessObj.IsConnected()){
				cChatManager::GetInstance().addToChatLog("캐릭터서버접속불가");
			}

			break;
			//PostQuitMessage(NULL);
		}
		else if (!MyCharMessObj.IsConnected()){
			cChatManager::GetInstance().addToChatLog("캐릭터서버접속불가");
		}
		else {
			cChatManager::GetInstance().addToChatLog("채팅 및 캐릭터 서버접속완료");
		}
		EnableWindow(GetDlgItem(hWnd, EDIT1), TRUE);
		
		AfxBeginThread(MessageRecThread, 0);
		AfxBeginThread(MessageRecThread2, 0);
				
		SetFocus(hWnd);
		break;
	}
	case WM_SETFOCUS:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case EDIT1:
			SetWindowText(GetDlgItem(hWnd, EDIT1), L"");
			break;
		case EDIT4:
			SetWindowText(GetDlgItem(hWnd, EDIT4), L"");
			break;
		default:
			break;
		}
		break;
	/*case WM_TIMER:{
			
			break;
	}*/
	case WM_KEYUP:
		switch (wParam){
		case VK_RETURN : 
			if (IsWindowEnabled(GetDlgItem(hWnd, EDIT1))){
				g_pChatMgr->setInputString(">");
				SetFocus(_hwMemo);
			}			
			break;
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{		
		//case BUTTON2:
			//EnableWindow(GetDlgItem(hWnd, BUTTON2), FALSE);
			////EnableWindow(GetDlgItem(hWnd, BUTTON1), TRUE);
			//EnableWindow(GetDlgItem(hWnd, EDIT2), FALSE);
			//EnableWindow(GetDlgItem(hWnd, EDIT3), FALSE);
			//MyMessObj.Init(sServerAddress, 8084);
			//if (!MyMessObj.IsConnected())
			//{
			//	//MessageBox(hWnd, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
			//	cChatManager::GetInstance().addToChatLog("서버접속불가");
			//	//PostQuitMessage(NULL);
			//}
			//EnableWindow(GetDlgItem(hWnd, EDIT1), TRUE);
			//AfxBeginThread(MessageRecThread, 0);
			//SetFocus(GetDlgItem(hWnd, EDIT1));
			//break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
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