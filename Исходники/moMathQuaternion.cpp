moQuaternion<Real>& moQuaternion<Real>::Squad (Real fT, const moQuaternion& rkQ0,
    const moQuaternion& rkA0, const moQuaternion& rkA1, const moQuaternion& rkQ1)
{
    Real fSlerpT = ((Real)2.0)*fT*((Real)1.0-fT);
    moQuaternion kSlerpP = Slerp(fT,rkQ0,rkQ1);
    moQuaternion kSlerpQ = Slerp(fT,rkA0,rkA1);
    return Slerp(fSlerpT,kSlerpP,kSlerpQ);
}