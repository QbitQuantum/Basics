/*
================
AlphaSelectDlg_WndProc

Window procedure for the alpha select dialog
================
*/
INT_PTR CALLBACK AlphaSelectDlg_WndProc ( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_INITDIALOG:
		{		
			int color;
			
			gAlphaDlg  = hwnd;
			gAlphaHook = SetWindowsHookEx( WH_GETMESSAGE, AlphaSelectDlg_GetMsgProc, NULL, GetCurrentThreadId() );
			color      = GetRValue(ColorButton_GetColor ((HWND)lParam));

			// The lParam for the alpha select dialog is the window handle of the button pressed
			SetWindowLongPtr ( hwnd, GWL_USERDATA, lParam );
			
			// Subclass the alpha 
			SetWindowLongPtr ( GetDlgItem ( hwnd, IDC_GUIED_ALPHASLIDER ), GWL_USERDATA, MAKELONG(0,color) );

			// Numbers only on the edit box and start it with the current alpha value.
			NumberEdit_Attach ( GetDlgItem ( hwnd, IDC_GUIED_ALPHA ) );		
			SetWindowText ( GetDlgItem ( hwnd, IDC_GUIED_ALPHA ), va("%.3f", ((float)color / 255.0f) ) );
			break;
		}

		case WM_DESTROY:
			UnhookWindowsHookEx( gAlphaHook );
			ReleaseCapture ( );
			gAlphaDlg = NULL;
			break;		
		
		case WM_ACTIVATE:
			if ( !LOWORD(wParam) )
			{
				EndDialog ( hwnd, 0 );
			}
			break;

		case WM_COMMAND:
			switch ( LOWORD(wParam) )
			{
				case IDC_GUIED_ALPHA:
				{
					char	temp[64];
					float	value;
					
					// Get the current text in the window and convert it to a float
					GetDlgItemText ( hwnd, IDC_GUIED_ALPHA, temp, 64 );
					value = atof ( temp );
					
					if ( value < 0.0f ) 
					{
						value = 0.0f;
					}
					else if ( value > 1.0f )
					{
						value = 1.0f;
					}

					// Set the current alpha value in the slider
					SetWindowLongPtr ( GetDlgItem ( hwnd, IDC_GUIED_ALPHASLIDER ), GWL_USERDATA, MAKELONG(0,(255.0f * value)) );
					break;
				}
					
				case IDC_GUIED_ALPHASLIDER:
				case IDOK:
				{
					int color = (short)HIWORD(GetWindowLongPtr ( GetDlgItem ( hwnd, IDC_GUIED_ALPHASLIDER ), GWL_USERDATA ));
					ColorButton_SetColor ( (HWND)GetWindowLongPtr ( hwnd, GWL_USERDATA ), RGB(color,color,color) );
					EndDialog ( hwnd, 0 );
					break;
				}
					
				case IDCANCEL:
					EndDialog ( hwnd, 0 );
					break;
			}
			break;			
	}

	return FALSE;
}