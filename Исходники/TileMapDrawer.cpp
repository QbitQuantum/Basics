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
	int mX, mY;
	PAINTSTRUCT ps;
	HDC hdc;

	::GetClientRect(hWnd, &winRect);
	WorldRenderer worldHandle(hWnd, hdc, winRect, player);

	/*
	*/
	switch (message)
	{
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		worldHandle.update(playerAct);
		EndPaint(hWnd, &ps);
		break;	
	
	case WM_MOUSEMOVE:
		// 부드럽게 보이기 위해서는 잔상처리를 그대로 하는 게 더 부드럽게 보임
		// 잔상처리를 안할경우 화면이 번쩍거리는 현상이 보이게 됨
		mX = LOWORD(lParam); // x coordinate
		mY = HIWORD(lParam); // y coordinate
		/*
		*/
		switch (wParam){
		case MK_LBUTTON:
			if (player.moveFlag == true){
				player.pos = worldHandle.getPlayerCoordinate(mX, mY);
				player.curpos = { mX, mY };

				if (worldHandle.isCurInside(player)){
					player.obj = worldHandle.getTileCoordnate(mX, mY);
					hdc = ::GetDC(hWnd);
					::Ellipse(hdc, player.obj.left, player.obj.top, player.obj.right, player.obj.bottom);
					::ReleaseDC(hWnd, hdc);
					playerAct = true;
				}
				else if (playerAct){
					hdc = ::GetDC(hWnd);
					::Ellipse(hdc, player.obj.left, player.obj.top, player.obj.right, player.obj.bottom);
					::ReleaseDC(hWnd, hdc);
				}
				else{
					//
				}
			}
			break;				
		}			
		/*
		*/
		break;

	case WM_LBUTTONUP:
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_LBUTTONDOWN:
		mX = LOWORD(lParam); // x coordinate
		mY = HIWORD(lParam); // y coordinate

		//test
		if (player.pos.x == worldHandle.getPlayerCoordinate(mX, mY).x &&
			player.pos.y == worldHandle.getPlayerCoordinate(mX, mY).y){
			player.moveFlag = true;
		}
		else {
			player.moveFlag = false;
		}
		//

		player.pos = worldHandle.getPlayerCoordinate(mX, mY);
		player.curpos = { mX, mY };

		if ( worldHandle.isCurInside(player) ){
			player.obj = worldHandle.getTileCoordnate(mX, mY);
			InvalidateRect(hWnd, NULL, true);
			playerAct = true;
		}
		else if(playerAct){
			InvalidateRect(hWnd, NULL, true);
		}
		else{
			playerAct = false;
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