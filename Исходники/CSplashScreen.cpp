void CSplashScreen::Initialize(const char* pFilename)
{
	// Create a splash window class
	WNDCLASSEXA wc;

	// Fill the window class structure
	wc.cbSize		   = sizeof(WNDCLASSEX);
	wc.style			= NULL;
	wc.lpfnWndProc	  = MessageRouter;
	wc.cbClsExtra	   = 0;
	wc.cbWndExtra	   = 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= NULL;
	wc.hCursor		  = LoadCursor(NULL, IDC_WAIT);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName	= "Splash";
	wc.hIconSm		  = NULL;

	// Register the splash window class
	RegisterClassExA(&wc);

	// Load the bitmap
	mBitmap = (HBITMAP)LoadImageA(0, pFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// Get the bitmap size
	BITMAP bmp;
	GetObject(mBitmap, sizeof(BITMAP), &bmp);
	mWinWidth = bmp.bmWidth;
	mWinHeight = bmp.bmHeight;

	// Get screen resolution
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Set splash window position to the center of the screen
	int iPosX = (iScreenWidth - mWinWidth) / 2;
	int iPosY = (iScreenHeight - mWinHeight) / 2;

	// Create a new splash window
	mSplashWindow = CreateWindowExA
	(
		WS_EX_TOPMOST,			  // Extended style
		"Splash",				   // Class Definitions name (we are using a system class here)
		"Splash",				   // Window name
		WS_POPUP,				   // Style
		iPosX, iPosY,			   // Position
		mWinWidth, mWinHeight,	// Dimensions
		NULL,					   // Handle to parent window
		NULL,					   // Handle to menu
		NULL,					   // Handle to instance
		this						// Passing "this" so we can receive messages later
	);
}