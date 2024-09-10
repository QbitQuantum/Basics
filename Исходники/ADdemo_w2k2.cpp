//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
long FAR PASCAL
WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char str2[40];
	char *ss;
	int dec,sign,xpos,pp;

    switch (message)
    {
        case WM_ACTIVATEAPP:
            // Pause if minimized or not the top window
            g_bActive = (wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE);
            return 0L;
			break;

        case WM_DESTROY:
            // Clean up and close the app
            ADmainExit();
            PostQuitMessage(0);
            return 0L;
			break;
		
		case WM_PAINT:
//			if (video.enabled) ADmainLoop();
			break;

		case WM_SIZE:
			if (!RunFullscreen)
			{
				//wnWidth = LOWORD(lParam);
				//wnHeight = HIWORD(lParam); 
//			    if (video.enabled) ADmainLoop();
			}
            break;

		case WM_LBUTTONDOWN:
			if (demoRunning)
			{
			  PostMessage(hWnd, WM_CLOSE, 0, 0);
              return 0L;
			}
			break;
/*
        case WM_MOUSEMOVE:
		    if (demoRunning)
			{
               xpos = LOWORD(lParam);
			   if (xpos>mouseop)
			   {
				  curpos+=0.001;
				  if (curpos>1) curpos=1;
			   }
			   else
			   {
				  curpos-=0.001;
				  if (curpos<0) curpos=0;
			   }
			   mouseop=xpos;
			}
*/
        case WM_KEYDOWN:
            // Handle any non-accelerated key commands
			if (demoRunning)
            switch (wParam)
            {

				case VK_F2:
					     curpos-=0.02f;
						 if (curpos<0) curpos=0;
						 break;
                case VK_F3:
                         curpos+=0.02f;
						 if (curpos>1) curpos=1;
						 break;
                case VK_F4:
                         curpos=1.0;
						 break;
				case VK_F5:
					// ss=str1;
					ss=ecvt(curpos, 8, &dec, &sign);
					strcpy(str2,"pos: 0.");
					dec=abs(dec);
					for (pp=0; pp<dec; pp++)
					  strcat(str2, "0");

					strcat(str2,ss);
					MessageBox(miawin, str2, "AD-Tuning System", NULL);
                    break;

				case VK_ESCAPE:
                case VK_F12:
                    // PostMessage(hWnd, WM_CLOSE, 0, 0);
					demo_state=1;
                    return 0L;
					break;
            }
            break;

        case WM_SETCURSOR:
            // Turn off the cursor if this is a full-screen app
            if (RunFullscreen) SetCursor(NULL);
            else SetCursor(miocursor);
            return TRUE;
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}