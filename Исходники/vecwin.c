LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

   switch(Message){
   case WM_CREATE:
     break;
   case WM_SIZE:  
     /* This is called with 0,0 when iconized. That is bad. So don't resize
	now.*/
     wWidth = LOWORD(lParam);  // width of client area 
     wHeight = HIWORD(lParam); // height of client area 
/*       printf("Resized: %d %d\n",wWidth,wHeight); */
     /*     AccisRenewBitmap(hwnd);*/
     break;
   case WM_PAINT:
/*       printf("Paint BitBlt\n"); */
     /*Trying for private DC*/
/*       hdcWindow = BeginPaint(hwnd, &ps); */
     BitBlt(hdcWindow, 0, 0, wWidth, wHeight, hdcMemory, 0, 0, SRCCOPY);
/*         EndPaint(hwnd, &ps); */
     GetClientRect(hwnd,&wRect);
     ValidateRect(hwnd,&wRect);/* Needed without endpaint. Not perfect.
				Resize leads to continuous BitBlt.
			       Needs new/current window size.*/
     break;
   case WM_CLOSE:
       /* It is not safe to do the following from the right-hand X.
	  Makes the program hang. The Default is also bad so act the same.*/
/*       DestroyWindow(hwnd); */
/*       break; */
   case WM_DESTROY:
   case WM_LBUTTONDOWN: /* Click in window to exit from this message loop. */
     DeleteDC(hdcMemory);
     PostQuitMessage(0);
     break;
   default:
     return DefWindowProc(hwnd, Message, wParam, lParam);
   }
   return 0;
}