/*!
   Calculate the size for a arrow that fits into a rect of a given size

   \param arrowType Arrow type
   \param boundingSize Bounding size
   \return Size of the arrow
*/
QSize QwtArrowButton::arrowSize(Qt::ArrowType arrowType,
    const QSize &boundingSize) const
{
    QSize bs = boundingSize;
    if ( arrowType == Qt::UpArrow || arrowType == Qt::DownArrow )
        bs.transpose();
        
    const int MinLen = 2;
    const QSize sz = bs.expandedTo(
        QSize(MinLen, 2 * MinLen - 1)); // minimum

    int w = sz.width();
    int h = 2 * w - 1;

    if ( h > sz.height() )
    {
        h = sz.height();
        w = (h + 1) / 2;
    }

    QSize arrSize(w, h);
    if ( arrowType == Qt::UpArrow || arrowType == Qt::DownArrow )
        arrSize.transpose();

    return arrSize;
}