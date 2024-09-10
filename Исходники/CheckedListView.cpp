HIMAGELIST CheckedListView::CreateCheckBoxImageList(HWND hWnd)
{
	HDC hdc_wnd, hdc;
	HBITMAP hbm_im, hbm_mask, hbm_orig;
	RECT rc;
	HIMAGELIST himl;
                                    
	int x = GetSystemMetrics(SM_CXSMICON);
	himl = ImageList_Create(x, GetSystemMetrics(SM_CYSMICON), ILC_COLOR16 | ILC_MASK, 2, 2);
	hdc_wnd = GetDC(hWnd);
	hdc = CreateCompatibleDC(hdc_wnd);
	hbm_im = CreateCompatibleBitmap(hdc_wnd, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON));	
	hbm_mask = CreateBitmap(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 1, 1, NULL);
	ReleaseDC(hWnd, hdc_wnd);
                                                                      
	rc.left = rc.top = 0;
	rc.right = GetSystemMetrics(SM_CXSMICON);
	rc.bottom = GetSystemMetrics(SM_CYSMICON);

	hbm_orig = (HBITMAP) SelectObject(hdc, hbm_mask);
	SelectObject(hdc, hbm_im);	

	// Create normal image
	_createButtonCheckImage(hdc, &rc, false, CheckedColorNone);
	SelectObject(hdc, hbm_orig);
	ImageList_Add(himl, hbm_im, hbm_mask);
	SelectObject(hdc, hbm_im);

	// Create color checked images
	CheckedColor colors[] = {CheckedColorBlack, CheckedColorGrey, CheckedColorYellow, CheckedColorGreen, CheckedColorNone};
	CheckedColor* color = colors;

	while (*color != CheckedColorNone)
	{	
		_createButtonCheckImage(hdc, &rc, true, *color);
		SelectObject(hdc, hbm_orig);
		ImageList_Add(himl, hbm_im, hbm_mask);
		SelectObject(hdc, hbm_im);
		color++;
	}

	DeleteObject(hbm_mask);
	DeleteObject(hbm_im);
	DeleteDC(hdc);
	return himl;
}