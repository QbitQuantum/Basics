// the real list view intercepts these keys to control editing
static LRESULT CALLBACK editSubProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubclass, DWORD_PTR dwRefData)
{
	uiTable *t = (uiTable *) dwRefData;
	HRESULT hr;

	switch (uMsg) {
	case WM_KEYDOWN:
		switch (wParam) {
		// TODO handle VK_TAB and VK_SHIFT+VK_TAB
		case VK_RETURN:
			hr = uiprivTableFinishEditingText(t);
			if (hr != S_OK) {
				// TODO
			}
			return 0;		// yes, the real list view just returns here
		case VK_ESCAPE:
			hr = uiprivTableAbortEditingText(t);
			if (hr != S_OK) {
				// TODO
			}
			return 0;
		}
		break;
	// the real list view also forces these flags
	case WM_GETDLGCODE:
		return DLGC_HASSETSEL | DLGC_WANTALLKEYS;
	case WM_NCDESTROY:
		if (RemoveWindowSubclass(hwnd, editSubProc, uIDSubclass) == FALSE)
			logLastError(L"RemoveWindowSubclass()");
		// fall through
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}