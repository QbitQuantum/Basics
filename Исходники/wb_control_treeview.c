BOOL wbCreateTreeViewImageList(PWBOBJ pwbo, HBITMAP hbmImage, int nImages, COLORREF clTransparent)
{
	HBITMAP hbmMask;
	static HIMAGELIST hi;
	BITMAP bm;

	if(!pwbo || !pwbo->hwnd || !IsWindow(pwbo->hwnd))
		return FALSE;

	if(hbmImage && nImages) {

		GetObject(hbmImage, sizeof(BITMAP), (LPSTR) &bm);
		if((bm.bmWidth == 0) | (bm.bmHeight == 0))
			return FALSE;

		nImages = MAX(1, MIN(nImages, MIN(bm.bmWidth, MAX_IMAGELIST_IMAGES)));

		if(clTransparent != NOCOLOR) {
			hbmMask = wbCreateMask(hbmImage, clTransparent);
			hi = ImageList_Create(bm.bmWidth / nImages, bm.bmHeight, ILC_COLORDDB | ILC_MASK, nImages, 0);
			ImageList_Add(hi, hbmImage, hbmMask);
			TreeView_SetImageList(pwbo->hwnd, hi, TVSIL_NORMAL);
			DeleteObject(hbmMask);
		} else {
			hi = ImageList_Create(bm.bmWidth / nImages, bm.bmHeight, ILC_COLORDDB, nImages, 0);
			ImageList_Add(hi, hbmImage, NULL);
			TreeView_SetImageList(pwbo->hwnd, hi, TVSIL_NORMAL);
		}
	} else {
		TreeView_SetImageList(pwbo->hwnd, NULL, TVSIL_NORMAL);
		ImageList_Destroy(hi);
	}
	return TRUE;
}