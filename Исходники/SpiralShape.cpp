void SpiralShape::createPath(const QSizeF &size)
{
    Q_UNUSED(size);
    clear();
    QPointF center = QPointF(m_radii.x() / 2.0, m_radii.y() / 2.0);
    //moveTo(QPointF(size.width(), m_radii.y()));
    qreal adv_ang = (m_clockwise ? -1.0 : 1.0) * M_PI_2;
    // radius of first segment is non-faded radius:
    qreal m_radius = m_radii.x() / 2.0;
    qreal r = m_radius;

    QPointF oldP(center.x(), (m_clockwise ? -1.0 : 1.0) * m_radius + center.y());
    QPointF newP;
    QPointF newCenter(center);
    moveTo(oldP);
    uint m_segments = 10;
    //m_handles[0] = oldP;

    for (uint i = 0; i < m_segments; ++i) {
        newP.setX(r * cos(adv_ang * (i + 2)) + newCenter.x());
        newP.setY(r * sin(adv_ang * (i + 2)) + newCenter.y());

        if (m_type == Curve) {
            qreal rx = qAbs(oldP.x() - newP.x());
            qreal ry = qAbs(oldP.y() - newP.y());
            if (m_clockwise) {
                arcTo(rx, ry, ((i + 1) % 4) * 90, 90);
            } else {
                arcTo(rx, ry, 360 - ((i + 1) % 4) * 90, -90);
            }
        } else {
            lineTo(newP);
        }

        newCenter += (newP - newCenter) * (1.0 - m_fade);
        oldP = newP;
        r *= m_fade;
    }
    //m_handles[1] = QPointF(center.x(), (m_clockwise ? -1.0 : 1.0) * m_radius + center.y());
    m_points = *m_subpaths[0];
}