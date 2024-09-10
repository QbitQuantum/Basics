void map_text(MapGC *mgc, MapSettings *settings,
	      int x, int y, const char *text, int style)
{
  if (FALSE);
#ifdef HAVE_CAIRO
  else if (mgc->cairo_cr)
    {
      int xpos = x;
      int ypos = y;
      cairo_text_extents_t extents;

      cairo_select_font_face(mgc->cairo_cr, "Sans",
			     CAIRO_FONT_SLANT_NORMAL,
			     CAIRO_FONT_WEIGHT_NORMAL);

      if (style & 0x800)
	{
	  if (settings->pdamode)
	    cairo_set_font_size(mgc->cairo_cr, 9);
	  else
	    cairo_set_font_size(mgc->cairo_cr, 14);
	}
      else
	{
	  if (settings->pdamode)
	    cairo_set_font_size(mgc->cairo_cr, 8);
	  else
	    cairo_set_font_size(mgc->cairo_cr, 11);
	}

      cairo_text_extents(mgc->cairo_cr, text, &extents);

      if ((style & 0x300) == 0x100)
	{
	  xpos -= extents.width;
	}
      else if ((style & 0x300) == 0x200)
	{
	  xpos -= extents.width / 2;
	}
      else if ((style & 0x300) == 0x300)
	{
	  xpos -= extents.width / 2;
	  ypos -= extents.height / 2;
	}

      if (style & 0x400)
	map_bkg_rectangle(mgc, settings,
			  xpos, ypos, extents.width, extents.height);

      if (style & 1)
	cairo_set_source_rgb(mgc->cairo_cr, 0, 0, 1);
      else
	cairo_set_source_rgb(mgc->cairo_cr, 0, 0, 0);

      cairo_move_to(mgc->cairo_cr, xpos, ypos + extents.height);
      cairo_show_text(mgc->cairo_cr, text);
    }
#endif
#ifdef HAVE_GTK
  else if (mgc->gtk_drawable)
    {
      int xpos = x;
      int ypos = y;
      int width;
      int height;

      PangoFontDescription *fd;
      PangoLayout *layout =
	gtk_widget_create_pango_layout(mgc->gtk_widget, text);

      if (style & 0x800)
	{
	  if (settings->pdamode)
	    fd = pango_font_description_from_string("Sans 9");
	  else
	    fd = pango_font_description_from_string("Sans 14");
	}
      else
	{
	  if (settings->pdamode)
	    fd = pango_font_description_from_string("Sans 8");
	  else
	    fd = pango_font_description_from_string("Sans 11");
	}

      pango_layout_set_font_description(layout, fd);

      pango_layout_get_pixel_size(layout, &width, &height);

      if ((style & 0x300) == 0x100)
	{
	  xpos -= width;
	}
      else if ((style & 0x300) == 0x200)
	{
	  xpos -= width / 2;
	}
      else if ((style & 0x300) == 0x300)
	{
	  xpos -= width / 2;
	  ypos -= height / 2;
	}

      if (style & 0x400)
	map_bkg_rectangle(mgc, settings,
			  xpos, ypos, width, height);

      if (style & 1)
	gdk_draw_layout_with_colors(mgc->gtk_drawable, mgc->gtk_gc, xpos, ypos,
				    layout, &settings->blue, NULL);
      else
	gdk_draw_layout_with_colors(mgc->gtk_drawable, mgc->gtk_gc, xpos, ypos,
				    layout, &settings->black, NULL);

      if (layout != NULL)
	g_object_unref(G_OBJECT(layout));

      pango_font_description_free(fd);
    }
#endif
#ifdef HAVE_QT
  else if (mgc->qt_painter)
    {
      qt_text(mgc->qt_painter, settings,
	      x, y, text, style);
    }
#endif
#ifdef HAVE_QUARTZ
  else if (mgc->quartz_gc)
    {
      int xpos = x;
      int ypos = y;
      int width;
      int height;

      CGContextSelectFont(mgc->quartz_gc, "Verdana",
			  8, kCGEncodingMacRoman);

      if (style & 0x800)
	{
	  if (settings->pdamode)
	    CGContextSetFontSize(mgc->quartz_gc, 9);
	  else
	    CGContextSetFontSize(mgc->quartz_gc, 14);
	}
      else
	{
	  if (settings->pdamode)
	    CGContextSetFontSize(mgc->quartz_gc, 8);
	  else
	    CGContextSetFontSize(mgc->quartz_gc, 11);
	}

      {
	CGPoint oldPos = CGContextGetTextPosition(mgc->quartz_gc);
	CGContextSetTextDrawingMode(mgc->quartz_gc, kCGTextInvisible);
	CGContextShowText(mgc->quartz_gc, text, strlen(text));
	CGPoint newPos = CGContextGetTextPosition(mgc->quartz_gc);
	CGContextSetTextDrawingMode(mgc->quartz_gc, kCGTextFill);
	CGContextSetTextPosition(mgc->quartz_gc, oldPos.x, oldPos.y);
	width = newPos.x - oldPos.x;
      }

      if ((style & 0x300) == 0x100)
	{
	  xpos -= width;
	}
      else if ((style & 0x300) == 0x200)
	{
	  xpos -= width / 2;
	}
      else if ((style & 0x300) == 0x300)
	{
	  xpos -= width / 2;
	  ypos -= height / 2;
	}

      if (style & 0x400)
	map_bkg_rectangle(mgc, settings,
			  xpos, ypos, width, height);

      if (style & 1)
	CGContextSetRGBStrokeColor(mgc->quartz_gc, 0, 0, 1, 1);
      else
	CGContextSetRGBStrokeColor(mgc->quartz_gc, 0, 0, 0, 1);

      CGContextSetTextPosition(mgc->quartz_gc, xpos, ypos);
      CGContextShowText(mgc->quartz_gc, text, strlen(text));
    }
#endif
#ifdef WIN32
  else if (mgc->win_dc)
    {
      int xpos = x;
      int ypos = y;
      int fontSize;
      HFONT oldFont;
      HFONT font;
      SIZE textSize;

      if (style & 0x800)
	{
	  if (settings->pdamode)
	    fontSize = 9;
	  else
	    fontSize = 14;
	}
      else
	{
	  if (settings->pdamode)
	    fontSize = 8;
	  else
	    fontSize = 11;
	}

      fontSize = fontSize * 3 / 2;

      font = CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MSSansSerif");
      oldFont = SelectObject(mgc->win_dc, font);

      GetTextExtentPoint32(mgc->win_dc, text, strlen(text), &textSize);

      if ((style & 0x300) == 0x100)
	{
	  xpos -= textSize.cx;
	}
      else if ((style & 0x300) == 0x200)
	{
	  xpos -= textSize.cx / 2;
	}
      else if ((style & 0x300) == 0x300)
	{
	  xpos -= textSize.cx / 2;
	  ypos -= textSize.cy / 2;
	}

      if (style & 0x400)
	map_bkg_rectangle(mgc, settings,
			  xpos, ypos, textSize.cx, textSize.cy);

      if (style & 1)
	SetTextColor(mgc->win_dc, RGB(0x00, 0x00, 0xff));
      else
	SetTextColor(mgc->win_dc, RGB(0x00, 0x00, 0x00));

      SetBkMode(mgc->win_dc, TRANSPARENT);
      TextOut(mgc->win_dc, xpos, ypos, text, strlen(text));
      SelectObject(mgc->win_dc, oldFont);
      DeleteObject(font);
    }
#endif
}