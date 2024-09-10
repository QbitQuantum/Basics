LRESULT CALLBACK WndProc (HWND hwnd, UINT Message,
                          WPARAM wParam, LPARAM lParam)
{
	int response;
	HDC hdc;
	PAINTSTRUCT paintstruct;
	static unsigned k = 0;

	switch (Message)
	{
		case WM_COMMAND:
			switch (LOWORD (wParam))
			{
          		case IDM_COM1:
            		cc.dwSize = sizeof(COMMCONFIG);
					cc.wVersion = 0x100;
					GetCommConfig (hComm, &cc, &cc.dwSize);
            		if (!CommConfigDialog (lpszCommName, hwnd, &cc))
               			break;
				break;
				case IDM_COM2:
					cc.dwSize = sizeof(COMMCONFIG);
					cc.wVersion = 0x100;
					GetCommConfig (hComm, &cc, &cc.dwSize);
            		if (!CommConfigDialog (lpszCommName, hwnd, &cc))
               			break;
				break;
			}
		break;
   		case WM_RBUTTONDOWN:		// Process right button
      		response = MessageBox (hwnd, "Press One:", "Right Button",
         							  MB_ABORTRETRYIGNORE);
			switch (response)
			{
         		case IDABORT:
            		MessageBox (hwnd, "", "Abort", MB_OK);
				break;
				case IDRETRY:
            		MessageBox (hwnd, "", "Retry", MB_OK);
				break;
				case IDIGNORE:
					MessageBox (hwnd, "", "Ignore", MB_OK);
				break;
			}
		break;

		case WM_LBUTTONDOWN:		// Process left button
      		response = MessageBox (hwnd, "Conitnue?", "Left Button",
         							  MB_ICONHAND | MB_YESNO);
			switch (response)
			{
         		case IDYES:
            		MessageBox (hwnd, "Press Button", "Yes", MB_OK);
				break;
				case IDNO:
            		MessageBox (hwnd, "Press Button", "No", MB_OK);
				break;
			}
		break;
		
		case WM_CHAR:	// Process keystroke
			hdc = GetDC (hwnd);			 // get device context
			sprintf (str, "%c", (char) wParam); // Convert char to string
			TextOut (hdc, 10*k, 0, str, strlen (str)); // output character	
			k++; // increment the screen x-coordinate
			ReleaseDC (hwnd, hdc); // Release device context
		break;
		
		case WM_PAINT:		// Process a repaint message
			hdc = BeginPaint (hwnd, &paintstruct); // Acquire DC
			TextOut (hdc, 0, 0, str, strlen (str)); // output character
			EndPaint (hwnd, &paintstruct); // Release DC
		break;

		case WM_DESTROY:	// Terminate program
      		PostQuitMessage (0);
		break;
		default:
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;
}