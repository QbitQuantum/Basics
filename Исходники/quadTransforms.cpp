Point2F BiQuadToSqr::transform( const Point2F &p ) const
{
    Point2F kA = m_kP00 - p;

    F32 fAB = mDotPerp( kA, m_kB );
    F32 fAC = mDotPerp( kA, m_kC);

    // 0 = ac*bc+(bc^2+ac*bd-ab*cd)*s+bc*bd*s^2 = k0 + k1*s + k2*s^2
    F32 fK0 = fAC*m_fBC;
    F32 fK1 = m_fBC*m_fBC + fAC*m_fBD - fAB*m_fCD;
    F32 fK2 = m_fBC*m_fBD;

    if (mFabs(fK2) > POINT_EPSILON)
    {
        // s-equation is quadratic
        F32 fInv = 0.5f/fK2;
        F32 fDiscr = fK1*fK1 - 4.0f*fK0*fK2;
        F32 fRoot = mSqrt( mFabs(fDiscr) );

        Point2F kResult0( 0, 0 );
        kResult0.x = (-fK1 - fRoot)*fInv;
        kResult0.y = fAB/(m_fBC + m_fBD*kResult0.x);
        F32 fDeviation0 = deviation(kResult0);
        if ( fDeviation0 == 0.0f )
            return kResult0;

        Point2F kResult1( 0, 0 );
        kResult1.x = (-fK1 + fRoot)*fInv;
        kResult1.y = fAB/(m_fBC + m_fBD*kResult1.x);
        F32 fDeviation1 = deviation(kResult1);
        if ( fDeviation1 == 0.0f )
            return kResult1;

        if (fDeviation0 <= fDeviation1)
        {
            if ( fDeviation0 < POINT_EPSILON )
                return kResult0;
        }
        else
        {
            if ( fDeviation1 < POINT_EPSILON )
                return kResult1;
        }
    }
    else
    {
        // s-equation is linear
        Point2F kResult( 0, 0 );

        kResult.x = -fK0/fK1;
        kResult.y = fAB/(m_fBC + m_fBD*kResult.x);
        F32 fDeviation = deviation(kResult);
        if ( fDeviation < POINT_EPSILON )
            return kResult;
    }

    // point is outside the quadrilateral, return invalid
    return Point2F(F32_MAX,F32_MAX);
}