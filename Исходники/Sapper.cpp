int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SAPPER, szWindowClass, MAX_LOADSTRING);
	HBITMAP hBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPBACK));

	HBRUSH hBrush = CreatePatternBrush(hBmp);

	BombField::setBmpEmpty(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPBUT)));
	BombField::setBmp0(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP0)));
	BombField::setBmpFlag(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPFLAG)));
	BombField::setBmpQm(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPQM)));
	BombField::setBmpBomb(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPBOMB)));
	BombField::setBmp1(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)));
	BombField::setBmp2(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2)));
	BombField::setBmp3(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3)));
	BombField::setBmp4(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4)));
	BombField::setBmp5(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5)));
	BombField::setBmp6(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP6)));
	BombField::setBmp7(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7)));
	BombField::setBmp8(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8)));
	BombField::setBmpExploded(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPEXPL)));

	if (!MyRegisterClass(hInstance, hBrush))
		return FALSE;

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAPPER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}