AcGePoint3d DoubleTTunnelDraw::caclHeadPoint()
{
    AcGeVector3d v = m_endPt - m_startPt;
    v.normalize(); // 单位方向向量
    v = v * m_distance;

    return m_endPt + v;
}