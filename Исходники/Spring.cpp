Vec Spring::getCurrentForce() const
{
    // we compute the force applied on particle 1 by particle 2

    Vec u = p1->getPosition() - p2->getPosition();

    double uNorm = u.normalize();	// u is thereafter normalized!
    if (uNorm < 1.0e-6) 
        return Vec();	// null force

    // force due to stiffness only
    Vec sF = -stiffness * (uNorm - equilibriumLength) * u;
    // damping force
    Vec dF = -damping * ((p1->getVelocity() - p2->getVelocity()) * u) * u;

    return sF + dF;
}