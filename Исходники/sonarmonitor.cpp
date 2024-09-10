void SonarMonitor::draw()
{
    Point point = m_hud->project(m_point);
    int radius = (m_hud->project(m_point + Point(0, m_radius)) - point).y;
    float scale = static_cast<float>(radius)/m_scale;
    PointF center = PointF(point) - PointF(1.5f);
    RectF rect = RectF(center, SizeF(4, 4));
    Matrix m(1);
    m = glm::scale(m, Vector3D(1, -1, 0));
    m = glm::rotate(m, m_hud->scenario()->yaw(), Vector3D(0, 0, 1));
    m = glm::translate(m, -m_hud->scenario()->position());

    m_hud->fontGreen().draw("T", point + Point(-2, -radius));
    m_hud->fontGreen().draw(QString("%1M").arg(m_scale), Rect(point + Point(-100, radius - 8), SizeF(200, -1)), true, false);
    m_center.draw(rect);

    for (fight::NavPoint *navPoint : m_hud->scenario()->navPoints())
        if (navPoint->isEnabled())
        {
            Vector2D dir = Vector2D(m * Vector4D(navPoint->position(), 1));
            float distance = glm::length(dir);
            if (distance < m_scale)
            {
                rect.setPos(center - dir*scale);
                m_nav.draw(rect);
            }
        }

    for (const auto &entry : m_hud->scenario()->sonar())
    {
        Vector2D dir = Vector2D(m * Vector4D(entry.object->position(), 1));
        float distance = glm::length(dir);
        if (distance < m_scale)
        {
            rect.setPos(center - dir*scale);
            (entry.isFriend ? m_friend : m_enemy).draw(rect);
        }
    }

    fight::Target &target = m_hud->scenario()->target();
    if (target.isLocked())
    {
        Vector2D dir = Vector2D(m * Vector4D(target.position(), 1));
        float distance = glm::length(dir);
        if (distance < m_scale)
        {
            rect.setPos(center - dir*scale);
            m_target.draw(rect);
        }
    }
}