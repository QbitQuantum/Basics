static INT_PTR ServiceCreateMergedFlagIcon(WPARAM wParam,LPARAM lParam)
{
	//TODO: use freeimage to create merget icon and add RGB(A) support
	ICONINFO icoi;
	BITMAP bm;
	HICON hIcon=NULL;
	/* load both icons */
	HICON hLowerIcon=(HICON)ServiceLoadFlagIcon((WPARAM)lParam,0);
	if (hLowerIcon == NULL) return NULL;
	HICON hUpperIcon=(HICON)ServiceLoadFlagIcon(wParam,0);
	/* merge them */
	if (GetIconInfo(hLowerIcon,&icoi)) {
		if (hUpperIcon!=NULL && GetObject(icoi.hbmColor,sizeof(bm),&bm)) {
			HDC hdc=CreateCompatibleDC(NULL);
			if (hdc!=NULL) {
				POINT aptTriangle[3];
				memset(&aptTriangle, 0, sizeof(aptTriangle));
				aptTriangle[1].y=bm.bmHeight-1;
				aptTriangle[2].x=bm.bmWidth-1;
				HRGN hrgn=CreatePolygonRgn(aptTriangle,_countof(aptTriangle),WINDING);
				if (hrgn!=NULL) {
					SelectClipRgn(hdc,hrgn);
					HBITMAP hbmPrev=(HBITMAP)SelectObject(hdc,icoi.hbmColor);
					if (hbmPrev!=NULL) {  /* error on select? */
						if (DrawIconEx(hdc,0,0,hUpperIcon,bm.bmWidth,bm.bmHeight,0,NULL,DI_NOMIRROR|DI_IMAGE)) {
							if (SelectObject(hdc,icoi.hbmMask)!=NULL) /* error on select? */
								DrawIconEx(hdc,0,0,hUpperIcon,bm.bmWidth,bm.bmHeight,0,NULL,DI_NOMIRROR|DI_MASK);
						}
						SelectObject(hdc,hbmPrev);
					}
					DeleteObject(hrgn);
				}
				DeleteDC(hdc);
			}
		}
		/* create icon */
		hIcon=CreateIconIndirect(&icoi);
		DeleteObject(icoi.hbmColor);
		DeleteObject(icoi.hbmMask);
	}
	return (INT_PTR)hIcon;
}