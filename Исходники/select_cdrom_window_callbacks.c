LRESULT CALLBACK Select_CDROM_Window_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE:
			Select_CDROM_Window_CreateChildWindows(hWnd);
			break;
		
		case WM_CLOSE:
			DestroyWindow(select_cdrom_window);
			return 0;
		
		case WM_MENUSELECT:
		case WM_ENTERSIZEMOVE:
		case WM_NCLBUTTONDOWN:
		case WM_NCRBUTTONDOWN:
			// Prevent audio stuttering when one of the following events occurs:
			// - Menu is opened.
			// - Window is resized.
			// - Left/Right mouse button down on title bar.
			Win32_ClearSoundBuffer();
			break;
		
		case WM_COMMAND:
			// Button press, or Enter pressed in textbox
			switch (LOWORD(wParam))
			{
				case IDOK: // Standard dialog button ID
				case IDC_BTN_OK:
				case IDC_BTN_SAVE:
					if (!IsWindowEnabled(SelCD_btnOK))
						break;
					
					SelCD_Save();
					DestroyWindow(hWnd);
					break;
				
				case IDC_BTN_APPLY:
					if (!IsWindowEnabled(SelCD_btnApply))
						break;
					
					SelCD_Save();
					break;
				
					case IDCANCEL: // Standard dialog button ID
				case IDC_BTN_CANCEL:
					DestroyWindow(hWnd);
					break;
			}
			break;
		
		case WM_DESTROY:
			if (hWnd != select_cdrom_window)
				break;
			
			select_cdrom_window = NULL;
			break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}