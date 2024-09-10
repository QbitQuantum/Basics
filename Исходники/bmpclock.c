void Init(void) {
	HRGN TSt;
	HBITMAP hBmpBack, hBmpCircle;

	hMenu = CreatePopupMenu();
	AppendMenu (hMenu,0,IDM_BACK1, szMenuBack1);
	AppendMenu (hMenu,0,IDM_BACK2, szMenuBack2);
	AppendMenu (hMenu,MF_SEPARATOR,0,NULL);
	AppendMenu (hMenu,0,IDM_CIRCLE1, szMenuCircle1);
	AppendMenu (hMenu,0,IDM_CIRCLE2, szMenuCircle2);
	AppendMenu (hMenu,MF_SEPARATOR,0,NULL);
	AppendMenu (hMenu,0,IDM_EXIT, szMenuExit);
	CheckMenuRadioItem (hMenu,IDM_BACK1,IDM_BACK2,IDM_BACK1,0);
	CheckMenuRadioItem (hMenu,IDM_CIRCLE1,IDM_CIRCLE2,IDM_CIRCLE1,0);

	TSt = CreateEllipticRgn (0,0,CLOCK_SIZE+1,CLOCK_SIZE+1);
	SetWindowRgn (hWinMain, TSt, TRUE);
	DeleteObject (TSt);
	SetWindowPos (hWinMain, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	dwNowBack = IDB_BACK1;
	dwNowCircle = IDB_CIRCLE1;
	CreateBackGround();
	CreateClockPic();
	SetTimer (hWinMain, ID_TIMER, 1000, NULL);
	return;
}