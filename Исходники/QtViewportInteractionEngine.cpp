bool QtViewportInteractionEngine::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::ScrollPrepare: {
        QScrollPrepareEvent* prepareEvent = static_cast<QScrollPrepareEvent*>(event);
        const QRectF viewportRect = m_viewport->boundingRect();
        const QRectF contentRect = m_viewport->mapRectFromItem(m_content, m_content->boundingRect());
        const QRectF posRange = computePosRangeForItemAtScale(m_content->contentsScale());
        prepareEvent->setContentPosRange(posRange);
        prepareEvent->setViewportSize(viewportRect.size());

        // As we want to push the contents and not actually scroll it, we need to invert the positions here.
        prepareEvent->setContentPos(-contentRect.topLeft());
        prepareEvent->accept();
        return true;
    }
    case QEvent::Scroll: {
        QScrollEvent* scrollEvent = static_cast<QScrollEvent*>(event);
        QPointF newPos = -scrollEvent->contentPos() - scrollEvent->overshootDistance();
        if (m_content->pos() != newPos) {
            QPointF currentPosInCSSCoordinates = m_viewport->mapToWebContent(m_content->pos());
            QPointF newPosInCSSCoordinates = m_viewport->mapToWebContent(newPos);

            // This must be emitted before viewportUpdateRequested so that the web process knows where to look for tiles.
            emit viewportTrajectoryVectorChanged(currentPosInCSSCoordinates - newPosInCSSCoordinates);
            m_content->setPos(newPos);
        }
        return true;
    }
    default:
        break;
    }
    return QObject::event(event);
}