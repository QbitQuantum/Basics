LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static BOOL bnowDraw = FALSE;
	int retval;
	PAINTSTRUCT ps;
	//static point line;
	static HANDLE hTimer;
	
	HBRUSH MyBrush, OldBrush;
	HPEN Mypen, Oldpen;

	static int CH_x, CH_y;			//케릭터 좌표
	static int direction;
	static int num;					//배게 번호

	static bool pillow[5];			//배게 5개 랜덤 등장
	static bool have_pillow;

	static int hori;				// x축		0-> 초기 1-> + 2-> -
	static int verti;				// y축

	static bool shoot;				// 총알(한번에 열개 까지)
										// 서버에서는 쏘았다는 신호만 보내 줄 것
	static int shootCount;
	static int pillow_x[5], pillow_y[5];	//배게의 위치

	switch (iMessage) {
	case WM_CREATE:

		// 윈속 초기화
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			return 1;

		// socket()
		Mysock =WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
		if (Mysock == INVALID_SOCKET) err_quit("socket()");

		// connect()
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
		serveraddr.sin_port = htons(SERVERPORT);
		retval = WSAConnect(Mysock, (sockaddr *)&serveraddr, sizeof(serveraddr),
			NULL, NULL, NULL, NULL);
		if (retval == SOCKET_ERROR) err_quit("connect()");

		WSAAsyncSelect(Mysock, hWnd, WM_SOCKET, FD_CLOSE | FD_READ);

		sendWSA.buf = send_buf;
		sendWSA.len = BUFSIZE;
		recvWSA.buf = recv_buf;
		recvWSA.len = BUFSIZE;

		// 데이터 통신에 사용할 변수
		char buf[BUFSIZE + 1];
		int len;
		return 0;
		hori = 0;
		verti = 0;
		shootCount = 0;
		shoot = false;

		//hTimer = (HANDLE)SetTimer(hWnd, 1, 30, NULL);

		return 0;

	case WM_KEYDOWN:{
		
		if (GameStart){
			//CS_ShootKey *shootkey = reinterpret_cast<CS_ShootKey*>(send_buf);
			CS_key *key = reinterpret_cast<CS_key*> (send_buf);
			if (wParam == VK_RIGHT){
				hori = 1;
				verti = 0;
			}
			if (wParam == VK_LEFT){
				hori = 2;
				verti = 0;
			}
			if (wParam == VK_UP){
				verti = 1;
				hori = 0;
			}
			if (wParam == VK_DOWN){
				verti = 2;
				hori = 0;
			}/*if (wParam == VK_SPACE){
				shoot = true;
			}*/
			key->type = CS_KEY;
			key->size = sizeof(CS_key);
			sendWSA.len = sizeof(CS_key);

			int ret;
			DWORD iobyte;
			if (0 != hori){
				if (1 == hori) {
					key->movetype = KEY_RIGHT;
					key->direction = 1;
				}
				else{
					key->movetype = KEY_LEFT;
					key->direction = 2;
				}
			}
			if (0 != verti){
				if (1 == verti) {
					key->movetype = KEY_UP;
					key->direction = 3;
				}
				else {
					key->movetype = KEY_DOWN;
					key->direction = 4;
				}
			}
			ret = WSASend(Mysock, &sendWSA, 1, &iobyte, 0, NULL, NULL);
			if (ret){
				int error_code = WSAGetLastError();
				printf("Error while sending packet[%d]", error_code);
			}


			//InvalidateRect(hWnd, NULL, TRUE);
		}
	}
		return 0;

	case WM_KEYUP:
		shoot = false;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//게임 공간
		Rectangle(hdc, 20, 20, 400, 400);

		//임시 케릭터
		if (Mych){
			MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
			OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
			Mypen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			Oldpen = (HPEN)SelectObject(hdc, Mypen);
			Ellipse(hdc, pl.x, pl.y, pl.x + 20, pl.y + 20);		//캐릭터 본체(원형)
			
			//if (direction == 1){								//방향 삼각형(오른쪽)
			//	MoveToEx(hdc, pl.x + 20, pl.y, NULL);
			//	LineTo(hdc, pl.x + 20, pl.y + 20);
			//	MoveToEx(hdc, pl.x + 20, pl.y + 20, NULL);
			//	LineTo(hdc, pl.x + 30, pl.y + 10);
			//	MoveToEx(hdc, pl.x + 30, pl.y + 10, NULL);
			//	LineTo(hdc, pl.x + 20, pl.y);
			//}if (direction == 2){								//방향 삼각형(왼쪽)
			//	MoveToEx(hdc, pl.x, pl.y, NULL);
			//	LineTo(hdc, pl.x, pl.y + 20);
			//	MoveToEx(hdc, pl.x, pl.y + 20, NULL);
			//	LineTo(hdc, pl.x - 10, pl.y + 10);
			//	MoveToEx(hdc, pl.x - 10, pl.y + 10, NULL);
			//	LineTo(hdc, pl.x, pl.y);
			//}if (direction == 3){								//방향 삼각형(위)
			//	MoveToEx(hdc, pl.x, pl.y, NULL);
			//	LineTo(hdc, pl.x + 20, pl.y);
			//	MoveToEx(hdc, pl.x + 20, pl.y, NULL);
			//	LineTo(hdc, pl.x + 10, pl.y - 10);
			//	MoveToEx(hdc, pl.x + 10, pl.y - 10, NULL);
			//	LineTo(hdc, pl.x, pl.y);
			//}if (direction == 4){								//방향 삼각형(아래)
			//	MoveToEx(hdc, pl.x, pl.y + 20, NULL);
			//	LineTo(hdc, pl.x + 20, pl.y + 20);
			//	MoveToEx(hdc, pl.x + 20, pl.y + 20, NULL);
			//	LineTo(hdc, pl.x + 10, pl.y + 30);
			//	MoveToEx(hdc, pl.x + 10, pl.y + 30, NULL);
			//	LineTo(hdc, pl.x, pl.y + 20);
			//}
			SelectObject(hdc, OldBrush);
			SelectObject(hdc, Oldpen);
			DeleteObject(MyBrush);
			DeleteObject(Mypen);
		}
		for (int i = 0; i <  8; ++i){
			if (Enemych[i]){	// 타 플레이어

				MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
				OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
				Mypen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				Oldpen = (HPEN)SelectObject(hdc, Mypen);
				Ellipse(hdc, enemy[i].x, enemy[i].y, enemy[i].x + 20, enemy[i].y + 20);		//캐릭터 본체(원형)

				//if (direction == 1){								//방향 삼각형(오른쪽)
				//	MoveToEx(hdc, enemy[i].x + 20, enemy[i].y, NULL);
				//	LineTo(hdc, enemy[i].x + 20, enemy[i].y + 20);
				//	MoveToEx(hdc, enemy[i].x + 20, enemy[i].y + 20, NULL);
				//	LineTo(hdc, enemy[i].x + 30, enemy[i].y + 10);
				//	MoveToEx(hdc, enemy[i].x + 30, enemy[i].y + 10, NULL);
				//	LineTo(hdc, enemy[i].x + 20, enemy[i].y);
				//}if (direction == 2){								//방향 삼각형(왼쪽)
				//	MoveToEx(hdc, enemy[i].x, enemy[i].y, NULL);
				//	LineTo(hdc, enemy[i].x, enemy[i].y + 20);
				//	MoveToEx(hdc, enemy[i].x, enemy[i].y + 20, NULL);
				//	LineTo(hdc, enemy[i].x - 10, enemy[i].y + 10);
				//	MoveToEx(hdc, enemy[i].x - 10, enemy[i].y + 10, NULL);
				//	LineTo(hdc, enemy[i].x, enemy[i].y);
				//}if (direction == 3){								//방향 삼각형(위)
				//	MoveToEx(hdc, enemy[i].x, enemy[i].y, NULL);
				//	LineTo(hdc, enemy[i].x + 20, enemy[i].y);
				//	MoveToEx(hdc, enemy[i].x + 20, enemy[i].y, NULL);
				//	LineTo(hdc, enemy[i].x + 10, enemy[i].y - 10);
				//	MoveToEx(hdc, enemy[i].x + 10, enemy[i].y - 10, NULL);
				//	LineTo(hdc, enemy[i].x, enemy[i].y);
				//}if (direction == 4){								//방향 삼각형(아래)
				//	MoveToEx(hdc, enemy[i].x, enemy[i].y + 20, NULL);
				//	LineTo(hdc, enemy[i].x + 20, enemy[i].y + 20);
				//	MoveToEx(hdc, enemy[i].x + 20, enemy[i].y + 20, NULL);
				//	LineTo(hdc, enemy[i].x + 10, enemy[i].y + 30);
				//	MoveToEx(hdc, enemy[i].x + 10, enemy[i].y + 30, NULL);
				//	LineTo(hdc, enemy[i].x, enemy[i].y + 20);
				//}			
				
				SelectObject(hdc, OldBrush);
				SelectObject(hdc, Oldpen);
				DeleteObject(MyBrush);
				DeleteObject(Mypen);

			}
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_SOCKET:
		if (WSAGETSELECTERROR(lParam)){
			closesocket((SOCKET)wParam);
			exit(-1);
			break;
		}
		switch (WSAGETSELECTEVENT(lParam)){
		case FD_READ:
			ReadPacket((SOCKET)wParam);
			break;
		case FD_CLOSE:
			closesocket((SOCKET)wParam);
			exit(-1);
			break;
		}
	default:break;
	

	case WM_DESTROY:
		//KillTimer(hWnd, 1);A
		PostQuitMessage(0);

		return 0;	
	
		}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}