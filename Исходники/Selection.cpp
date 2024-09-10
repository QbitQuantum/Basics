void Selection::transform(QTransform transform, int pageNum)
{
  m_selectionPolygon = transform.map(m_selectionPolygon);

  qreal sx = transform.m11();
  qreal sy = transform.m22();
  qreal s = (sx + sy) / 2.0;

  for (int i = 0; i < m_strokes.size(); ++i)
  {
    m_strokes[i].points = transform.map(m_strokes[i].points);
    /*
    'if (!transform.isRotating())' doesn't work, since rotation of 180 and 360 degrees is treated as a scaling transformation. Same goes for
    'if (transform.isScaling())'
    */
    if (transform.determinant() != 1)
    {
      m_strokes[i].penWidth = m_strokes[i].penWidth * s;
    }
  }
  if (transform.determinant() != 1)
  {
    m_x_padding *= sx;
    m_y_padding *= sy;
  }
  if (transform.isRotating())
  {
    m_x_padding = m_padding;
    m_y_padding = m_padding;
  }

  m_angle = 0.0;

  setPageNum(pageNum);
}