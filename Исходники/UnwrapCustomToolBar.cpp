void ToolBarFrame::Init()
{
	mParentWindow = NULL;
	mToolBarWindow = NULL;
	mPopUpWindow = NULL;
	mDummyWindow = NULL;

	mToolBar = NULL;
	mOwner = 0;

	mX = 0;
	mY = 0;
	mW = 0;
	mH = 0;

	mLocation = kFloat;

	mLoaded = false;

	mCenter = false;

	mImages = NULL; 
	

	static BOOL registered = FALSE;
	if (!registered && mhInstance) {
		registered = TRUE;
		WNDCLASS  wc;
		wc.style         = 0;
		wc.hInstance     = mhInstance;
		wc.hIcon         = NULL;
		wc.hCursor       = NULL;
		wc.hbrBackground = NULL; 
		wc.lpszMenuName  = NULL;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.lpfnWndProc   = PopUpToolbarProc;
		wc.lpszClassName = _M("ToolBarFrameWindow");
		RegisterClass(&wc);

	}

	HBITMAP hBitmap, hMask;	
	mImages = ImageList_Create(16, 15, TRUE, 4, 0);
	hBitmap = LoadBitmap(mhInstance,MAKEINTRESOURCE(IDB_UNWRAP_TRANSFORM));
	hMask   = LoadBitmap(mhInstance,MAKEINTRESOURCE(IDB_UNWRAP_TRANSFORM_MASK));
	ImageList_Add(mImages,hBitmap,hMask);
	DeleteObject(hBitmap);
	DeleteObject(hMask);
}