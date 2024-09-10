/*!
    Translate a rectangle from plot into pixel coordinates
    \return Rectangle in pixel coordinates
    \sa QwtPlotPicker::invTransform()
*/
QRect QwtPlotPicker::transform(const QwtDoubleRect &rect) const
{
    QwtDiMap xMap = plot()->canvasMap(d_xAxis);
    QwtDiMap yMap = plot()->canvasMap(d_yAxis);

    const int x1 = xMap.transform(rect.x1());
    const int x2 = xMap.transform(rect.x2());
    const int y1 = yMap.transform(rect.y1());
    const int y2 = yMap.transform(rect.y2());

    return QRect(x1, y1, x2 - x1, y2 - y1);
}