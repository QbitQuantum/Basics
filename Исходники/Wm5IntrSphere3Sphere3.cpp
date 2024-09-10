    bool IntrSphere3Sphere3<Real>::Test ( Real tmax,
                                          const Vector3<Real>& velocity0, const Vector3<Real>& velocity1 )
    {
        Vector3<Real> relVelocity = velocity1 - velocity0;
        Real a = relVelocity.SquaredLength();
        Vector3<Real> CDiff = mSphere1->Center - mSphere0->Center;
        Real c = CDiff.SquaredLength();
        Real rSum = mSphere0->Radius + mSphere1->Radius;
        Real rSumSqr = rSum * rSum;

        if ( a > ( Real )0 )
        {
            Real b = CDiff.Dot( relVelocity );
            if ( b <= ( Real )0 )
            {
                if ( -tmax * a <= b )
                {
                    return a * c - b * b <= a * rSumSqr;
                }
                else
                {
                    return tmax * ( tmax * a + ( ( Real )2 ) * b ) + c <= rSumSqr;
                }
            }
        }

        return c <= rSumSqr;
    }