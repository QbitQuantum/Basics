LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  POINT pt;
	switch(msg)
	{
    case WM_ACTIVATE:
      switch(LOWORD(wParam))
      {
        case WA_ACTIVE:
        case WA_CLICKACTIVE:
          if(!ShowCaret(hWnd))
            DbgPrint("ShowCaret(0x%x)\n", hWnd);
          break;
        case WA_INACTIVE:
          if(!HideCaret(hWnd))
            DbgPrint("HideCaret(0x%x)\n", hWnd);
          break;
      }
      break;

    case WM_KEYDOWN:
      if(!GetCaretPos(&pt))
      {
        DbgPrint("GetCaretPos() failed!\n");
        break;
      }
      switch(wParam)
      {
        case VK_LEFT:
          pt.x -= CharWidth;
          break;
        case VK_UP:
          pt.y -= CharHeight;
          break;
        case VK_RIGHT:
          pt.x += CharWidth;
          break;
        case VK_DOWN:
          pt.y += CharHeight;
          break;
      }
      if(!SetCaretPos(pt.x, pt.y))
        DbgPrint("SetCaretPos() failed!\n");
      break;

    case WM_RBUTTONDOWN:
      if(!CreateCaret(hWnd, CaretBitmap, 0, 0))
        DbgPrint("CreateCaret() for window 0x%x failed!\n", hWnd);
      else
        if(!ShowCaret(hWnd))
          DbgPrint("ShowCaret(0x%x)\n", hWnd);
      break;

    case WM_LBUTTONDOWN:
      if(!CreateCaret(hWnd, (HBITMAP)0, CaretWidth, CaretHeight))
        DbgPrint("CreateCaret() for window 0x%x failed!\n", hWnd);
      else
        if(!ShowCaret(hWnd))
          DbgPrint("ShowCaret(0x%x)\n", hWnd);
      break;

    case WM_CREATE:
      if(!CreateCaret(hWnd, (HBITMAP)0, CaretWidth, CaretHeight))
        DbgPrint("CreateCaret() for window 0x%x failed!\n", hWnd);
      else
        if(!SetCaretPos(1, 1))
          DbgPrint("SetCaretPos(%i, %i) failed!\n", 1, 1);
      break;

    case WM_DESTROY:
      if(!DestroyCaret())
        DbgPrint("DestroyCaret() failed!\n");
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}