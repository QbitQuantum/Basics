/*! Get the position of the location relative to its body in 
 *  the J2000 ecliptic coordinate system.
 */
Vector3d Location::getPlanetocentricPosition(double t) const
{
    if (parent == NULL)
    {
        return position.cast<double>();
    }
    else
    {
        Quaterniond q = parent->getEclipticToBodyFixed(t);
        return q.conjugate() * position.cast<double>();
    }
}