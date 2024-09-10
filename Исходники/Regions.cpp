  void xorRect(Graphics &g, const Point &pt)
  {
    Rect rc(VACA_MIN(m_startPoint.x, pt.x),
	    VACA_MIN(m_startPoint.y, pt.y),
	    abs(m_startPoint.x-pt.x)+1,
	    abs(m_startPoint.y-pt.y)+1);
    
    g.setRop2(R2_NOTXORPEN);
    g.intersectClipRect(getAbsoluteClientBounds());

    Pen pen(Color::Black);			// TODO XorPen?

    if (m_ellipses)
      g.drawEllipse(pen, rc);
    else
      g.drawRect(pen, rc);

    g.setRop2(R2_COPYPEN);
  }