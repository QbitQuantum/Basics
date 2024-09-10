void FragmentCanvas::draw(QPainter & p) {
  if (! visible()) return;
  p.setRenderHint(QPainter::Antialiasing, true);
  QFontMetrics fm(the_canvas()->get_font(UmlNormalFont));
  int w = fm.width((name.isEmpty()) ? QString("X") : name);
  int h = fm.height() / 2;  
  QRect r = rect();
  QRect rname = r;
  
  rname.setWidth(w + h);
  rname.setHeight(fm.height() + h);
  
  int h1 = (fm.height() + h)/2;
  int x1 = rname.right() + h1;
  int y1 = rname.bottom() - h1;
  
  QColor bckgrnd = p.backgroundColor();

  p.setBackgroundMode((used_color == UmlTransparent) ? ::Qt::TransparentMode : ::Qt::OpaqueMode);

  QColor co = color(used_color);
  FILE * fp = svg();

  if (fp != 0)
    fputs("<g>\n", fp);
  
  p.setBackgroundColor(co);
  p.setFont(the_canvas()->get_font(UmlNormalFont));
  
  if (used_color != UmlTransparent)
    p.fillRect(r, co);
  else if (!name.isEmpty()) {
    Q3PointArray a(6);
    QBrush brsh = p.brush();
    
    a.setPoint(0, rname.left(), rname.top());
    a.setPoint(1, x1, rname.top());
    a.setPoint(2, x1, y1);
    a.setPoint(3, rname.right(), rname.bottom());
    a.setPoint(4, rname.left(), rname.bottom());
    a.setPoint(5, rname.left(), rname.top());

    p.setBrush(UmlWhiteColor);
    p.drawPolygon(a, TRUE, 0, 5);
    p.setBrush(brsh);
    
    if (fp != 0)
      draw_poly(fp, a, UmlWhite);
  }

  if (fp != 0)
    fprintf(fp, "\t<rect fill=\"%s\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
	    " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
	    svg_color(used_color), 
	    r.x(), r.y(), r.width() - 1, r.height() - 1);
  
  p.drawRect(r);
  
  if (refer != 0) {
    QString s = refer->get_name() + form;
    QRect r2(r.left(), r.top() + 2*fm.height(),
	     r.width(), fm.height());

    p.drawText(r2, ::Qt::AlignCenter, s);
    
    if (fp != 0)
      draw_text(r2, ::Qt::AlignCenter, s,
		p.font(), fp);
  }
  
  if (!name.isEmpty())
    p.drawText(rname, ::Qt::AlignCenter, name);
  if (fp != 0)
    draw_text(rname, ::Qt::AlignCenter, name,
	      p.font(), fp);
  
  p.drawLine(rname.left(), rname.bottom(), rname.right(), rname.bottom());
  p.drawLine(rname.right(), rname.bottom(), x1, y1);
  p.drawLine(x1, y1, x1, rname.top());

  if (fp != 0) {
    fprintf(fp, "\t<line stroke=\"black\" stroke-opacity=\"1\""
	    " x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",
	    rname.left(), rname.bottom(), rname.right(), rname.bottom());
    fprintf(fp, "\t<line stroke=\"black\" stroke-opacity=\"1\""
	    " x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",
	    rname.right(), rname.bottom(), x1, y1);
    fprintf(fp, "\t<line stroke=\"black\" stroke-opacity=\"1\""
	    " x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",
	    x1, y1, x1, rname.top());
    fputs("</g>\n", fp);
  }
	       
  p.setBackgroundColor(bckgrnd);
  
  if (selected())
    show_mark(p, r);
}