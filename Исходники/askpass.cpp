  static INT_PTR CALLBACK dlgProc(HWND i_hwnd, UINT i_message,
				  WPARAM i_wParam, LPARAM i_lParam)
  {
    DialogPassphrase *This =
      reinterpret_cast<DialogPassphrase *>(
	GetWindowLongPtrW(i_hwnd, GWLP_USERDATA));
    if (!This)
      switch (i_message)
      {
	case WM_INITDIALOG:
	  This = reinterpret_cast<DialogPassphrase *>(i_lParam);
	  SetWindowLongPtrW(i_hwnd, GWLP_USERDATA, i_lParam);
	  This->initialize(i_hwnd);
	  return This->wmInitDialog(reinterpret_cast<HWND>(i_wParam));
      }
    else
      switch (i_message)
      {
	case WM_CLOSE:
	  return This->wmClose();
	case WM_COMMAND:
	  return This->wmCommand(HIWORD(i_wParam), LOWORD(i_wParam),
				 reinterpret_cast<HWND>(i_lParam));
      }
    return FALSE;
  }