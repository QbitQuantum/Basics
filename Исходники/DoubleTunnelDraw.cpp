void DoubleTunnelDraw::caclEndPoint( AcGePoint3d& endPt1, AcGePoint3d& endPt2 )
{
    AcGeVector3d v = m_endPt - m_startPt;
    v.normalize();

    v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
    endPt1 = m_endPt + v * m_width * 0.5;

    v.rotateBy( PI, AcGeVector3d::kZAxis );
    endPt2 = m_endPt + v * m_width * 0.5;
}