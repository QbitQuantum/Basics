void Vector3<Real>::GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
    Vector3& rkW, bool bUnitLengthW)
{
    if ( !bUnitLengthW )
        rkW.Normalize();

    Real fInvLength;

    if ( Math<Real>::FAbs(rkW.m_afTuple[0]) >=
         Math<Real>::FAbs(rkW.m_afTuple[1]) )
    {
        // W.x or W.z is the largest magnitude component, swap them
        fInvLength = Math<Real>::InvSqrt(rkW.m_afTuple[0]*rkW.m_afTuple[0] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = -rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[1] = (Real)0.0;
        rkU.m_afTuple[2] = +rkW.m_afTuple[0]*fInvLength;
    }
    else
    {
        // W.y or W.z is the largest magnitude component, swap them
        fInvLength = Math<Real>::InvSqrt(rkW.m_afTuple[1]*rkW.m_afTuple[1] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = (Real)0.0;
        rkU.m_afTuple[1] = +rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[2] = -rkW.m_afTuple[1]*fInvLength;
    }

    rkV = rkW.Cross(rkU);
}