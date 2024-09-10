static void winFrameDrawItem(Ihandle* ih, DRAWITEMSTRUCT *drawitem)
{ 
  iupwinBitmapDC bmpDC;
  HDC hDC = iupwinDrawCreateBitmapDC(&bmpDC, drawitem->hDC, drawitem->rcItem.right-drawitem->rcItem.left, 
                                                            drawitem->rcItem.bottom-drawitem->rcItem.top);

  iupwinDrawParentBackground(ih, hDC, &drawitem->rcItem);

  if (iupAttribGet(ih, "_IUPFRAME_HAS_TITLE"))
  {
    int x, y;
    HFONT hOldFont, hFont = (HFONT)iupwinGetHFontAttrib(ih);
    int txt_height = iupFrameGetTitleHeight(ih);
    COLORREF fgcolor;
    SIZE size;

    char* title = iupdrvBaseGetTitleAttrib(ih);
    if (!title) title = "";

    x = drawitem->rcItem.left+7;
    y = drawitem->rcItem.top;

    hOldFont = SelectObject(hDC, hFont);
    GetTextExtentPoint32(hDC, title, strlen(title), &size);
    ExcludeClipRect(hDC, x-2, y, x+size.cx+2, y+size.cy);

    drawitem->rcItem.top += txt_height/2;
    if (iupwin_comctl32ver6)
      iupwinDrawThemeFrameBorder(ih->handle, hDC, &drawitem->rcItem, drawitem->itemState);
    else
      DrawEdge(hDC, &drawitem->rcItem, EDGE_ETCHED, BF_RECT);

    SelectClipRgn(hDC, NULL);

    if (drawitem->itemState & ODS_DISABLED)
      fgcolor = GetSysColor(COLOR_GRAYTEXT);
    else
    {
      unsigned char r, g, b;
      char* color = iupAttribGetInherit(ih, "FGCOLOR");
      if (!color)
      {
        if (!iupwinDrawGetThemeFrameFgColor(ih->handle, &fgcolor))
          fgcolor = 0;  /* black */
      }
      else
      {
        if (iupStrToRGB(color, &r, &g, &b))
          fgcolor = RGB(r,g,b);
        else
          fgcolor = 0;  /* black */
      }
    }

    winFrameDrawText(hDC, title, x, y, fgcolor);

    SelectObject(hDC, hOldFont);
  }
  else
  {
    char* value = iupAttribGetStr(ih, "SUNKEN");
    if (iupStrBoolean(value))
      DrawEdge(hDC, &drawitem->rcItem, EDGE_SUNKEN, BF_RECT);
    else
      DrawEdge(hDC, &drawitem->rcItem, EDGE_ETCHED, BF_RECT);
  }

  iupwinDrawDestroyBitmapDC(&bmpDC);
}