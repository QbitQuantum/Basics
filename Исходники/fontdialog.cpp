static LRESULT CALLBACK fontDialogSampleSubProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	ID2D1RenderTarget *rt;
	struct fontDialog *f;

	switch (uMsg) {
	case msgD2DScratchPaint:
		rt = (ID2D1RenderTarget *) lParam;
		f = (struct fontDialog *) dwRefData;
		fontDialogDrawSampleText(f, rt);
		return 0;
	case WM_NCDESTROY:
		if (RemoveWindowSubclass(hwnd, fontDialogSampleSubProc, uIdSubclass) == FALSE)
			logLastError(L"error removing font dialog sample text subclass");
		break;
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}