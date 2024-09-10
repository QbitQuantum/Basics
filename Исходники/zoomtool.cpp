void ZoomTool::scaleView(const QPointF &centerPos)
{

    QTransform transform;
    transform.scale(m_currentScale, m_currentScale);
    view()->setTransform(transform);

    QPointF adjustedCenterPos = centerPos;
    QSize rectSize(view()->rect().width() / m_currentScale,
                   view()->rect().height() / m_currentScale);

    QRectF sceneRect;
    if (qAbs(m_currentScale - 1.0f) < Constants::ZoomSnapDelta) {
        adjustedCenterPos.rx() = rectSize.width() / 2;
        adjustedCenterPos.ry() = rectSize.height() / 2;
    }

    if (m_currentScale < 1.0f) {
        adjustedCenterPos.rx() = rectSize.width() / 2;
        adjustedCenterPos.ry() = rectSize.height() / 2;
        sceneRect.setRect(view()->rect().width() / 2 -rectSize.width() / 2,
                          view()->rect().height() / 2 -rectSize.height() / 2,
                          rectSize.width(),
                          rectSize.height());
    } else {
        sceneRect.setRect(adjustedCenterPos.x() - rectSize.width() / 2,
                          adjustedCenterPos.y() - rectSize.height() / 2,
                          rectSize.width(),
                          rectSize.height());
    }

    view()->setSceneRect(sceneRect);
}