/*!
  \return Bounding rectangle of all samples.
  For an empty series the rectangle is invalid.
*/
QRectF QwtPlotTradingCurve::boundingRect() const
{
    QRectF rect = QwtPlotSeriesItem::boundingRect();
    if ( orientation() == Qt::Vertical )
        rect.setRect( rect.y(), rect.x(), rect.height(), rect.width() );

    return rect;
}