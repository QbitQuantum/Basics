void plD_init_win3(PLStream *pls)
{
	HWND      hwndMain;
	WNDCLASS  wndclass;
	HINSTANCE hInstance;
	WinDev    *dev;
	int       greyvalue;
	char      *ptitle;
	//long      backGroundColor;
	
	/* Initial window position */
	int xPos    = 100;
	int yPos    = 100;
	
	/* Initial window size */
	int nWidth  = 720;
	int nHeight = 540;
	
	int xmin = 0;
	int xmax = PIXELS_X-1;
	int ymin = 0;
	int ymax = PIXELS_Y-1;
	
	color = 1;
	hwnd = 0;
	pls->color = 1;		/* Is a color device */
	plParseDrvOpts(win3_options);
	if (!color) pls->color = 0; /* But user does not want color */
	
	/* Set up device parameters */
	pls->termin      = 1; /* is an interactive terminal */
	pls->icol0       = 1; /* current color */
	pls->width       = 1; /* current pen width */
	pls->bytecnt     = 0;
	pls->page        = 0;
	if (buffered)
		pls->plbuf_write = 1; /* buffer the output */
	else
		pls->plbuf_write = 0;
	pls->dev_flush   = 1; /* flush as we like */
	pls->dev_fill0   = 1;	
	pls->dev_fastimg = 1; /* is a fast image device */
	pls->dev_xor     = 1; /* device support xor mode */
	if (pls->dev != NULL) delete pls->dev;
	pls->dev = new WinDev;
	assert(pls->dev != NULL);
	
	dev = (WinDev *) pls->dev;
	dev->nextPlot = 0;
	dev->write_to_window = 1;
	dev->write_to_pixmap = 0;
	dev->PenColor=RGB(pls->cmap0[0].r,pls->cmap0[0].g,pls->cmap0[0].b);
	dev->PenWidth=0;
	
	dev->hPen     = CreatePen(PS_SOLID,dev->PenWidth,dev->PenColor);
	dev->hPenOld = (HPEN)SelectObject(dev->hdc,dev->hPen);
	dev->hbr      = CreateSolidBrush(RGB(pls->cmap0[0].r,pls->cmap0[0].g,pls->cmap0[0].b));
	dev->hbrOld   = (HBRUSH)SelectObject(dev->hdc,dev->hbr);
	dev->hMenu    = NULL;

        dev->isDead   = FALSE;
	
	if (pls->color) {
		dev->backGroundColor = RGB(pls->cmap0[0].r,pls->cmap0[0].g,pls->cmap0[0].b);
	} else {
		greyvalue = (pls->cmap0[0].r+pls->cmap0[0].g+pls->cmap0[0].b)/3;
		dev->backGroundColor = RGB(greyvalue,greyvalue,greyvalue);
	}

	if (!hwnd) {
		/* Window created by the driver */
		dev->externalWindow = 0;
		hInstance = GetModuleHandle(NULL);
		
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS;
		wndclass.lpfnWndProc = ::PlPlotWndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = sizeof(pls);
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(hInstance,"PLICON");
		wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
        wndclass.hbrBackground = (struct HBRUSH__ *)CreateSolidBrush(dev->backGroundColor);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szPlPlotClass;
		RegisterClass (&wndclass);
		ptitle = (char *) &szPlPlotWName[0] ;
		if ( pls->plwindow ) ptitle = pls->plwindow ;
		
		dev->hwnd = CreateWindow(szPlPlotClass,ptitle,
			WS_OVERLAPPEDWINDOW,
			xPos,yPos,nWidth,nHeight,
			NULL,dev->hMenu,
			hInstance,NULL);
		
		SetWindowLong(dev->hwnd,GWL_USERDATA,(long)pls);
		
		ShowWindow(dev->hwnd,SW_SHOWDEFAULT);
		
		SetForegroundWindow(dev->hwnd);
		
	} else {
		/* Window provided externally */		
		dev->hwnd = (HWND)hwnd;
		dev->externalWindow = 1;
	}


	dev->hdc = GetDC(dev->hwnd);

	SetPolyFillMode(dev->hdc,WINDING);
	
	plP_setpxl(xmax/150.0/nWidth*nHeight,ymax/150.0);
	plP_setphy(xmin,xmax,ymin,ymax);


	if (pls->db)
	{
     	// create a compatible device context
     	dev->db_hdc = CreateCompatibleDC(dev->hdc);
     	dev->db_bmp = CreateCompatibleBitmap(dev->hdc, nWidth,nHeight);
		SelectObject(dev->db_hdc, dev->db_bmp);
		dev->hdc=dev->db_hdc;
	}
}