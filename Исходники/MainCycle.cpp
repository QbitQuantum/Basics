LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_TIMER:
		InvalidateRgn(hWnd, 0, 1);
		RedrawWindow(hWnd, 0, 0, 0);// RDW_ERASE;
		break;

	case WM_PAINT:
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		mainloop(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		for (auto c : Circle::objectStorage)
		{
			InterfaceRobort* r = dynamic_cast<InterfaceRobort*>(c);
			if (r != nullptr) {
				r->moveToPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
		}
		break;
	case WM_LBUTTONDOWN:
		for (auto c : Circle::objectStorage)
		{
			InterfaceRobort* r = dynamic_cast<InterfaceRobort*>(c);
			if (r != nullptr) {
				r->moveToPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				Circle::objectStorage.push_back(new Bolt(r->x, r->y, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 10, r));
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}