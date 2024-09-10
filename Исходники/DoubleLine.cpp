void DoubleLine::caclEndPoint( AcGePoint3d& endPt1, AcGePoint3d& endPt2 )
{
    AcGeVector3d v = m_ept - m_spt;
    v.normalize();

    v.rotateBy( PI * 0.5, AcGeVector3d::kZAxis );
    endPt1 = m_ept + v * m_width * 0.5;

    v.rotateBy( PI, AcGeVector3d::kZAxis );
    endPt2 = m_ept + v * m_width * 0.5;
}