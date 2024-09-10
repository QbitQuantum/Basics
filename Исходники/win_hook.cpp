static LRESULT CALLBACK CallWndHookProc(UINT nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode < 0)
		return CallNextHookEx(nullptr, nCode, wParam, lParam);
	
	if (nCode == HC_ACTION)
	{
		PCWPSTRUCT swpStruct = (PCWPSTRUCT)lParam;

		//skip messages from childs
		if (g_hWndTarget == swpStruct->hwnd)
		{
			switch(swpStruct->message)
			{
			case WM_ACTIVATE:
				PostMessageW(g_hWndSrv, WMU_ACTIVATE, swpStruct->wParam, swpStruct->lParam);
				break;
			case WM_DESTROY:
				PostMessageW(g_hWndSrv, WMU_DESTROY, (WPARAM)swpStruct->hwnd, swpStruct->lParam);
				break;
			}
		}
	}

	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}