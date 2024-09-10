HWND createToolbar(HINSTANCE hInst, HWND hWnd)
{
#if 1
  HBITMAP hBitmap = (HBITMAP)LoadImage(hInst,
                               MAKEINTRESOURCE(IDB_TOOLBAR),
                               IMAGE_BITMAP, 0, 0, 
                               LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
#else
  HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "toolbar.bmp", IMAGE_BITMAP, 0, 0, 
                               LR_LOADFROMFILE | LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
#endif

  HWND ret = CreateToolbarEx(hWnd,
    WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
    11,
    30,
    NULL, (int)hBitmap,
    NULL, 0, //buttons set later
    0, 0, 0, 0, sizeof(TBBUTTON));

  addTools(ret);
  SendMessage(ret, TB_SETSTYLE, 0, TBSTYLE_FLAT | CCS_TOP | TBSTYLE_TOOLTIPS |
    //wrapable style doesn't work with separators
    //use nodivider to remove the two stupid pixel lines on top of the toolbar
    CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_ALTDRAG); // | TBSTYLE_WRAPABLE);// );
  SendMessage(ret, TB_AUTOSIZE, 0, 0);
  ShowWindow(ret, SW_SHOW);

  return ret;
}