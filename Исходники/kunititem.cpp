void KUnitItem::slotMouseMove(QGraphicsSceneMouseEvent *event)
{
    if (myMode == MouseMode_RESIZE)
    {
        QPointF curPoint(event->scenePos());
        QPointF curPointItem = this->mapFromScene(curPoint);

        bool flagx = lastPoint.x() > oppositePos.x();
        bool flagx1 = curPointItem.x() > oppositePos.x();
        bool flagy = lastPoint.y() > oppositePos.y();
        bool flagy1 = curPointItem.y() > oppositePos.y();


        qreal dist = 0;

        QRectF rectf;
        rectf.setRect(m_frame.x()
                      , m_frame.y()
                      , m_frame.width()
                      , m_frame.height());


        KResizeFocus::PosInHost pos = curResizeFocus->getInHost();
        if (pos == KResizeFocus::NORTH_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                dist = 20;
            }
            rectf.setY(curPointItem.y());
            rectf.setHeight(dist);
        }
        else if(pos == KResizeFocus::SOUTH_MIDDLE)
        {
            QPointF br = dashRect->rect().topRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                dist = 20;
            }
            rectf.setHeight(dist);
        }
        else if(pos == KResizeFocus::EAST_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomLeft();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                dist = 20;
            }
            rectf.setWidth(dist);
        }
        else if(pos == KResizeFocus::WEST_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                dist = 20;
            }
            rectf.setX(curPointItem.x());
            rectf.setWidth(dist);
        }
        else if(pos == KResizeFocus::NORTH_WEST)
        {
            QPointF topRight = dashRect->rect().topRight();
            QPointF bottomLeft = dashRect->rect().bottomLeft();

            qreal distx = Util::GetPointDistLine(oppositePos,topRight,curPointItem);
            qreal disty = Util::GetPointDistLine(oppositePos,bottomLeft,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setTopLeft(curPointItem);
        }
        else if(pos == KResizeFocus::NORTH_EAST)
        {
            QPointF topLeft = dashRect->rect().topLeft();
            QPointF bottomRight = dashRect->rect().bottomRight();

            qreal distx = Util::GetPointDistLine(oppositePos,topLeft,curPointItem);
            qreal disty = Util::GetPointDistLine(oppositePos,bottomRight,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setTopRight(curPointItem);
        }
        else if(pos == KResizeFocus::SOUTH_EAST)
        {
            QPointF topRight = dashRect->rect().topRight();
            QPointF bottomLeft = dashRect->rect().bottomLeft();

            qreal disty = Util::GetPointDistLine(oppositePos,topRight,curPointItem);
            qreal distx = Util::GetPointDistLine(oppositePos,bottomLeft,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setBottomRight(curPointItem);
        }
        else if(pos == KResizeFocus::SOUTH_WEST)
        {
            QPointF topLeft = dashRect->rect().topLeft();
            QPointF bottomRight = dashRect->rect().bottomRight();

            qreal disty = Util::GetPointDistLine(oppositePos,topLeft,curPointItem);
            qreal distx = Util::GetPointDistLine(oppositePos,bottomRight,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }
            rectf.setBottomLeft(curPointItem);
        }

        dashRect->setRect(rectf);
    }
    else if(myMode == MouseMode_ROTATE)
    {
        QPointF curPos = event->scenePos();
        QPointF cpos = this->mapToScene(frame().center());
//        qDebug()<<cpos;
		qreal angleLast = Util::ComputeAngle(mLastRotatePoint, cpos);
		qreal angleCur = Util::ComputeAngle(curPos, cpos);
        qreal angle = angleCur - angleLast;

        setAngle(angle);
        mLastRotatePoint = curPos;
        onRotate();
    }
    else if(myMode == MouseMode_MOVE)
    {
        onMoving();
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}