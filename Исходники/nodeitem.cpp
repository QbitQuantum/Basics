void NodeItem::setRadius(qreal radius)
{
    m_radius = radius;
    setRect(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
    update();
}