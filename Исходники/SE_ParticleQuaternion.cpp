Quaternion Quaternion::Slerp (Real fT, const Quaternion& rkP,
        const Quaternion& rkQ, bool shortestPath)
{
    Real fCos = rkP.Dot(rkQ);
    Quaternion rkT;

    // Do we need to invert rotation?
    if (fCos < 0.0f && shortestPath)
    {
        fCos = -fCos;
        rkT = -rkQ;
    }
    else
    {
        rkT = rkQ;
    }

    if (Math::Abs(fCos) < 1 - ms_fEpsilon)
    {
        // Standard case (slerp)
        Real fSin = Math::Sqrt(1 - Math::Sqr(fCos));
        Radian fAngle = Math::ATan2(fSin, fCos);
        Real fInvSin = 1.0f / fSin;
        Real fCoeff0 = Math::Sin((1.0f - fT) * fAngle) * fInvSin;
        Real fCoeff1 = Math::Sin(fT * fAngle) * fInvSin;
        return fCoeff0 * rkP + fCoeff1 * rkT;
    }
    else
    {
        // There are two situations:
        // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
        // interpolation safely.
        // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
        // are an infinite number of possibilities interpolation. but we haven't
        // have method to fix this case, so just use linear interpolation here.
        Quaternion t = (1.0f - fT) * rkP + fT * rkT;

        // taking the complement requires renormalisation
        t.normalise();
        return t;
    }
}