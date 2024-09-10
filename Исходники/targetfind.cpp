bool CTargetFind::isWithinArea(position_t* pos)
{
    return distance(*m_PRadiusAround, *pos) <= m_radius;
}