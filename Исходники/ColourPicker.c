BOOL CALLBACK OverrideEditCtrlWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_GETDLGCODE:
			return DLGC_WANTALLKEYS;

		case WM_SETFOCUS:
			SendMessage(hWnd, EM_SETSEL, 0, -1);
			break;

		case WM_CHAR:
			if (wParam == VK_TAB)
			{
				SetFocus(GetNextDlgTabItem(GetParent(hWnd), hWnd, FALSE));
				return 0;
			}
			else if (wParam == VK_RETURN)
			{
				int val;
				char text[4];
				GetWindowText(hWnd, text, 4);
				val = atoi(text);

				if (hColourLineValues[LINE_H] == hWnd)
					SetColourH(&session.current_colour, val);
				else if (hColourLineValues[LINE_S] == hWnd)
					SetColourS(&session.current_colour, val);
				else if (hColourLineValues[LINE_V] == hWnd)
					SetColourV(&session.current_colour, val);
				else if (hColourLineValues[LINE_R] == hWnd)
					SetColourR(&session.current_colour, val);
				else if (hColourLineValues[LINE_G] == hWnd)
					SetColourG(&session.current_colour, val);
				else if (hColourLineValues[LINE_B] == hWnd)
					SetColourB(&session.current_colour, val);

				RedrawColourBlocks();
				return 0;
			}
			break;
	}

	return CallWindowProc((WNDPROC)GetWindowLong(hWnd, GWL_USERDATA), hWnd, Message, wParam, lParam);
}