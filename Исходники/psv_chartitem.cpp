void PSV_ChartItem::updateForDouble()
{
    QMapIterator<QString,PSV_CurveInfo> iter(m_curveDataMap);
    qreal posY = m_staStartPoint.y();
    qreal posX = m_staStartPoint.x();
    while(iter.hasNext())
    {
        iter.next();
        PSV_CurveInfo curveInfo = iter.value();
        updateAxisRange(curveInfo.m_axisType);
        addCurveItem(curveInfo);
        addEllipseItem(curveInfo);
        if(!isStaHidden())
        {
            QGraphicsTextItem *textItem = new QGraphicsTextItem(this);
            textItem->setData(E_ITEM_TYPE,PSV::staLabelItem);
            textItem->setData(E_CURVE_NAME,curveInfo.m_curveName);
            textItem->setFlags(QGraphicsItem::ItemIsSelectable);
            textItem->installSceneEventFilter(this);

            textItem->setDefaultTextColor(getDefaultColor());
            textItem->setFont(staFont());
            textItem->setHtml(curveInfo.m_staHtmText);
            double textHeight = textItem->boundingRect().height();
            int staMaxHeight = (int)textHeight* 6 / 10;
            textItem->setPos(posX + textItem->boundingRect().height(),posY);

            QPixmap pixmap(staMaxHeight,staMaxHeight);
            pixmap.fill();
            QPen pen(curveInfo.m_lineColor);
            pen.setWidth(3);
            QPainter painter(&pixmap);
            painter.setPen(pen);
            if(!curveInfo.m_isHidden)
            {
                QBrush brush(curveInfo.m_lineColor);
                painter.setBrush(brush);
            }
            painter.drawRect(0, 0, pixmap.height(), pixmap.height());
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap,this);
            pixmapItem->setPixmap(pixmap);
            pixmapItem->setPos(posX,posY + textHeight * 2 / 10);
            pixmapItem->setData(E_ITEM_TYPE,PSV::staLabelItem);
            pixmapItem->setData(E_CURVE_NAME,curveInfo.m_curveName);
            pixmapItem->setFlags(QGraphicsItem::ItemIsSelectable);
            pixmapItem->installSceneEventFilter(this);
            if(posX + 2 * m_staMaxWidth > m_chartRect.right())
            {
                posX = m_staStartPoint.x();
                posY += textItem->boundingRect().height() + getData(PSV::margin,3).toInt();
            }
            else
            {
                posX += m_staMaxWidth;
            }
        }
    }
    //TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
    //    QGraphicsRectItem *item = new QGraphicsRectItem(m_rect,this);//TTTTTTTTTTTTTTT
    //    item->setPen(QPen(QColor(Qt::red)));//TTTTTTTTTTTTTTT
    //TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
}