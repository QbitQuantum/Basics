void TLHScroll (TLWndData* pWD, int code, int pos, HWND hWndBar) {
	int pagesize;
	int newpos;
	int scrollamount;

	pagesize = pWD->tlInval.right - pWD->tlInval.left;
	newpos = pWD->iHorizontalPos;

	switch (code) {
	case SB_TOP :
		newpos = 0;
		break;

	case SB_BOTTOM :
		newpos = (pWD->iTotalWidth-pagesize);
		break;

	case SB_PAGELEFT :
		newpos -= pagesize;
		if (newpos < 0) newpos = 0;
		break;

	case SB_PAGERIGHT :
		newpos += pagesize;
		if (newpos > (pWD->iTotalWidth-pagesize)) 
			newpos = (pWD->iTotalWidth-pagesize);
		break;

	case SB_LINELEFT :
		newpos-=3;
		if (newpos < 0) newpos = 0;
		break;

	case SB_LINERIGHT :
		newpos+=3;
		if (newpos > (pWD->iTotalWidth-pagesize)) 
			newpos = (pWD->iTotalWidth-pagesize);
		break;

	case SB_THUMBPOSITION :
	case SB_THUMBTRACK :
		newpos = pos;
		break;

	default :
		return;
	}
	scrollamount = pWD->iHorizontalPos - newpos;
	pWD->iHorizontalPos = newpos;
	if (scrollamount) {
		ScrollWindowEx (pWD->hWnd, scrollamount, 0, NULL, &(pWD->tlRect),
						NULL, NULL, SW_INVALIDATE|SW_SCROLLCHILDREN); 
		UpdateWindow (pWD->hWnd);
	}
}