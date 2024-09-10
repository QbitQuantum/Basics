static void drawTest(Ihandle* ih)
{
  RECT rect;
  HDC hDC = (HDC)IupGetAttribute(ih, "PREVIEWDC");
  int w = IupGetInt(ih, "PREVIEWWIDTH");
  int h = IupGetInt(ih, "PREVIEWHEIGHT");

  SetRect(&rect, 0, 0, w, h);
  FillRect(hDC, &rect, GetStockObject(WHITE_BRUSH));

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(255, 0, 0));

  MoveToEx(hDC, 0, 0, NULL);
  LineTo(hDC, w-1, h-1);
  MoveToEx(hDC, 0, h-1, NULL);
  LineTo(hDC, w-1, 0);
}