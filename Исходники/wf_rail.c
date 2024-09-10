static void wf_rail_window_common(rdpContext* context, WINDOW_ORDER_INFO* orderInfo, WINDOW_STATE_ORDER* windowState)
{
	wfRailWindow* railWindow = NULL;
	wfContext* wfc = (wfContext*) context;
	RailClientContext* rail = wfc->rail;
	UINT32 fieldFlags = orderInfo->fieldFlags;

	PrintRailWindowState(orderInfo, windowState);

	if (fieldFlags & WINDOW_ORDER_STATE_NEW)
	{
		HANDLE hInstance;
		WCHAR* titleW = NULL;
		WNDCLASSEX wndClassEx;

		railWindow = (wfRailWindow*) calloc(1, sizeof(wfRailWindow));

		if (!railWindow)
			return;

		railWindow->wfc = wfc;

		railWindow->dwStyle = windowState->style;
		railWindow->dwStyle &= ~RAIL_DISABLED_WINDOW_STYLES;
		railWindow->dwExStyle = windowState->extendedStyle;
		railWindow->dwExStyle &= ~RAIL_DISABLED_EXTENDED_WINDOW_STYLES;

		railWindow->x = windowState->windowOffsetX;
		railWindow->y = windowState->windowOffsetY;
		railWindow->width = windowState->windowWidth;
		railWindow->height = windowState->windowHeight;

		if (fieldFlags & WINDOW_ORDER_FIELD_TITLE)
		{
			char* title = NULL;

			ConvertFromUnicode(CP_UTF8, 0, (WCHAR*) windowState->titleInfo.string,
				   windowState->titleInfo.length / 2, &title, 0, NULL, NULL);

			railWindow->title = title;
		}
		else
		{
			railWindow->title = _strdup("RdpRailWindow");
		}

		ConvertToUnicode(CP_UTF8, 0, railWindow->title, -1, &titleW, 0);

		hInstance = GetModuleHandle(NULL);

		ZeroMemory(&wndClassEx, sizeof(WNDCLASSEX));
		wndClassEx.cbSize = sizeof(WNDCLASSEX);
		wndClassEx.style = 0;
		wndClassEx.lpfnWndProc = wf_RailWndProc;
		wndClassEx.cbClsExtra = 0;
		wndClassEx.cbWndExtra = 0;
		wndClassEx.hIcon = NULL;
		wndClassEx.hCursor = NULL;
		wndClassEx.hbrBackground = NULL;
		wndClassEx.lpszMenuName = NULL;
		wndClassEx.lpszClassName = _T("RdpRailWindow");
		wndClassEx.hInstance = hInstance;
		wndClassEx.hIconSm = NULL;

		RegisterClassEx(&wndClassEx);

		railWindow->hWnd = CreateWindowExW(
				railWindow->dwExStyle, /* dwExStyle */
				_T("RdpRailWindow"), /* lpClassName */
				titleW, /* lpWindowName */
				railWindow->dwStyle, /* dwStyle */
				railWindow->x, /* x */
				railWindow->y, /* y */
				railWindow->width, /* nWidth */
				railWindow->height, /* nHeight */
				NULL, /* hWndParent */
				NULL, /* hMenu */
				hInstance, /* hInstance */
				NULL /* lpParam */
				);

		SetWindowLongPtr(railWindow->hWnd, GWLP_USERDATA, (LONG_PTR) railWindow);

		HashTable_Add(wfc->railWindows, (void*) (UINT_PTR) orderInfo->windowId, (void*) railWindow);

		free(titleW);

		UpdateWindow(railWindow->hWnd);

		return;
	}
	else
	{
		railWindow = (wfRailWindow*) HashTable_GetItemValue(wfc->railWindows,
			(void*) (UINT_PTR) orderInfo->windowId);
	}

	if (!railWindow)
		return;

	if ((fieldFlags & WINDOW_ORDER_FIELD_WND_OFFSET) ||
		(fieldFlags & WINDOW_ORDER_FIELD_WND_SIZE))
	{
		if (fieldFlags & WINDOW_ORDER_FIELD_WND_OFFSET)
		{
			railWindow->x = windowState->windowOffsetX;
			railWindow->y = windowState->windowOffsetY;
		}

		if (fieldFlags & WINDOW_ORDER_FIELD_WND_SIZE)
		{
			railWindow->width = windowState->windowWidth;
			railWindow->height = windowState->windowHeight;
		}

		SetWindowPos(railWindow->hWnd, NULL,
			railWindow->x,
			railWindow->y,
			railWindow->width,
			railWindow->height,
			0);
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_OWNER)
	{
		
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_STYLE)
	{
		railWindow->dwStyle = windowState->style;
		railWindow->dwStyle &= ~RAIL_DISABLED_WINDOW_STYLES;
		railWindow->dwExStyle = windowState->extendedStyle;
		railWindow->dwExStyle &= ~RAIL_DISABLED_EXTENDED_WINDOW_STYLES;

		SetWindowLongPtr(railWindow->hWnd, GWL_STYLE, (LONG) railWindow->dwStyle);
		SetWindowLongPtr(railWindow->hWnd, GWL_EXSTYLE, (LONG) railWindow->dwExStyle);
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_SHOW)
	{
		ShowWindow(railWindow->hWnd, windowState->showState);
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_TITLE)
	{
		char* title = NULL;
		WCHAR* titleW = NULL;

		ConvertFromUnicode(CP_UTF8, 0, (WCHAR*) windowState->titleInfo.string,
			   windowState->titleInfo.length / 2, &title, 0, NULL, NULL);

		free(railWindow->title);
		railWindow->title = title;

		ConvertToUnicode(CP_UTF8, 0, railWindow->title, -1, &titleW, 0);

		SetWindowTextW(railWindow->hWnd, titleW);

		free(titleW);
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_OFFSET)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_SIZE)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_WND_CLIENT_DELTA)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_RP_CONTENT)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_ROOT_PARENT)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_WND_RECTS)
	{
		UINT32 index;
		HRGN hWndRect;
		HRGN hWndRects;
		RECTANGLE_16* rect;

		if (windowState->numWindowRects > 0)
		{
			rect = &(windowState->windowRects[0]);
			hWndRects = CreateRectRgn(rect->left, rect->top, rect->right, rect->bottom);

			for (index = 1; index < windowState->numWindowRects; index++)
			{
				rect = &(windowState->windowRects[index]);
				hWndRect = CreateRectRgn(rect->left, rect->top, rect->right, rect->bottom);
				CombineRgn(hWndRects, hWndRects, hWndRect, RGN_OR);
				DeleteObject(hWndRect);
			}

			SetWindowRgn(railWindow->hWnd, hWndRects, TRUE);
			DeleteObject(hWndRects);
		}
	}

	if (fieldFlags & WINDOW_ORDER_FIELD_VIS_OFFSET)
	{

	}

	if (fieldFlags & WINDOW_ORDER_FIELD_VISIBILITY)
	{

	}

	UpdateWindow(railWindow->hWnd);
}