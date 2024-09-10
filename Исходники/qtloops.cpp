void plotPathsToPainter(QPainter& painter, QPainterPath& path,
			const Numpy1DObj& x, const Numpy1DObj& y,
			const Numpy1DObj* scaling,
			const QRectF* clip,
			const QImage* colorimg)
{
  QRectF cliprect( QPointF(-32767,-32767), QPointF(32767,32767) );
  if( clip != 0 )
    {
      qreal x1, y1, x2, y2;
      clip->getCoords(&x1, &y1, &x2, &y2);
      cliprect.setCoords(x1, y1, x2, y2);
    }
  QRectF pathbox = path.boundingRect();
  cliprect.adjust(pathbox.left(), pathbox.top(),
		  pathbox.bottom(), pathbox.right());

  // keep track of duplicate points
  QPointF lastpt(-1e6, -1e6);
  // keep original transformation for restoration after each iteration
  QTransform origtrans(painter.worldTransform());

  // number of iterations
  int size = min(x.dim, y.dim);

  // if few color points, trim down number of paths
  if( colorimg != 0 )
    size = min(size, colorimg->width());
  // too few scaling points
  if( scaling != 0 )
    size = min(size, scaling->dim);

  // draw each path
  for(int i = 0; i < size; ++i)
    {
      const QPointF pt(x(i), y(i));
      if( cliprect.contains(pt) && ! smallDelta(lastpt, pt) )
	{
	  painter.translate(pt);
	  if( scaling != 0 )
	    {
	      // scale point if requested
	      const qreal s = (*scaling)(i);
	      painter.scale(s, s);
	    }
	  if( colorimg != 0 )
	    {
	      // get color from pixel and create a new brush
	      QBrush b( QColor::fromRgba(colorimg->pixel(i, 0)) );
	      painter.setBrush(b);
	    }

	  painter.drawPath(path);
	  painter.setWorldTransform(origtrans);
	  lastpt = pt;
	}
    }
}