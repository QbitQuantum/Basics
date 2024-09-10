LRESULT GestureHandler::WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	bool gestureHandled = 0;
    GESTUREINFO  gi;
    ZeroMemory(&gi, sizeof(GESTUREINFO));
    gi.cbSize = sizeof(GESTUREINFO);
	BOOL result = GetGestureInfo((HGESTUREINFO)lParam, &gi);

	if(result)
	{
		switch(gi.dwID)
		{
			case GID_BEGIN:
			case GID_END:
				gestureHandled = 1;
				break;
			case GID_ZOOM:
				handleZoom(hWnd, gi);
				gestureHandled = 1;
				break;
			case GID_PAN:
				handlePan(hWnd, gi);
				gestureHandled = 1;
				break;
			case GID_ROTATE:
				handleRotate(hWnd, gi);
				gestureHandled = 1;
				break;
			case GID_TWOFINGERTAP:
				handle2FingerTap(hWnd, gi);
				gestureHandled = 1;
				break;
			case GID_PRESSANDTAP:
				handlePNT(hWnd, gi);
				gestureHandled = 1;
				break;
			default:
				gestureHandled = 0;
				break;
		}
	}
	else
	{
		//failed to get gesture info
	}

	if (gestureHandled)
    {
        CloseGestureInfoHandle((HGESTUREINFO)lParam);
    }
	else
    {
        DefWindowProc(hWnd, WM_GESTURE, wParam, lParam);
    }

	return (GID_END | GID_ZOOM | GID_PAN | GID_ROTATE | GID_TWOFINGERTAP | GID_PRESSANDTAP) << 1;
}