void QElipseItem::SetLeft(qreal nLeft) //set the rect left
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setLeft(nLeft);
    setRect(nrect);
}