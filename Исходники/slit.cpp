qreal Slit::scalar(const Ray * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the slit's edges lie
    qreal l = rdy * (m_leftEdge.x() - rx) - rdx * (m_leftEdge.y() - ry);
    qreal r = rdy * (m_rightEdge.x() - rx) - rdx * (m_rightEdge.y() - ry);
    qreal sl = rdy * (m_leftSlitEdge.x() - rx) - rdx * (m_leftSlitEdge.y() - ry);
    qreal sr = rdy * (m_rightSlitEdge.x() - rx) - rdx * (m_rightSlitEdge.y() - ry);
    //pair of points lie on the same side of ray - intersection impossible
    if(((Settings::fuzzyIsGreaterThanZero(l) && Settings::fuzzyIsGreaterThanZero(sl)) || (Settings::fuzzyIsLessThanZero(l) && Settings::fuzzyIsLessThanZero(sl)))&&((Settings::fuzzyIsGreaterThanZero(r) && Settings::fuzzyIsGreaterThanZero(sr)) || (Settings::fuzzyIsLessThanZero(r) && Settings::fuzzyIsLessThanZero(sr)))) return -1.0;
    qreal sx = m_leftEdge.x(); //x coordinate of slit segment edge
    qreal sy = m_leftEdge.y(); //y coordinate of slit segment edge
    qreal sdx = m_rightEdge.x() - sx; //horizontal component of the slit segment's vector
    qreal sdy = m_rightEdge.y() - sy; //vertical component of the slit segment's vector
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into line equation: (sdy * (x - sx) - sdx * (y - sy) = 0) and solve for d
    return (sdx * ry - sdy * rx + sdy * sx - sdx * sy) / (sdy * rdx - sdx * rdy);
}