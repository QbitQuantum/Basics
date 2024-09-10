/***********************************************************************
 *Funtion : Get the handle rect
 *Return  : QRectF handle rect.
 *Parameter: handle id.
 **********************************************************************/
QRectF SamDrawItemBase::getHandleRect(int iHandleID, QRectF &qrcBondingRect)
{
    QRectF qrRect;
    // get the center of the handle in logical coords
    QPointF qpPoint = getHandle(iHandleID, qrcBondingRect);

    /*Set the rect and normalize it*/
    qrRect.setRect(qpPoint.rx()-SAMDRAW_TRACKER_POS_OFT, qpPoint.ry()-SAMDRAW_TRACKER_POS_OFT, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
    qrRect = qrRect.normalized();

    return qrRect;
}