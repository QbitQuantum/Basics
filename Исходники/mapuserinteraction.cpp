bool MapUserInteraction::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    Q_D(MapUserInteraction);

    Q_ASSERT(d->map);
    MapHelper *helper = d->map->helper();

//    qDebug() << "Event" << event->type() << helper;

    if (!helper)
        return false;

    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (helper->mouseDown(e))
            e->accept();

        break;
    }

    case QEvent::MouseButtonRelease: {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (helper->mouseUp(e))
            e->accept();
        break;
    }

    case QEvent::MouseMove: {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (helper->mouseMove(e))
            e->accept();
        break;
    }

    case QEvent::Wheel: {
        QWheelEvent *e = static_cast<QWheelEvent*>(event);
        if (helper->wheelEvent(e))
            e->accept();
        break;
    }

    case QEvent::KeyPress: {
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if (helper->keyPress(e))
            e->accept();
        break;
    }

    case QEvent::KeyRelease: {
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if (helper->keyRelease(e))
            e->accept();
        break;
    }

    case QEvent::Gesture: {
#if 0
        static bool even = false;
        even = !even; // ХЗ почему, но ТАП-ХОЛД срабатывает дважды. Чётные срабатывание откидываем
        if (even)
            helper->gesture(static_cast<QGestureEvent *>(event));
#endif
        break;

#if 0
        if (QGesture *swipe = ge->gesture(Qt::SwipeGesture)) {
            LogD("GE") << "SwipeGesture";
            static_cast<QSwipeGesture *>(swipe);
        }
        if (QGesture *pan = ge->gesture(Qt::PanGesture)) {
            static_cast<QPanGesture *>(pan);
            LogD("GE") << "PanGesture";
        }
#endif
    }

    case QEvent::TouchBegin:
    {
        QTouchEvent *e = static_cast<QTouchEvent *>(event);
        if (helper->touch(e))
            e->accept();

        QList<QTouchEvent::TouchPoint> pts = e->touchPoints();
        if (pts.size() == 1) {
            QRectF r = pts.first().sceneRect();
            r.moveCenter(r.center() - d->map->position());
        }
        break;
    }
    case QEvent::TouchEnd:
    {
        QTouchEvent *e = static_cast<QTouchEvent *>(event);
        if (helper->touch(e))
            e->accept();

        QList<QTouchEvent::TouchPoint> pts = e->touchPoints();
        if (pts.size() == 1) {
            QRectF r = pts.first().sceneRect();
            r.moveCenter(r.center() - d->map->position());
        }
        break;
    }
    case QEvent::TouchUpdate:
    {
        QTouchEvent *e = static_cast<QTouchEvent *>(event);
        if (helper->touch(e))
            e->accept();
        break;
    }


    default:
        return false;
        break;
    } // switch (event->type())

    return true;
}