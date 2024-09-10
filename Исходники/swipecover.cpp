bool SwipeCover::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::ScrollPrepare:
    {
        for(int i=0; i<delta; i++)
            posLst.append(curPos);
        QScrollPrepareEvent *se = static_cast<QScrollPrepareEvent *>(e);
        se->setViewportSize(QSizeF(parentSize));
        se->setContentPosRange(QRectF(0.0, 0.0, 0.0,range));
        se->setContentPos(QPointF(0.0, curPos));
        se->accept();
        isScrolled=false;
        qDebug()<<"ScrollPrepare";
        return true;
    }
    case QEvent::Scroll:
    {
        QScrollEvent *se = static_cast<QScrollEvent *>(e);
        isScrolled = true;
        curPos  =  se->contentPos().y();
        scrollBar->setValue((int)(curPos/k));
        qDebug() <<"Scroll: " << curPos;
        int ic = 20;
        if (ic>0) {
        }
        se->accept();
        return true;
    }
    case QEvent::MouseButtonPress:
        isScrolled = false;
        return true;
    case QEvent::MouseButtonRelease:
        if(!isScrolled)
        {
            qDebug()<<"MouseButtonClick!!! "<<((QMouseEvent*)e)->pos();
            emit onClick(((QMouseEvent*)e)->pos()+QPoint(0,scrollBar->value()));
        }
        isScrolled = false;
        return true;

    default:
        return QWidget::event(e);
    }
    return true;

}