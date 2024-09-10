static void LoadImages() {
	if (hButtonImages) return;
	HBITMAP hBitmap, hMask;
	hButtonImages = ImageList_Create(15, 14, ILC_MASK, 2, 0);	// 17 is kluge to center square. -SA
	hBitmap     = LoadBitmap (hInstance,MAKEINTRESOURCE(IDB_BUTTONS));
	hMask       = LoadBitmap (hInstance,MAKEINTRESOURCE(IDB_BUTTON_MASK));
	ImageList_Add(hButtonImages, hBitmap, hMask);
	DeleteObject(hBitmap);
	DeleteObject(hMask);
}