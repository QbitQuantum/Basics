int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	InitCommonControlsEx(&ICC);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_PATH);

	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_APILOG2);
#define MATRIX
#ifdef MATRIX
	TControl::FDefaultBackBrush = CreateSolidBrush(0);
	TControl::FDefaultPen = CreatePen(PS_SOLID, 1, hCol);
	TAppWindow::FWindowClass.hIconSm = LoadIcon(hInstance, (LPCTSTR)IDI_SMALL);
	TAppWindow::FWindowClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APILOG2);
	TControl::FDefaultTextColor = 0x00FF79;
	TGroupBox::FDefaultStyle = 0;

	TCustomGrid::FDefaultTxtColor = mCol;
	TCustomGrid::FDefaultSelTxtColor = 0x00FF79;//0x0FF079;

	TCustomGrid::FDefaultCellsBrush = TControl::FDefaultBackBrush;
	TCustomGrid::FDefaultSelBrush = CreateSolidBrush(hCol);
	TCustomGrid::FDefaultBlurBrush = CreateSolidBrush(0x032C17);
#endif
	HFONT hFont = CreateFontIndirect(&LogFont);
	TProcess * Process = new TProcess(hInstance, 0, nCmdShow, hFont);

    int Result = DefMessageLoop(hAccelTable);
	//DestroyIcon(TAppWindow::FWindowClass.hIconSm);
	//DestroyIcon(TAppWindow::FWindowClass.hIcon);
	DeleteObject(hFont);
#ifdef MATRIX
	DeleteObject(TControl::FDefaultBackBrush);
	DeleteObject(TCustomGrid::FDefaultSelBrush);
	DeleteObject(TControl::FDefaultPen);
#endif

	DestroyAcceleratorTable(hAccelTable);

	_CrtMemDumpAllObjectsSince(0);
    return Result;	
}