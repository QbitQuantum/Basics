//----------------------------------------------------------------------------
bool Mgc::TestIntersection (const Plane& rkPlane,
    const Ellipsoid& rkEllipsoid, bool bUnitNormal)
{
    Vector3 kNormal = rkPlane.Normal();
    Real fConstant = rkPlane.Constant();
    if ( !bUnitNormal )
    {
        Real fLength = kNormal.Unitize();
        fConstant /= fLength;
    }

    Real fDiscr = kNormal.Dot(rkEllipsoid.InverseA()*kNormal);
    Real fRoot = Math::Sqrt(Math::FAbs(fDiscr));
    Real fSDist = kNormal.Dot(rkEllipsoid.Center()) - fConstant;
    return Math::FAbs(fSDist) <= fRoot;
}