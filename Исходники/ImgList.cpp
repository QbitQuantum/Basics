int CImgList::AddMasked(int id, COLORREF mask) {
	HBITMAP hm;

	hm = LoadBitmap((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(id));

	if(hm)
		return ImageList_AddMasked(himlIcons, hm, mask);
	else
		return -1;
}