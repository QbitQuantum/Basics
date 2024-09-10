int COXListPopup::Pick(CRect rect, CRect rectParent)
{
	AdjustDisplayRectangle(rect, rectParent);

	MoveWindow(rect);
	ShowWindow(SW_SHOWNA);
	SetCapture();

	// init message loop
	bool bBreak = false;
	int iReturnItemIdx = -1;
	while (!bBreak)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));
		if (msg.message == WM_LBUTTONUP)
		{
			// Get the item under the mouse cursor
			int xPos = GET_X_LPARAM(msg.lParam); 
			int yPos = GET_Y_LPARAM(msg.lParam);

			BOOL bOutside;
			UINT nIndex = ItemFromPoint(CPoint(xPos, yPos), bOutside);
			if (!bOutside)
				iReturnItemIdx = (int) nIndex;
			bBreak = true;
		}
		else if (msg.message == WM_KEYDOWN)
		{
			// Handle ESCAPE, UP, DOWN and ENTER
			if (msg.wParam == VK_ESCAPE)
				bBreak = true;
			else if (msg.wParam == VK_UP)
			{
				int iSel = GetCurSel();
				if (iSel == -1 || iSel == 0)
					SetCurSel(0);
				else
					SetCurSel(iSel - 1);
			}
			else if (msg.wParam == VK_DOWN)
			{
				// Move the selection 1 item down
				int iSel = GetCurSel();
				if (iSel == -1)
					SetCurSel(0);
				else if (iSel == GetCount() - 1)
				{
					// Do nothing
				}
				else
					SetCurSel(iSel + 1);
			}
			else if (msg.wParam == VK_RETURN)
			{
				iReturnItemIdx = GetCurSel();
				bBreak = true;
			}
		}
		else if (msg.message == WM_LBUTTONDOWN)
		{
			// Do nothing				
		}
		else if (msg.message == WM_MOUSEMOVE)
		{
			// Select the item under the mouse cursor
			int xPos = GET_X_LPARAM(msg.lParam); 
			int yPos = GET_Y_LPARAM(msg.lParam);

			BOOL bOutside;
			UINT nIndex = ItemFromPoint(CPoint(xPos, yPos), bOutside);
			if (!bOutside)
				SetCurSel((int) nIndex);
		}
		else
		{
			DispatchMessage(&msg);
		}
	}

	ReleaseCapture();
	ShowWindow(SW_HIDE);

	return iReturnItemIdx;
}