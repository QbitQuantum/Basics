//------------------------------------------------------    
BOOL CRectTracker::TrackHandle( HWND hWnd, const LPPOINT point, int HitTest )
{
	ATLASSERT(point);

    if ((HitTest != hitBegin) && (HitTest != hitEnd) && (HitTest != hitMiddle))
        return FALSE;

    if (!IsValidPos())
        return FALSE;

    // set mouse cursor parameters
    RECT CursorRect;

    if (IsRectEmpty(&ValidRect))
    {
        GetClientRect(hWnd, &CursorRect);
    }
    else
    {
        // valid rectangle is not empty
        if (HitTest == hitMiddle)
        {
            RECT BeginRect = ValidRect;
			OffsetRect(&BeginRect, point->x, point->y);
			OffsetRect(&BeginRect,  -CurPos.Begin.x, -CurPos.Begin.y);
            NormalizeRect(&BeginRect);

            RECT EndRect = ValidRect;
			OffsetRect(&EndRect, point->x, point->y);
			OffsetRect(&EndRect,  -CurPos.End.x, -CurPos.End.y);
            NormalizeRect(&EndRect);

            CursorRect = ValidRect;
            IntersectRect(&CursorRect, &CursorRect, &BeginRect);
            IntersectRect(&CursorRect, &CursorRect, &EndRect);
        }
        else
            CursorRect = ValidRect;
    };

    if (IsRectEmpty(&CursorRect))
        return FALSE;

    ClientToScreen(hWnd, (LPPOINT)&CursorRect );
    ClientToScreen(hWnd, ((LPPOINT)&CursorRect)+1 );
    ClipCursor(&CursorRect);
    SetCapture(hWnd);

	// get DC for drawing
	HDC dc = GetDC(hWnd);

    // set dc parameters
    HPEN LinePen = CreatePen( PS_SOLID, LineWidth, CLR_WHITE );
    HPEN hOldPen = (HPEN)SelectObject(dc, LinePen);
    SetROP2(dc, R2_XORPEN );

    KLinePos OriginalPos = CurPos;
    BOOL bCanceled = FALSE;

    // draw the rectangle for the first time
	DrawRect(dc, &CurPos.Begin, &CurPos.End);

	// get messages until capture lost or cancelled/accepted
    BOOL bExit = FALSE;
    KLinePos NewPos;

	while (!bExit)
	{
		MSG msg;
		BOOL b = ::GetMessage(&msg, NULL, 0, 0);
		ATLASSERT(b);

		if (GetCapture() != hWnd)
			break; // exit loop

		switch (msg.message)
		{
		    // handle movement/accept messages
		    case WM_LBUTTONUP:
		    case WM_MOUSEMOVE:
                {
			        NewPos = CurPos;
                    POINT MousePoint = { (int)(short)LOWORD(msg.lParam), (int)(short)HIWORD(msg.lParam) };

                    switch (HitTest)
                    {
                        case hitBegin:
                            NewPos.Begin = MousePoint;
                            break;

                        case hitEnd:
                            NewPos.End = MousePoint;
                            break;

                        case hitMiddle:
                             NewPos.Begin.x = OriginalPos.Begin.x + (MousePoint.x-point->x);
                             NewPos.Begin.y = OriginalPos.Begin.y + (MousePoint.y-point->y);

                             NewPos.End.x = OriginalPos.End.x + (MousePoint.x-point->x);
                             NewPos.End.y = OriginalPos.End.y + (MousePoint.y-point->y);
                             break;
                    };

                    // redraw the line
                    if ((NewPos.Begin.x != CurPos.Begin.x) || (NewPos.Begin.y != CurPos.Begin.y) ||
						(NewPos.End.x != CurPos.End.x) || (NewPos.End.y != CurPos.End.y))
                    {
                        // draw new rectangle
						DrawRect(dc, &NewPos.Begin, &NewPos.End);

                        // erase old rectangle
						DrawRect(dc, &CurPos.Begin, &CurPos.End);
                    };

                    if (IsValidPos(NewPos))
                        CurPos = NewPos;

                    if (msg.message == WM_LBUTTONUP)
                        bExit = TRUE;
                };
    	        break;

		    // handle cancel messages
		    case WM_KEYDOWN:
			    if (msg.wParam == VK_ESCAPE)
                {
                    bCanceled = TRUE;
                    bExit = TRUE;
                };
			    break;

		    case WM_RBUTTONDOWN:
                bCanceled = TRUE;
                bExit = TRUE;
                break;

		    // just dispatch rest of the messages
		    default:
			    DispatchMessage(&msg);
			    break;
	    }
    };

    ClipCursor(NULL);
    ReleaseCapture();

    if (bCanceled)
        CurPos = OriginalPos;

    SelectObject(dc, hOldPen);
	DeleteObject(LinePen);
	ReleaseDC(hWnd, dc);
    return !bCanceled;
};