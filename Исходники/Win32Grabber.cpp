	void Win32Grabber::grabCursor(const Rect& rect, HDC hdc)
	{
		CURSORINFO cursorInfo = { 0 };
		cursorInfo.cbSize = sizeof(CURSORINFO);

		if (GetCursorInfo(&cursorInfo))
		{
			if (cursorInfo.flags == CURSOR_SHOWING)
			{
				ICONINFO iconInfo = { 0 };
				GetIconInfo(cursorInfo.hCursor, &iconInfo);

				POINT pos;
				GetCursorPos(&pos);

				int x = pos.x - rect.x - iconInfo.xHotspot;
				int y = pos.y - rect.y - iconInfo.yHotspot;
				DrawIconEx(hdc, x, y, cursorInfo.hCursor, 0, 0, 0, NULL, DI_NORMAL | DI_DEFAULTSIZE);

				DeleteObject(iconInfo.hbmColor);
				DeleteObject(iconInfo.hbmMask);
			}
		}
	}