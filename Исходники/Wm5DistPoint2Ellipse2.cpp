Real DistPoint2Ellipse2<Real>::GetSquared ()
{
    // Compute coordinates of point in ellipse coordinate system.
    Vector2<Real> diff = *mPoint - mEllipse->Center;
    Vector2<Real> y(diff.Dot(mEllipse->Axis[0]), diff.Dot(mEllipse->Axis[1]));
    Vector2<Real> x;

    Real sqrDistance = SqrDistance(mEllipse->Extent, y, x);

    mClosestPoint0 = *mPoint;
    mClosestPoint1 = mEllipse->Center +
        x[0]*mEllipse->Axis[0] +
        x[1]*mEllipse->Axis[1];

    return sqrDistance;
}