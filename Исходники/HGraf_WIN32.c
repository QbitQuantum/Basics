/* EXPORT-> MakeXGraf: Create and open window, initialization */
void MakeXGraf(char *wname, int x, int y, int w, int h, int bw)
     /* WIN32: bw is ignored. */
{
   WNDCLASS WindowClass;
   char sbuf[256], *hgraf = "HGraf";
   HDC dc;
     
   if (winCreated)
      HError(6870, "MakeXGraf: Attempt to recreate the graphics window");
     
   WindowClass.hInstance = GetModuleHandle(NULL);
   WindowClass.lpszClassName = hgraf;
   WindowClass.lpfnWndProc = HGWinFunc;
   WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
   WindowClass.hIcon = NULL;
   WindowClass.hCursor = LoadCursor(NULL,IDC_ARROW);
   WindowClass.lpszMenuName = NULL;
   WindowClass.cbClsExtra = 0;
   WindowClass.cbWndExtra = 0;
   WindowClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
     
   RegisterClass(&WindowClass);
     
   strcpy(sbuf, hgraf);  strcat(sbuf, ": ");  strcat(sbuf, wname);
     
   theWindow = 
      CreateWindow(hgraf, sbuf, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                   x,y, w,h, HWND_DESKTOP, NULL,
                   WindowClass.hInstance,       NULL);
     
   /* adjust window size so that the client rectangle is the size requested */
   /* by the caller of MakeXGraf() --- Win32 interprets w and h as the dimensions */
   /* of the overall window. */
   GetClientRect(theWindow,&ClientRect);
   MoveWindow(theWindow,x,y,w+w-ClientRect.right,h+h-ClientRect.bottom,TRUE); 
   GetClientRect(theWindow,&ClientRect);
     
   /* Obtain and initialize device contexts */
   dc = GetDC(theWindow);
   memDC = CreateCompatibleDC(dc);
   SetArcDirection(memDC,AD_COUNTERCLOCKWISE);
   SetArcDirection(dc,AD_COUNTERCLOCKWISE);
   SetPolyFillMode(memDC,WINDING);
   SetPolyFillMode(memDC,WINDING);
   SetTextAlign(memDC,TA_BASELINE | TA_LEFT);
   SetTextAlign(dc,TA_BASELINE | TA_LEFT);
   SetBkMode(memDC,TRANSPARENT);
   SetBkMode(dc,TRANSPARENT);
   theBitmap = CreateCompatibleBitmap(dc,w,h);
   SelectObject(memDC,theBitmap);
   ReleaseDC(theWindow,dc);
   CreateHeap(&btnHeap, "Button heap", MHEAP, sizeof(HButton), 1.0, 100, 100);
     
   InitGlobals();
   InstallColours();
     
   winCreated = TRUE;
   HSetColour(WHITE);
   HFillRectangle(0,0,ClientRect.right,ClientRect.bottom);
}