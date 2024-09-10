void PackageCanvas::draw(QPainter & p) {
  if (! visible()) return;
  p.setRenderHint(QPainter::Antialiasing, true);
  QRect r = rect();
  const BasicData * data = browser_node->get_data();  
  const QPixmap * px = 
    ProfiledStereotypes::diagramPixmap(data->get_stereotype(),
				       the_canvas()->zoom());
  FILE * fp = svg();
  
  if (fp != 0)
    fputs("<g>\n", fp);

  if (px != 0) {
    p.setBackgroundMode(::Qt::TransparentMode);
    
    
    int lft = (px->width() < width()) ? r.x() + (width() - px->width())/2 : r.x();
    
    p.drawPixmap(lft, r.y(), *px);
    if (fp != 0)
      // pixmap not really exported in SVG
      fprintf(fp, "\t<rect fill=\"%s\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
	      " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
	      svg_color(UmlBlack), lft, r.y(), px->width() - 1, px->height() - 1);
    
    r.moveBy(0, px->height());
    p.setFont(the_canvas()->get_font(UmlNormalBoldFont));
    p.drawText(r, ::Qt::AlignHCenter, browser_node->get_name());
    
    // pixmap not yet exported in SVG
    if (fp != 0)
      draw_text(r, ::Qt::AlignHCenter, browser_node->get_name(),
		p.font(), fp);
    p.setFont(the_canvas()->get_font(UmlNormalFont));
  }
  else {
    QColor bckgrnd = p.backgroundColor();
    QColor co = color(used_color);
    
    p.setBackgroundMode((used_color == UmlTransparent) ? ::Qt::TransparentMode : ::Qt::OpaqueMode);
    p.setBackgroundColor(co);
    p.setFont(the_canvas()->get_font(UmlNormalFont));
    
    QFontMetrics fm(the_canvas()->get_font(UmlNormalFont));
    const int four = (int) (4 * the_canvas()->zoom());
    const int he = fm.height();
    const int shadow = the_canvas()->shadow();
    if ((used_color != UmlTransparent) && (shadow != 0)) {
      r.setRight(r.right() - shadow);
      r.setBottom(r.bottom() - shadow);
    }
    
    r.setWidth(r.width() * 2 / 5);
    r.setHeight(he + four);
    if (used_color != UmlTransparent)
      p.fillRect(r, co);
    
    if (fp != 0)
      fprintf(fp, "\t<rect fill=\"%s\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
	      " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
	      svg_color(used_color), 
	      r.x(), r.y(), r.width() - 1, r.height() - 1);
    
    p.drawRect(r);
    
    if ((used_color != UmlTransparent) && (shadow != 0)) {
      p.fillRect (r.right(), r.top() + shadow,
		  shadow, r.height() - 1 - shadow,
		  ::Qt::darkGray);
      
      if (fp != 0)
	fprintf(fp, "\t<rect fill=\"#%06x\" stroke=\"none\" stroke-opacity=\"1\""
		" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
		QColor(::Qt::darkGray).rgb()&0xffffff,
		r.right(), r.top() + shadow, shadow - 1, r.height() - 1 - shadow - 1);
    }
    
    const char * name = browser_node->get_name();
    
    if (in_tab) {
      p.drawText(r, ::Qt::AlignCenter, name);
      if (fp != 0)
	draw_text(r, ::Qt::AlignCenter, name,
		  p.font(), fp);
    }
    
    r = rect();
    if ((used_color != UmlTransparent) && (shadow != 0)) {
      r.setRight(r.right() - shadow);
      r.setBottom(r.bottom() - shadow);
    }
    
    r.setTop(r.top() + he + four - 1);
    if (used_color != UmlTransparent)
      p.fillRect(r, co);
    
    if (fp != 0)
      fprintf(fp, "\t<rect fill=\"%s\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
	      " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
	      svg_color(used_color),
	      r.x(), r.y(), r.width() - 1, r.height() - 1);
    
    p.drawRect(r);
    
    if ((used_color != UmlTransparent) && (shadow != 0)) {
      p.fillRect (r.right(), r.top() + shadow,
		  shadow, r.height() - 1,
		  ::Qt::darkGray);
      p.fillRect (r.left() + shadow, r.bottom(),
		  r.width() - 1, shadow,
		  ::Qt::darkGray);
      
      if (fp != 0) {
	fprintf(fp, "\t<rect fill=\"#%06x\" stroke=\"none\" stroke-opacity=\"1\""
		" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
		QColor(::Qt::darkGray).rgb()&0xffffff,
		r.right(), r.top() + shadow, shadow - 1, r.height() - 1 - 1);
	
	fprintf(fp, "\t<rect fill=\"#%06x\" stroke=\"none\" stroke-opacity=\"1\""
		" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
		QColor(::Qt::darkGray).rgb()&0xffffff,
		r.left() + shadow, r.bottom(), r.width() - 1 - 1, shadow - 1);
      }
    }
    
    const int three = (int) (3 * the_canvas()->zoom());
    
    r.setTop(r.top() + three);
    
    if (! in_tab) {
      p.drawText(r, ::Qt::AlignHCenter + ::Qt::AlignTop, name);
      if (fp != 0)
	draw_text(r, ::Qt::AlignHCenter + ::Qt::AlignTop, name,
		  p.font(), fp);
      r.setTop(r.top() + he + three);
    }
    
    if (data->get_stereotype()[0]) {
      p.drawText(r, ::Qt::AlignHCenter + ::Qt::AlignTop, 
		 QString("<<") + toUnicode(data->get_short_stereotype()) + ">>");
      if (fp != 0)
	draw_text(r, ::Qt::AlignHCenter + ::Qt::AlignTop, 
		  QString("<<") + toUnicode(data->get_short_stereotype()) + ">>",
		  p.font(), fp);
      r.setTop(r.top() + he + three);
    }
    
    if (full_name != name) {
      p.setFont(the_canvas()->get_font(UmlNormalItalicFont));
      p.drawText(r, ::Qt::AlignHCenter + ::Qt::AlignTop, full_name);
      if (fp != 0)
	draw_text(r, ::Qt::AlignHCenter + ::Qt::AlignTop, full_name,
		  p.font(), fp);
      p.setFont(the_canvas()->get_font(UmlNormalFont));
    }
  
    p.setBackgroundColor(bckgrnd);
  }
  
  if (fp != 0)
    fputs("</g>\n", fp);
  
  if (selected())
    show_mark(p, rect());
}