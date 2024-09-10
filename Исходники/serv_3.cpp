LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		{
			hdc = BeginPaint(hWnd, &ps);// дескриптор л¤ отображени¤ элементов окна
			startButton = CreateWindowEx(0,TEXT("button"),TEXT("Start Server"),WS_VISIBLE|WS_CHILD,700, 20, 150, 30, hWnd, (HMENU)START_ID, hInst, 0);
			stopButton = CreateWindowEx(0,TEXT("button"),TEXT("Stop Server"),WS_VISIBLE|WS_CHILD,700, 60, 150, 30, hWnd, (HMENU)STOP_ID, hInst, 0);
			addButton = CreateWindowEx(0,TEXT("button"),TEXT("Add file"),WS_VISIBLE|WS_CHILD,700, 150, 150, 30, hWnd, (HMENU)ADD_ID, hInst, 0);
			exitButton = CreateWindowEx(0,TEXT("button"),TEXT("Exit"),WS_VISIBLE|WS_CHILD,700, 350, 150, 30, hWnd, (HMENU)EXIT_ID, hInst, 0);
			hEdit			= CreateWindowEx(	0,TEXT("edit"),TEXT("127.0.0.1"), WS_CHILD | WS_VISIBLE| ES_LEFT | ES_MULTILINE,60, 10, 400, 20, hWnd, (HMENU)EDIT_ID, hInst, 0);
			hEdit2			= CreateWindowEx(	0,TEXT("edit"),TEXT("12345"), WS_CHILD | WS_VISIBLE| ES_LEFT | ES_MULTILINE,60, 40, 400, 20, hWnd, (HMENU)EDIT2_ID, hInst, 0);
			hList			= CreateWindowEx(	0,TEXT("ListBox"),0,WS_CHILD | WS_VISIBLE| ES_LEFT|ES_NUMBER, 60, 130, 500, 400, hWnd, (HMENU)LIST_ID, hInst, 0);
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// –азобрать выбор:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case EXIT_ID:
			DestroyWindow(hWnd);
			break;
		case ADD_ID:
		{
			OPENFILENAME ofn;
			PSTR FileName  = new char [255];
			lstrcpy(FileName,"");
			ZeroMemory(&ofn,sizeof(ofn));										// очистим структуру
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = FileName;
			ofn.lpstrFilter = "WAV\0*.wav";// маскафильтра добавлени¤ файла
			ofn.nFilterIndex = 1;//айдишник структуры
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nMaxFile = 9999;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
			bool ret = GetOpenFileName(&ofn); 
			DefWindowProc(hWnd, WM_PAINT, wParam, lParam);
			SendMessage(hList,LB_ADDSTRING,wParam,(LPARAM)ofn.lpstrFile);
			SendMessage(hList,LB_SETCURSEL,0,0);
			break;
		}
		case START_ID:
		{
			WSAStartup(MAKEWORD(2,2), &wsaData);										// Initialize Winsock
			SendRecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);					// Create a SOCKET for connecting to server
			// Setup the TCP listening socket
			ServerAddr.sin_family=AF_INET;												//семейство адресов 
			char S[255];
			SendMessage(hEdit, WM_GETTEXT, 255, (LPARAM)S);
			ServerAddr.sin_addr.s_addr = inet_addr( S );
			SendMessage(hEdit2, WM_GETTEXT, 255, (LPARAM)S);
			int tmp = atoi(S); // число
			ServerAddr.sin_port=htons(tmp);
			err = bind( SendRecvSocket, (sockaddr *) &ServerAddr, sizeof(ServerAddr));	// св¤зывание адреса с сокетом
			if (err == SOCKET_ERROR) 
			{
				char strerr[256];
				int tmp = WSAGetLastError();
				sprintf(strerr,"%d",tmp);
				std::string tmp_S;
				tmp_S="ERROR number: ";
				tmp_S+=strerr;
				MessageBox(hWnd,(LPCSTR)strerr,tmp_S.c_str(),  MB_ICONERROR);
				closesocket(SendRecvSocket);
				WSACleanup();
				break;
			}
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind;
			int el=-100;
			el=SendMessage(hList,LB_GETCURSEL,0,0);
			if (el==-1)
			{
				MessageBox(hWnd,"Add element", "ERROR", MB_ICONERROR);
				closesocket(SendRecvSocket);
				WSACleanup();
				break;
			}
			SendMessage(hList,LB_GETTEXT, el, (LPARAM)TransFileName);
			hFind = FindFirstFile((LPCSTR)TransFileName, &FindFileData);
			FindClose(hFind);
			ifs.open(TransFileName,std::ios_base::binary);
			SetTimer(hWnd,100500,50,NULL);
			break;
		}
		case STOP_ID:
		{
			KillTimer(hWnd,100500);
			if (ifs.is_open()) ifs.close();
			closesocket(SendRecvSocket);
			WSACleanup();
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// добавьть любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		{
			if(wParam==100500)
			{
				DWORD val = 20; // ждем 20 мс
				setsockopt (SendRecvSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&val, sizeof DWORD);		//без этого вызова висим вечно
				err = recvfrom(SendRecvSocket,recvbuf,maxlen,0,(sockaddr *)&ClientAddr,&ClientAddrSize);
				if (err > 0) 
				{
					recvbuf[err]=0;
					std::string inS, FunctionS, ComandS;
					inS = (char* )recvbuf;
					int i =0;
					while ((i<inS.length()) && (inS[i] != ' '))
						ComandS +=inS[i++];
					int comand = atoi(ComandS.c_str());
					if (comand == 1)
					{
						const int NN=sizeof(sWaveHeader);
						char* buf=new char[NN];
						int k=0;
						if (ifs.peek()!=EOF)
						{
							for (int j =0; j<NN; ++j)
							{
								buf[k]=ifs.get();
								++k;
								if (ifs.peek()==EOF)
									break;
							}
						}
						sWaveHeader Hdr;
						copybuf(reinterpret_cast<char*>(&Hdr),buf, sizeof(sWaveHeader));
						sendto(SendRecvSocket,buf,k,0,(sockaddr *)&ClientAddr,sizeof(ClientAddr));		// отправл¤ем результат на сервер
						delete []buf;
					}
					if(comand>1)
					{
						++count_obr;
						const int NN=comand;
						char* buf=new char[NN];
						int k=0;
						if (ifs.peek()!=EOF)
						{
							for (int j =0; j<NN; ++j)
							{
								buf[k]=ifs.get();
								++k;
								if (ifs.peek()==EOF)
									break;
							}
						}
						sendto(SendRecvSocket,buf,k,0,(sockaddr *)&ClientAddr,sizeof(ClientAddr));			// отправл¤ем результат на сервер
						delete []buf;
					}

				}
				if (ifs.is_open())
					if (ifs.peek()==EOF)
					{
						KillTimer(hWnd,100500);
						if (ifs.is_open())ifs.close();
						closesocket(SendRecvSocket);
						WSACleanup();

						char tmp_count[256];
						sprintf(tmp_count,"%d",count_obr);
						std::string message_i;
						message_i = TransFileName;
						message_i+= "  file transfer is complete. count_obr = ";
						message_i+= tmp_count;
						MessageBox(hWnd, message_i.c_str(),"Information", MB_ICONINFORMATION);
					}
			}
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}