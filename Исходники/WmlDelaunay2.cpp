bool Delaunay2<Real>::InTriangle (const Vector2<Real>& rkV0,
    const Vector2<Real>& rkV1, const Vector2<Real>& rkV2,
    const Vector2<Real>& rkTest)
{
    // test against normal to first edge
    Vector2<Real> kDir = rkTest - rkV0;
    Vector2<Real> kNor(rkV0.Y() - rkV1.Y(), rkV1.X() - rkV0.X());
    if ( kDir.Dot(kNor) < -Math<Real>::EPSILON )
        return false;

    // test against normal to second edge
    kDir = rkTest - rkV1;
    kNor = Vector2<Real>(rkV1.Y() - rkV2.Y(), rkV2.X() - rkV1.X());
    if ( kDir.Dot(kNor) < -Math<Real>::EPSILON )
        return false;

    // test against normal to third edge
    kDir = rkTest - rkV2;
    kNor = Vector2<Real>(rkV2.Y() - rkV0.Y(), rkV0.X() - rkV2.X());
    if ( kDir.Dot(kNor) < -Math<Real>::EPSILON )
        return false;

    return true;
}