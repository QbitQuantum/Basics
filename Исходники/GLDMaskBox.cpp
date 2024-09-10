QPainterPath GLDMaskBox::buildPathRoundRectTip()
{
    // 建立圆角矩形tip路径
    QPainterPath path;

    do
    {
        QRect rc = this->rect();

        if (m_oTipBoxParam.m_sizeArrow.isValid())
        {
            rc -= QMargins(m_oTipBoxParam.m_sizeArrow.height(),
                           m_oTipBoxParam.m_sizeArrow.height(),
                           m_oTipBoxParam.m_sizeArrow.height(),
                           m_oTipBoxParam.m_sizeArrow.height());
        }
        else
        {
            break;
        }

        if (!m_oTipBoxParam.m_wgtOwner)
        {
            break;
        }

        // 添加圆角矩形
        path.addRoundedRect(rc, 20, 20);

        // 计算箭头（按照屏幕坐标进行计算）

        // 计算第一个交点（与外围）
        QPoint ptOwnerCenter = m_oTipBoxParam.m_wgtOwner->mapToGlobal(
                    m_oTipBoxParam.m_wgtOwner->rect().center());
        QPoint ptThisCenter = this->mapToGlobal(this->rect().center());

        QLineF lineCenters(ptOwnerCenter, ptThisCenter);
        QRectF rcRing(this->mapToGlobal(this->rect().topLeft()),
                      this->mapToGlobal(this->rect().bottomRight()));

        QPointF pt1(0, 0);
        QPointF pt2(0, 0);

        if (!calcCrossLine2Rect(lineCenters, rcRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow1 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        // 计算剩下两个交点（与内围）
        double dR = 0;
        double dAngle = 0;

        calcRadiusAndAngleOfPt2d(ptThisCenter, dR, dAngle, ptArrow1);
        QPointF ptNew1 = calcPtOfAngle2d(dR, dR, dAngle + 10, ptArrow1).toPoint();
        QPointF ptNew2 = calcPtOfAngle2d(dR, dR, dAngle - 10, ptArrow1).toPoint();

        QLineF line1(ptOwnerCenter, ptNew1);
        QLineF line2(ptOwnerCenter, ptNew2);

        QRectF rcInsideRing(this->mapToGlobal(rc.topLeft()), this->mapToGlobal(rc.bottomRight()));

        if (!calcCrossLine2Rect(line1, rcInsideRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow2 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        if (!calcCrossLine2Rect(line2, rcInsideRing, pt1, pt2))
        {
            break;
        }

        QPoint ptArrow3 = pt1.isNull() ? pt2.toPoint() : pt1.toPoint();

        QVector<QPoint> ptsArrow;
        ptsArrow << mapFromGlobal(ptArrow1)
                 << mapFromGlobal(ptArrow2)
                 << mapFromGlobal(ptArrow3)
                 << mapFromGlobal(ptArrow1);

        QPolygonF polygon(ptsArrow);
        QPainterPath pathArrow;
        pathArrow.addPolygon(polygon);

        path += pathArrow;

    } while(0);

    return path;
}