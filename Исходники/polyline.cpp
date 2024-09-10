double Polyline::project(const Vector2d &point) const
{
    double bestS = 0.;
    double minDistSq = (point - _pts[0]).squaredNorm();

    for(int i = 0; i < _pts.endIdx(1); ++i)
    {
        double len = (_lengths[i + 1] - _lengths[i]);
        double invLen = 1. / len;
        Vector2d der = (_pts[i + 1] - _pts[i]) * invLen;
        double dot = der.dot(point - _pts[i]);        
        if(dot < 0.)
            dot = 0.;
        if(dot > len)
            dot = len;

        Vector2d ptOnLine = _pts[i] + (_pts[i + 1] - _pts[i]) * (dot * invLen);
        double distSq = (ptOnLine - point).squaredNorm();
        if(distSq < minDistSq)
        {
            minDistSq = distSq;
            bestS = _lengths[i] + dot;
        }
    }

    return bestS;
}