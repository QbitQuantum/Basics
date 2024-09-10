CylinderFit3<Real>::CylinderFit3 (int numPoints, const Vector3<Real>* points,
    Vector3<Real>& center, Vector3<Real>& axis, Real& radius, Real& height,
    bool inputsAreInitialGuess)
{
    Real invRSqr = (Real)1;
    if (!inputsAreInitialGuess)
    {
        // Find the least-squares line that fits the data and use it as an
        // initial guess for the cylinder axis.
        Line3<Real> line = OrthogonalLineFit3(numPoints, points);
        center = line.Origin;
        axis = line.Direction;
    }

    mError = Math<Real>::MAX_REAL;
    const int iMax = 8;
    int i;
    for (i = 0; i < iMax; ++i)
    {
        mError = UpdateInvRSqr(numPoints, points, center, axis, invRSqr);
        mError = UpdateDirection(numPoints, points, center, axis, invRSqr);
        mError = UpdateCenter(numPoints, points, center, axis, invRSqr);
    }

    // Compute the radius.
    radius = Math<Real>::InvSqrt(invRSqr);

    // Project points onto fitted axis to determine extent of cylinder along
    // the axis.
    Real tMin = axis.Dot(points[0] - center);
    Real tMax = tMin;
    for (i = 1; i < numPoints; ++i)
    {
        Real t = axis.Dot(points[i] - center);
        if (t < tMin)
        {
            tMin = t;
        }
        else if (t > tMax)
        {
            tMax = t;
        }
    }

    // Compute the height.  Adjust the center to point that projects to
    // midpoint of extent.
    height = tMax - tMin;
    center += (((Real)0.5)*(tMin + tMax))*axis;
}