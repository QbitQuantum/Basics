void pTriangle::ComputeForce(Vector3 vair) {
    //find the tirangle velocity
    velocity = (p1->getVelocity() + p2->getVelocity() + p3->getVelocity()) / 3 ;
    //assume no air velocity for now
    Vector3 v = velocity - vair;
    
    Vector3 r1 = p1->getPosition();
    Vector3 r2 = p2->getPosition();
    Vector3 r3 = p3->getPosition();
    //find triangle unnormalized normal, n*
    Vector3 ra = (r2 - r1);
    Vector3 rb = (r3 - r1);
    Vector3 ncross;
    ncross.Cross(ra, rb);
    
    //constants
    float p = 1.225f;
    float cd = 1.225f;
    
    //force = -1/2 * p * |v|^2 * cd * a * n
    Vector3 v2an = ( (v.Mag()*v.Dot(ncross))/(2.0f*ncross.Mag()) ) * ncross;
    Vector3 aeroForce = (-1.0f/2.0f) * p * cd * v2an;
    aeroForce = aeroForce / 3;
    p1->ApplyForce(aeroForce);
    p2->ApplyForce(aeroForce);
    p3->ApplyForce(aeroForce);
    normal = ncross.Normalize();
}