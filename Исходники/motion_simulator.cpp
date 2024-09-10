IC float intersectRayIdentitySphere(const Fvector& rO, const Fvector& rV)
{
    Fvector Q;
    Q.invert(rO);

    float c = Q.magnitude();
    float v = Q.dotproduct(rV);
    float d = 1 - (c*c - v*v);

    // If there was no intersection, return -1
    if (d < 0.0) return (-1.0f);

    // Return the distance to the [first] intersecting point
    return (v - _sqrt(d));
}