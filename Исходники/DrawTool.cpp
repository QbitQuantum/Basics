// 闭合多边形向内偏移
bool OffSetPolygon( const AcGePoint3dArray& polygon, double offset, bool is_inner, AcGePoint3dArray& offset_polygon )
{
    // 判断多边形方向
    int dir = ClockWise( polygon );
    if( dir == 0 ) return false;

    // 向内或向外???
    int c = ( is_inner ? -1 : 1 );

    // 偏移方向角度
    //		1) 与多边形的方向有关(dir)
    //		2) 与要偏移的方向有关(is_inner)
    double angle = c * dir * PI * 0.5;

    bool ret = true;

    int n = polygon.length();
    for( int i = 0; i < n; i++ )
    {
        int p1 = ( n + i - 1 ) % n, p2 = i % n, p3 = ( i + 1 ) % n;

        // 对点进行偏移
        // 计算偏移向量
        AcGeVector3d v1 = polygon[p2] - polygon[p1];
        v1.normalize();
        v1.rotateBy( angle, AcGeVector3d::kZAxis );

        AcGeVector3d v2 = polygon[p3] - polygon[p2];
        v2.normalize();
        v2.rotateBy( angle, AcGeVector3d::kZAxis );

        // 求两个向量的夹角
        double angle = v1.angleTo( v2 );
        double L = abs( offset / cos( angle * 0.5 ) );

        AcGeVector3d v = v1 + v2;
        v.normalize();

        offset_polygon.append( polygon[p2] + v * L );
    }
    return ret;
}