void QtWebPageEventHandler::handleInputEvent(const QInputEvent* event)
{
    if (m_viewportController) {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
        case QEvent::TouchBegin:
            m_viewportController->touchBegin();

            // The page viewport controller might still be animating kinetic scrolling or a scale animation
            // such as double-tap to zoom or the bounce back effect. A touch stops the kinetic scrolling
            // where as it does not stop the scale animation.
            // The gesture recognizer stops the kinetic scrolling animation if needed.
            break;
        case QEvent::MouseMove:
        case QEvent::TouchUpdate:
            // The scale animation can only be interrupted by a pinch gesture, which will then take over.
            if (m_viewportController->scaleAnimationActive() && m_pinchGestureRecognizer.isRecognized())
                m_viewportController->interruptScaleAnimation();
            break;
        case QEvent::MouseButtonRelease:
        case QEvent::TouchEnd:
            m_viewportController->touchEnd();
            break;
        default:
            break;
        }

        // If the scale animation is active we don't pass the event to the recognizers. In the future
        // we would want to queue the event here and repost then when the animation ends.
        if (m_viewportController->scaleAnimationActive())
            return;
    }

    bool isMouseEvent = false;

    switch (event->type()) {
    case QEvent::MouseButtonPress:
        isMouseEvent = true;
        m_isMouseButtonPressed = true;
        break;
    case QEvent::MouseMove:
        if (!m_isMouseButtonPressed)
            return;
        isMouseEvent = true;
        break;
    case QEvent::MouseButtonRelease:
        isMouseEvent = true;
        m_isMouseButtonPressed = false;
        break;
    case QEvent::MouseButtonDblClick:
        return;
    default:
        break;
    }

    QList<QTouchEvent::TouchPoint> activeTouchPoints;
    QTouchEvent::TouchPoint currentTouchPoint;
    qint64 eventTimestampMillis = event->timestamp();
    int touchPointCount = 0;

    if (!isMouseEvent) {
        const QTouchEvent* touchEvent = static_cast<const QTouchEvent*>(event);
        const QList<QTouchEvent::TouchPoint>& touchPoints = touchEvent->touchPoints();
        currentTouchPoint = touchPoints.first();
        touchPointCount = touchPoints.size();
        activeTouchPoints.reserve(touchPointCount);

        for (int i = 0; i < touchPointCount; ++i) {
            if (touchPoints[i].state() != Qt::TouchPointReleased)
                activeTouchPoints << touchPoints[i];
        }
    } else {
        const QMouseEvent* mouseEvent = static_cast<const QMouseEvent*>(event);
        touchPointCount = 1;

        // Make a distinction between mouse events on the basis of pressed buttons.
        currentTouchPoint.setId(mouseEvent->buttons());
        currentTouchPoint.setScreenPos(mouseEvent->screenPos());
        // For tap gesture hit testing the float touch rect is translated to
        // an int rect representing the radius of the touch point (size/2),
        // thus the touch rect has to have a size of at least 2.
        currentTouchPoint.setRect(QRectF(mouseEvent->localPos(), QSizeF(2, 2)));

        if (m_isMouseButtonPressed)
            activeTouchPoints << currentTouchPoint;
    }

    const int activeTouchPointCount = activeTouchPoints.size();

    if (!activeTouchPointCount) {
        if (touchPointCount == 1) {
            // No active touch points, one finger released.
            if (m_panGestureRecognizer.isRecognized())
                m_panGestureRecognizer.finish(currentTouchPoint, eventTimestampMillis);
            else {
                // The events did not result in a pan gesture.
                m_panGestureRecognizer.cancel();
                m_tapGestureRecognizer.finish(currentTouchPoint);
            }

        } else
            m_pinchGestureRecognizer.finish();

        // Early return since this was a touch-end event.
        return;
    } else if (activeTouchPointCount == 1) {
        // If the pinch gesture recognizer was previously in active state the content might
        // be out of valid zoom boundaries, thus we need to finish the pinch gesture here.
        // This will resume the content to valid zoom levels before the pan gesture is started.
        m_pinchGestureRecognizer.finish();
        m_panGestureRecognizer.update(activeTouchPoints.first(), eventTimestampMillis);
    } else if (activeTouchPointCount == 2) {
        m_panGestureRecognizer.cancel();
        m_pinchGestureRecognizer.update(activeTouchPoints.first(), activeTouchPoints.last());
    }

    if (m_panGestureRecognizer.isRecognized() || m_pinchGestureRecognizer.isRecognized() || m_webView->isMoving())
        m_tapGestureRecognizer.cancel();
    else if (touchPointCount == 1)
        m_tapGestureRecognizer.update(currentTouchPoint);

}