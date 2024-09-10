bool Wml::Culled (const Plane3<Real>& rkPlane,
    const Ellipsoid3<Real>& rkEllipsoid, bool bUnitNormal)
{
    Vector3<Real> kNormal = rkPlane.GetNormal();
    Real fConstant = rkPlane.GetConstant();
    if ( !bUnitNormal )
    {
        Real fLength = kNormal.Normalize();
        fConstant /= fLength;
    }

    Real fDiscr = kNormal.Dot(rkEllipsoid.InverseA()*kNormal);
    Real fRoot = Math<Real>::Sqrt(Math<Real>::FAbs(fDiscr));
    Real fSDist = kNormal.Dot(rkEllipsoid.Center()) - fConstant;
    return fSDist <= -fRoot;
}