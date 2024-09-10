//--------------------------------------------------------------------------------------------------
///  Test bounding box to see if it's outside the frustum or not
///
/// \return true if outside or exactly on the boundary. false if inside.
//--------------------------------------------------------------------------------------------------
bool Frustum::isOutside(const BoundingBox& bbox) const
{
    CVF_ASSERT(m_planes.size() == 6);

    const Vec3d& boxMin = bbox.min();
    const Vec3d& boxMax = bbox.max();

    Vec3d point;
    Vec3d planeNormal;

    std::map<int, Plane>::const_iterator it;
    for (it = m_planes.begin(); it != m_planes.end(); it++)
    {
        planeNormal = it->second.normal();

        point.x() = (planeNormal.x() <= 0.0) ? boxMin.x() : boxMax.x();
        point.y() = (planeNormal.y() <= 0.0) ? boxMin.y() : boxMax.y();
        point.z() = (planeNormal.z() <= 0.0) ? boxMin.z() : boxMax.z();

        if (it->second.distanceSquared(point) < 0.0)
        {
            return true;
        }
    }

    return false;
}