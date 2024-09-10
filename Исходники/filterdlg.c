LRESULT CALLBACK
FilterListProcedure(
	IN HWND hWnd,
	IN UINT uMsg,
	IN WPARAM wp,
	IN LPARAM lp,
	IN UINT_PTR uIdSubclass,
	IN DWORD_PTR dwRefData
	)
{
	BOOLEAN Handled;

	switch (uMsg) {

		case WM_KEYDOWN:

			if ((ULONG)wp == VK_DELETE) {
				Handled = FilterListOnDelete(hWnd, uMsg, wp, lp);
				if (Handled) {
					return TRUE;
				}
			}
	}

	return DefSubclassProc(hWnd, uMsg, wp, lp);
} 