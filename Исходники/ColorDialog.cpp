static LRESULT CALLBACK opacitySliderSubProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	ID2D1RenderTarget *rt;
	struct colorDialog *c;
	D2D1_POINT_2F *pos;
	D2D1_SIZE_F *size;

	c = (struct colorDialog *) dwRefData;
	switch (uMsg) {
	case msgD2DScratchPaint:
		rt = (ID2D1RenderTarget *) lParam;
		drawOpacitySlider(c, rt);
		return 0;
	case msgD2DScratchLButtonDown:
		pos = (D2D1_POINT_2F *) wParam;
		size = (D2D1_SIZE_F *) lParam;
		c->a = 1 - (pos->x / size->width);
		updateDialog(c, NULL);
		return 0;
	case WM_NCDESTROY:
		if (RemoveWindowSubclass(hwnd, opacitySliderSubProc, uIdSubclass) == FALSE)
			logLastError(L"error removing color dialog opacity slider subclass");
		break;
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}