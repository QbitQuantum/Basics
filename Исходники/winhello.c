LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CONTEXTMENU:
			TrackPopupMenu(GetSubMenu(GetMenu(hwnd),0),TPM_LEFTALIGN,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),0,hwnd,NULL);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_EXIT:
					DestroyWindow(hwnd);
				break;
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
					if (GetMenuState(GetMenu(hwnd), LOWORD(wParam), MF_BYCOMMAND) & MF_CHECKED)
						CheckMenuItem(GetMenu(hwnd), LOWORD(wParam), MF_BYCOMMAND | MF_UNCHECKED);
					else
						CheckMenuItem(GetMenu(hwnd),LOWORD(wParam),MF_BYCOMMAND|MF_CHECKED);
				break;
			}
		break;
		case WM_DESTROY:
			WritePrivateProfileInt("window","height",height,configfile);
			WritePrivateProfileInt("window","width",width,configfile);
			PostQuitMessage(0);
		break;
		case WM_SIZE:
			width = LOWORD(lParam);
			height = HIWORD(lParam);
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}