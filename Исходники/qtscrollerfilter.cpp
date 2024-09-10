bool QtScrollerFilter::eventFilter_QAbstractScrollArea(QAbstractScrollArea *area, QEvent *event)
{
    switch (event->type()) {
    case QtScrollPrepareEvent::ScrollPrepare:
    {
        QtScrollPrepareEvent *se = static_cast<QtScrollPrepareEvent *>(event);
        if (canStartScrollingAt_QAbstractScrollArea(area, se->startPos().toPoint())) {
            QScrollBar *hBar = area->horizontalScrollBar();
            QScrollBar *vBar = area->verticalScrollBar();

            se->setViewportSize(QSizeF(area->viewport()->size()));
            se->setContentPosRange(QRectF(0, 0, hBar->maximum(), vBar->maximum()));
            se->setContentPos(QPointF(hBar->value(), vBar->value()));
            se->accept();
            return true;
        }
        return false;
    }
    case QtScrollEvent::Scroll:
    {
        QtScrollEvent *se = static_cast<QtScrollEvent *>(event);

        QScrollBar *hBar = area->horizontalScrollBar();
        QScrollBar *vBar = area->verticalScrollBar();
        hBar->setValue(se->contentPos().x());
        vBar->setValue(se->contentPos().y());

        QPoint os = overshoot.value(area);
#ifdef Q_WS_WIN
        typedef BOOL (*PtrBeginPanningFeedback)(HWND);
        typedef BOOL (*PtrUpdatePanningFeedback)(HWND, LONG, LONG, BOOL);
        typedef BOOL (*PtrEndPanningFeedback)(HWND, BOOL);

        static PtrBeginPanningFeedback ptrBeginPanningFeedback = 0;
        static PtrUpdatePanningFeedback ptrUpdatePanningFeedback = 0;
        static PtrEndPanningFeedback ptrEndPanningFeedback = 0;

        if (!ptrBeginPanningFeedback)
            ptrBeginPanningFeedback = (PtrBeginPanningFeedback) QLibrary::resolve(QLatin1String("UxTheme"), "BeginPanningFeedback");
        if (!ptrUpdatePanningFeedback)
            ptrUpdatePanningFeedback = (PtrUpdatePanningFeedback) QLibrary::resolve(QLatin1String("UxTheme"), "UpdatePanningFeedback");
        if (!ptrEndPanningFeedback)
            ptrEndPanningFeedback = (PtrEndPanningFeedback) QLibrary::resolve(QLatin1String("UxTheme"), "EndPanningFeedback");

        if (ptrBeginPanningFeedback && ptrUpdatePanningFeedback && ptrEndPanningFeedback) {
            WId wid = area->window()->winId();

            if (!se->overshootDistance().isNull() && os.isNull())
                ptrBeginPanningFeedback(wid);
            if (!se->overshootDistance().isNull())
                ptrUpdatePanningFeedback(wid, -se->overshootDistance().x(), -se->overshootDistance().y(), false);
            if (se->overshootDistance().isNull() && !os.isNull())
                ptrEndPanningFeedback(wid, true);
        } else
#endif
        {
            QPoint delta = os - se->overshootDistance().toPoint();
            if (!delta.isNull()) {
                ignoreMove = true;
                area->viewport()->move(area->viewport()->pos() + delta);
                ignoreMove = false;
            }
        }
        overshoot[area] = se->overshootDistance().toPoint();
        return true;
    }
    case QEvent::Move: {
        if (!ignoreMove && !overshoot.value(area).isNull()) {
            ignoreMove = true;
            area->viewport()->move(area->viewport()->pos() - overshoot.value(area));
            ignoreMove = false;
        }
        return false;
    }
    default:
        return false;
    }
}