float CCPoint::getAngle(const CCPoint& other) const
{
    CCPoint a2 = normalize();
    CCPoint b2 = other.normalize();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if( fabs(angle) < __FLT_EPSILON__ ) return 0.f;
    return angle;
}