int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wcl;
	HDC hdc;
	char buffer[] = "hello";

	wcl.hInstance = hThisInst;
	wcl.lpszClassName = WINDOW_CLASS_NAME;
	wcl.lpfnWndProc = WindowFunc;
	wcl.style = CS_HREDRAW | CS_VREDRAW;

	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcl.lpszMenuName = WINDOW_CLASS_NAME;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;	

	wcl.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	

	if(!RegisterClass(&wcl)) return 0;

	if(!(hwnd = CreateWindowEx (
		WS_EX_TOPMOST,
		WINDOW_CLASS_NAME,
		"My First Proper Thing 2",
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hThisInst,
		NULL
		))) return 0;

	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);
	SetFocus(hwnd);
	ShowCursor(0);
	main_window_handle = hwnd;

	LoadBitmap(&colour_bmp_file,"texture2.bmp");
	LoadBitmap(&height_bmp_file,"heightd2.bmp");
	
	if (!DD_Init(hwnd))
	{

		DestroyWindow(hwnd);
		return 0;
	}


	ofstream fout("myfile.dem");

	int i,j,n,index = 0;
	for ( i = 0; i < 512; i++) {

		for ( j = 0; j < 512; j++) {

//			heights[i][j] = height_bmp_file.buffer[index++] * 8;
//			fout << heights[i][j] << " ";
			heights[i][j] = 0;
		
		}	

	fout << "\n";
	}

	index = 0;
	for ( i = 0; i < 1024; i++) {

		for ( j = 0; j < 1024; j++) {

			if ((colours[i][j] = colour_bmp_file.buffer[index++])>250) colours[i][j] = 250;
		
		
		}	

	fout << "\n";
	}

	LoadDEM();

	fout.close();

	LoadDEM();

	while (1) 
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT) { DD_Shutdown(); break; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else 
		{	
			
			memset(&ddsd,0,sizeof(ddsd));
			ddsd.dwSize = sizeof(ddsd);


		



			
			while ( lpddsback->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR,NULL) != DD_OK);

				video_buffer = (UCHAR *) ddsd.lpSurface;

				memset(video_buffer,0,SCREEN_WIDTH*SCREEN_HEIGHT);


				GameMain();
			
				lpddsback->Unlock(NULL);
			
			

		sprintf(buffer,"%d",poo);
	

		if (lpddsback->GetDC(&hdc) == DD_OK) {
		 
			 SetBkColor(hdc, RGB(0, 0, 255));
			SetTextColor(hdc, RGB(255, 255, 0));
       
            TextOut(hdc, 0, 0, buffer, lstrlen(buffer));
           
		
        lpddsback->ReleaseDC(hdc);
		}

		
//Z+=10;
if (Z>3840.0) Z -=3840.0;

			while (TRUE)
               {
                   ddrval = lpddsprimary->Flip(NULL, 0);
                   if (ddrval == DD_OK)
					  
					   
                       break;
                   if (ddrval == DDERR_SURFACELOST)
                   {
                       ddrval = lpddsprimary->Restore();
                       if (ddrval != DD_OK)
                           break;
                   }
                   if (ddrval != DDERR_WASSTILLDRAWING)
                       break; 
			} 
			
            
			if (KEY_DOWN(VK_ESCAPE)) {
				
			DD_Shutdown();
			
				PostMessage(main_window_handle,WM_CLOSE,0,0);
			}
		} 
	}

	DD_Shutdown();

	return(msg.wParam);

}