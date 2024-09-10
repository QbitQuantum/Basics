void ShowOTRMenu(MCONTACT hContact, POINT pt){
	HMENU menu = (HMENU) CallService(MS_MIROTR_MENUBUILDMIROTR, hContact, 0);
	SetWindowLongPtr(hDummyPaintWin, GWLP_USERDATA, (LONG_PTR)hContact);
	TrackPopupMenu(menu, 0, pt.x, pt.y, 0, hDummyPaintWin, 0);
	DestroyMenu(menu);
}