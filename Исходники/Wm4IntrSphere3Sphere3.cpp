bool IntrSphere3Sphere3<Real>::Test (Real fTMax,
    const Vector3<Real>& rkVelocity0, const Vector3<Real>& rkVelocity1)
{
    Vector3<Real> kVDiff = rkVelocity1 - rkVelocity0;
    Real fA = kVDiff.SquaredLength();
    Vector3<Real> kCDiff = m_rkSphere1.Center - m_rkSphere0.Center;
    Real fC = kCDiff.SquaredLength();
    Real fRSum = m_rkSphere0.Radius + m_rkSphere1.Radius;
    Real fRSumSqr = fRSum*fRSum;

    if (fA > (Real)0.0)
    {
        Real fB = kCDiff.Dot(kVDiff);
        if (fB <= (Real)0.0)
        {
            if (-fTMax*fA <= fB)
            {
                return fA*fC - fB*fB <= fA*fRSumSqr;
            }
            else
            {
                return fTMax*(fTMax*fA + ((Real)2.0)*fB) + fC <= fRSumSqr;
            }
        }
    }

    return fC <= fRSumSqr;
}