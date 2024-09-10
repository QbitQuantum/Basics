static LRESULT CALLBACK
PxTabProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PxTabObject* self = (PxTabObject*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);

	switch (msg)
	{
	case OCM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGING:
			return FALSE;

		case TCN_SELCHANGE:
		{
			int iIndex = TabCtrl_GetCurSel(self->hWin);
			PxTabPage_GotSelected(PyList_GetItem(self->pyPages, iIndex));
			break;
		}
		}

	}
	}
	return CallWindowProcW(self->fnOldWinProcedure, hwnd, msg, wParam, lParam);
}