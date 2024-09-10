void ShapesWidget::drawEmwebMW(WPainter& painter)
{
  WPainterPath p;

  /* Path copied from our SVG for one fourth of the MW */

  p.moveTo(120.59634,24.072913);
  p.cubicTo(116.12064,34.518895,115.98477,44.605222,115.98477,45.732141);
  p.lineTo(115.98477,138.81088);
  p.lineTo(137.7399,138.81088);
  p.lineTo(137.7399,45.732141);
  p.cubicTo(137.7399,45.708164,137.83581,38.53904,140.84892,31.841463);
  p.cubicTo(144.14176,24.512492,149.113,21.235634,156.98545,21.235634);
  p.cubicTo(164.8499,21.235634,169.81314,24.512492,173.10599,31.841463);
  p.cubicTo(176.10311,38.53904,176.215,45.708164,176.215,45.780095);
  p.lineTo(176.215,70.41343);
  p.lineTo(197.97014,70.41343);
  p.lineTo(197.97014,45.732141);
  p.cubicTo(197.97014,44.605222,197.83427,34.518895,193.35057,24.072913);
  p.cubicTo(186.70894,8.5517985,173.77734,0,156.99344,0);
  p.cubicTo(140.17756,0,127.25396,8.5517985,120.59634,24.072913);

  /*
   * Paint it four times, translated and inverted
   */

  painter.drawPath(p);

  const double dx = 176. - 115.98477;

  painter.save();

  painter.translate(dx, 0);
  painter.drawPath(p);

  painter.translate(dx, 0);

  painter.scale(-1, -1);
  painter.translate(0, -138.81088);
  painter.translate(-115.98477 - 197.95 - dx, 0);
  painter.drawPath(p);

  painter.translate(dx, 0);
  painter.drawPath(p);

  painter.restore();
}