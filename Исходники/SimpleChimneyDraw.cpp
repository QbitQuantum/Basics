void SimpleChimneyDraw::drawSegment( AcGiWorldDraw* mode, const AcGePoint3d& spt, const AcGePoint3d& ept )
{
    AcGeVector3d v = ept - spt;
    int n = ( int )( ( v.length() + m_space ) / ( m_length + m_space ) );
    //acutPrintf(_T("\n可绘制的个数:%d"), n);
    v.normalize();

    AcGePoint3d pt = spt;
    for( int i = 0; i < n; i++ )
    {
        DrawSegment( mode, pt, v, m_length, m_width, m_lineWidth );
        pt = pt + v * ( m_length + m_space );
    }
    double ll = ( ept - pt ).length();
    if( ll > m_length * 0.5 ) // 如果有长度的50%，则绘制一小段
    {
        DrawSegment( mode, pt, v, ll, m_width, m_lineWidth );
    }
}