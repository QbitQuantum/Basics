void Wml::BoxProjection (const Vector3<Real>& rkAxis,
    const Box3<Real>& rkBox, Real& rfMin, Real& rfMax)
{
    Real fOrigin = rkAxis.Dot(rkBox.Center());
    Real fMaximumExtent =
        Math<Real>::FAbs(rkBox.Extent(0)*rkAxis.Dot(rkBox.Axis(0))) +
        Math<Real>::FAbs(rkBox.Extent(1)*rkAxis.Dot(rkBox.Axis(1))) +
        Math<Real>::FAbs(rkBox.Extent(2)*rkAxis.Dot(rkBox.Axis(2)));

    rfMin = fOrigin - fMaximumExtent;
    rfMax = fOrigin + fMaximumExtent;
}