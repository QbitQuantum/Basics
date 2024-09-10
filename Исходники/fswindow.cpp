static LRESULT CALLBACK 
MainWindowProc(HWND MainWindow, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch(Message) {
		case WM_CREATE:
			InitWindowComponents(MainWindow, &Controls);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ERASEBKGND:
			// NOTE: Return a non-zero value. Literally.
			Result = !0;
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT PaintStruct;
			HDC DC = BeginPaint(MainWindow, &PaintStruct);
			RECT FillRegion;
			GetClientRect(MainWindow, &FillRegion);
			COLORREF Top = RGB(239, 241, 245);
			COLORREF Bottom = RGB(218, 223, 233);
			DrawGradient(DC, FillRegion, Top, Top, Bottom, Bottom);
			EndPaint(MainWindow, &PaintStruct);
			ReleaseDC(MainWindow, DC);
		} break;
		case WM_COMMAND:
		{
			HWND Ctrl = (HWND)lParam;
			if(HIWORD(wParam) == CBN_SELCHANGE && Ctrl == Controls.ComboBox) {
				DWORD Pos = SendMessageA((HWND)lParam, CB_GETCURSEL, 0, 0);
				window_data *WndData = (window_data*)SendMessageA((HWND)lParam, CB_GETITEMDATA, Pos, 0);
				if(WndData) {
					Controls.CurSelection = WndData;
					HWND Window = WndData->Window;
					WINDOWINFO WindowInfo = {};
					WindowInfo.cbSize = sizeof(WindowInfo);
					if(GetWindowInfo(Window, &WindowInfo)) {
						RECT Rect = WindowInfo.rcWindow;
						LONG Width = Rect.right - Rect.left;
						LONG Height = Rect.bottom - Rect.top;

						// TODO: Display usefull data
						char Buffer[256];
						StringCbPrintfA(Buffer, sizeof(Buffer), "%dx%d starting at (%d,%d)", Width, Height, Rect.left, Rect.top);
						SetWindowTextA(Controls.StaticText, Buffer);
						ShowWindow(Controls.StaticText, TRUE);
					}
					else {
						PRINT_ERR("Could not get window info.\n");
					}
				}
			}
			else if(HIWORD(wParam) == BN_CLICKED) {
				if(Ctrl == Controls.ButtonOK) {
					if(Controls.CurSelection) {
						int UseConfig = SendMessageA(Controls.CheckBox, BM_GETCHECK, 0, 0);
						if(UseConfig == BST_CHECKED) {
							load_file_result LoadResult = LoadWindowSizeFromConfig();
							if(LoadResult.Valid) {
								SetWindowMode(*Controls.CurSelection, LoadResult.Width, LoadResult.Height);
							}
							else {
								int SetToFullscreen = MessageBoxA(MainWindow, "Error loading config.ini.\nSet to fullscreen instead?", 0, MB_YESNO | MB_TASKMODAL);
								if(SetToFullscreen == IDYES) {
									SetFullscreen(*Controls.CurSelection);
								}
							}
						}
						else {
							SetFullscreen(*Controls.CurSelection);
						}
					}
					PostQuitMessage(0);
				}
				else if(Ctrl == Controls.ButtonCancel) {
					PostQuitMessage(0);
				}
				else {
					Result = DefWindowProcA(MainWindow, Message, wParam, lParam);
				}
			}
		} break;
		default:
			Result = DefWindowProcA(MainWindow, Message, wParam, lParam);
	}

	return Result;
}