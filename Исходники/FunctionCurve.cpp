/// Draw curve in Dots style
void FunctionCurve::drawDots(QPainter *painter, 
  const QwtScaleMap &xMap, const QwtScaleMap &yMap,
  const QRect &canvasRect) const
{
  const double start = xMap.s1();
  const double end = xMap.s2();

  const size_t n = m_x->size();
  // find first point to draw which is 0 or the one before first visible
  size_t istart = 0;
  for(; istart < n; ++istart)
  {
    const double& x = (*m_x)[istart];
    if ( x < start ) continue;
    if ( x > end ) break;
    if ( istart > 0 ) --istart;
    break;
  }
  if ( istart >= n ) return;
  size_t iend = n;

  bool doDrawSymbols = m_symbol->style() != QwtSymbol::NoSymbol;
  if ( doDrawSymbols && m_pointCoords.size() != n )
  {
    m_pointCoords.resize(n);
  }

  // draw the points
  for(size_t i = istart; i < n; ++i)
  {
    const double& x = (*m_x)[i];
    if ( x > end )
    {
      iend = i;
      break;
    }
    int x1 = xMap.transform(x);
    int y1 = yMap.transform(m_y.getCalculated(i));
    painter->drawPoint(x1,y1);
    if ( doDrawSymbols )
    {
      m_pointCoords[i] = QPoint(x1,y1);
    }
  }

  // draw the symbols
  if ( doDrawSymbols )
  {
    drawSymbols(painter,istart,iend);
  }
}