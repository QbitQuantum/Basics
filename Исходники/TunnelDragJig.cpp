Adesk::Boolean TunnelDragJig::update()
{
    AcGePlane plane;
    AcGeVector3d v = ept - spt;
    v.normalize();

    v.rotateBy( 0.5 * PI, AcGeVector3d::kZAxis );

    AcGeVector3d offset = curPt - basePt;
    double L = offset.dotProduct( v );
    if( L == 0 ) return false;

    if( L < 0 )
    {
        v.negate();
        L = -1 * L;
    }

    AcGePoint3d newSpt = spt + v * L, newEpt = ept + v * L;

    // 更新工作面坐标
    m_pWS->setSEPoint( newSpt, newEpt );
    m_pWS->updateDraw();

    return Adesk::kTrue;
}