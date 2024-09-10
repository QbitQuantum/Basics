static void winButtonDrawImageText(Ihandle* ih, HDC hDC, int rect_width, int rect_height, int border, UINT itemState)
{
  int xpad = ih->data->horiz_padding + border, 
      ypad = ih->data->vert_padding + border;
  int x, y, width, height, 
      txt_x, txt_y, txt_width, txt_height, 
      img_x, img_y, img_width, img_height, 
      bpp, shift = 0, style = 0;
  HFONT hFont = (HFONT)iupwinGetHFontAttrib(ih);
  HBITMAP hBitmap, hMask;
  COLORREF fgcolor;

  char* title = iupAttribGet(ih, "TITLE");
  char* str = iupStrProcessMnemonic(title, NULL, 0);   /* remove & */
  iupdrvFontGetMultiLineStringSize(ih, str, &txt_width, &txt_height);
  if (str && str!=title) free(str);

  if (itemState & ODS_DISABLED)
    fgcolor = GetSysColor(COLOR_GRAYTEXT);
  else
    fgcolor = ih->data->fgcolor;

  hBitmap = winButtonGetBitmap(ih, itemState, NULL, &img_width, &img_height, &bpp, &hMask);
  if (!hBitmap)
    return;

  if (ih->data->img_position == IUP_IMGPOS_RIGHT ||
      ih->data->img_position == IUP_IMGPOS_LEFT)
  {
    width  = img_width + txt_width + ih->data->spacing;
    height = iupMAX(img_height, txt_height);
  }
  else
  {
    width = iupMAX(img_width, txt_width);
    height = img_height + txt_height + ih->data->spacing;
  }

  if (itemState & ODS_SELECTED && !iupwin_comctl32ver6)
    shift = 1;

  if (itemState & ODS_NOACCEL && !iupwinGetKeyBoardCues())
    style |= DT_HIDEPREFIX;

  x = winButtonCalcAlignPosX(ih->data->horiz_alignment, rect_width, width, xpad, shift);
  y = winButtonCalcAlignPosY(ih->data->vert_alignment, rect_height, height, ypad, shift);

  switch(ih->data->img_position)
  {
  case IUP_IMGPOS_TOP:
    img_y = y;
    txt_y = y + img_height + ih->data->spacing;
    if (img_width > txt_width)
    {
      img_x = x;
      txt_x = x + (img_width-txt_width)/2;
    }
    else
    {
      img_x = x + (txt_width-img_width)/2;
      txt_x = x;
    }
    break;
  case IUP_IMGPOS_BOTTOM:
    img_y = y + txt_height + ih->data->spacing;
    txt_y = y;
    if (img_width > txt_width)
    {
      img_x = x;
      txt_x = x + (img_width-txt_width)/2;
    }
    else
    {
      img_x = x + (txt_width-img_width)/2;
      txt_x = x;
    }
    break;
  case IUP_IMGPOS_RIGHT:
    img_x = x + txt_width + ih->data->spacing;
    txt_x = x;
    if (img_height > txt_height)
    {
      img_y = y;
      txt_y = y + (img_height-txt_height)/2;
    }
    else
    {
      img_y = y + (txt_height-img_height)/2;
      txt_y = y;
    }
    break;
  default: /* IUP_IMGPOS_LEFT */
    img_x = x;
    txt_x = x + img_width + ih->data->spacing;
    if (img_height > txt_height)
    {
      img_y = y;
      txt_y = y + (img_height-txt_height)/2;
    }
    else
    {
      img_y = y + (txt_height-img_height)/2;
      txt_y = y;
    }
    break;
  }

  if (ih->data->horiz_alignment == IUP_ALIGN_ACENTER)
    style |= DT_CENTER;  /* let DrawText do the internal horizontal alignment, usefull for multiple lines */
  else if (ih->data->horiz_alignment == IUP_ALIGN_ARIGHT)
    style |= DT_RIGHT;

  iupwinDrawBitmap(hDC, hBitmap, hMask, img_x, img_y, img_width, img_height, bpp);
  iupwinDrawText(hDC, title, txt_x, txt_y, txt_width, txt_height, hFont, fgcolor, style);

  if (hMask)
    DeleteObject(hMask);
}