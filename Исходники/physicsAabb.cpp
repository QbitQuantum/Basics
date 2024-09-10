bool physicsAabb::overlaps(const physicsAabb& aabb)
{
    Point2f centerA = m_max.add(m_min);
    centerA.setMul(0.5f);

    Point2f centerB = aabb.m_max.add(aabb.m_min);
    centerB.setMul(0.5f);

    float dx = abs(centerA.x - centerB.x);
    float dy = abs(centerA.y - centerB.y);

    float sumX = m_max.x - centerA.x + aabb.m_max.x - centerB.x;
    float sumY = m_max.y - centerA.y + aabb.m_max.y - centerB.y;

    return (dx < sumX && dy < sumY);
}