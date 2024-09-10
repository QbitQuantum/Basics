LRESULT CALLBACK ControlPadWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	if (Msg == WM_CREATE)
	{
		// Pointer to a value to be passed to the window through 
		// the CREATESTRUCT structure is out window object instance.
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		ControlPad* pCtrlPad = static_cast<ControlPad*>(pcs->lpCreateParams);
		// Store the pointer as private data of the window
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToUlong(pCtrlPad)); 
		pCtrlPad->Attach(hWnd);
		pCtrlPad->OnCreate();
		return 0;
	}

	// Extract the pointer to out window object
	ControlPad* pCtrlPad = static_cast<ControlPad*>(UlongToPtr(::GetWindowLongPtr(hWnd, GWLP_USERDATA)));

	if (pCtrlPad)
	{
		pCtrlPad->WindowProc(Msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);

}