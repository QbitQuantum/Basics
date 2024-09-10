/*
 * InterfaceDrawBarBorder:  Draw border around a graph bar; the bar occupies
 *   the area "a" on hdc.
 */
void InterfaceDrawBarBorder( RawBitmap* prawbmpBackground, HDC hdc, AREA *a )
{
  int i, x, y;
  InterfaceElement *e;
  Bool vertical;

  elements[ELEMENT_BARRIGHT].x = a->cx;

  for (i = ELEMENT_BARLEFT; i <= ELEMENT_BARRIGHT; i++)
  {
    OffscreenWindowBackground(prawbmpBackground, a->x + elements[i].x, a->y + elements[i].y, 
			      elements[i].width, elements[i].height);
    
    OffscreenBitBlt(hdc, a->x + elements[i].x, a->y + elements[i].y, 
		    elements[i].width, elements[i].height,
		    elements[i].bits, 0, 0, DIBWIDTH(elements[i].width), 
		    OBB_COPY | OBB_FLIP | OBB_TRANSPARENT);
    GdiFlush();
  }

  repeaters[ELEMENT_BARBOTTOM].element.y = a->cy;

  for (i = ELEMENT_BARTOP; i <= ELEMENT_BARBOTTOM; i++)
  {
    e = &repeaters[i].element;
    x = e->x + a->x;
    y = e->y + a->y;
    vertical = repeaters[i].vertical;

    while (1)
    {
      if ((vertical && y >= a->y + a->cy) || (!vertical && x >= a->x + a->cx))
	break;

      OffscreenWindowBackground(prawbmpBackground, x, y, e->width, e->height);
      OffscreenBitBlt(hdc, x, y, e->width, e->height, e->bits, 0, 0, DIBWIDTH(e->width), 
		      OBB_COPY | OBB_FLIP | OBB_TRANSPARENT);
      if (vertical)
	y += e->height;
      else x += e->width;

      GdiFlush();
    }
  }
}