void QAndroidCameraFocusControl::updateFocusZones(QCameraFocusZone::FocusZoneStatus status)
{
    if (!m_session->camera())
        return;

    // create a focus zone (50x50 pixel) around the focus point
    m_focusZones.clear();

    if (m_actualFocusPoint.isNull())
        return;

    QSize viewportSize = m_session->camera()->previewSize();

    if (!viewportSize.isValid())
        return;

    if (m_session->camera()->getDisplayOrientation() % 180)
        viewportSize.transpose();

    QSizeF focusSize(50.f / viewportSize.width(), 50.f / viewportSize.height());
    float x = qBound(qreal(0),
                     m_actualFocusPoint.x() - (focusSize.width() / 2),
                     1.f - focusSize.width());
    float y = qBound(qreal(0),
                     m_actualFocusPoint.y() - (focusSize.height() / 2),
                     1.f - focusSize.height());

    QRectF area(QPointF(x, y), focusSize);

    m_focusZones.append(QCameraFocusZone(area, status));

    emit focusZonesChanged();
}