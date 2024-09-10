static void DrawLayerButton(HDC dc, RECT rect, const sLayer& layer, bool pushed)
{
  // get the menu color
  DWORD sys_color = GetSysColor(COLOR_MENU);
  RGB menu_color = {
    GetRValue(sys_color),
    GetGValue(sys_color),
    GetBValue(sys_color),
  };
  RGB white = { 255, 255, 255 };
  RGB black = { 0,   0,   0   };
  if (pushed) {
    std::swap(white, black);
  }
  HPEN very_light = CreateShadedPen(menu_color, white, 64);
  HPEN light      = CreateShadedPen(menu_color, white, 192);
  HPEN dark       = CreateShadedPen(menu_color, black, 192);
  HPEN very_dark  = CreateShadedPen(menu_color, black, 64);
  SaveDC(dc);
  SetROP2(dc, R2_COPYPEN);
  
  // draw the outer border
  SelectObject(dc, very_light);
  MoveToEx(dc, rect.left, rect.bottom - 1, NULL);
  LineTo(dc, rect.left, rect.top);
  LineTo(dc, rect.right - 1, rect.top);
  SelectObject(dc, very_dark);
  MoveToEx(dc, rect.left, rect.bottom - 1, NULL);
  LineTo(dc, rect.right - 1, rect.bottom - 1);
  LineTo(dc, rect.right - 1, rect.top);
 
  InflateRect(&rect, -1, -1);
  // draw the inner border
  SelectObject(dc, light);
  MoveToEx(dc, rect.left, rect.bottom - 1, NULL);
  LineTo(dc, rect.left, rect.top);
  LineTo(dc, rect.right - 1, rect.top);
  SelectObject(dc, dark);
  MoveToEx(dc, rect.left, rect.bottom - 1, NULL);
  LineTo(dc, rect.right - 1, rect.bottom - 1);
  LineTo(dc, rect.right - 1, rect.top);
 
  InflateRect(&rect, -1, -1);
  
  // draw the center of the button
  FillRect(dc, &rect, (HBRUSH)(COLOR_MENU + 1));
  int y = (rect.bottom - rect.top) / 2;
  int icon = (layer.IsVisible() ? IDI_LAYER_VISIBLE : IDI_LAYER_INVISIBLE);
  DrawIconEx(
    dc,
    rect.left + y - 8,
    rect.top + y - 8,
    LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(icon)),
    16,
    16,
    0,
    NULL,
    DI_NORMAL);
  rect.left += 18;
  SelectObject(dc, GetStockObject(DEFAULT_GUI_FONT));
  SetTextColor(dc, 0x000000);
  SetBkColor(dc, 0xFFFFFF);
  SetBkMode(dc, TRANSPARENT);
  DrawText(dc, layer.GetName(), strlen(layer.GetName()), &rect, DT_CENTER | DT_VCENTER);
  // clean up
  RestoreDC(dc, -1);
  DeleteObject(very_light);
  DeleteObject(light);
  DeleteObject(dark);
  DeleteObject(very_dark);
}