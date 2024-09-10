Real NaturalSpline3<Real>::GetSpeedKey (int key, Real t) const
{
    Vector3<Real> velocity = mB[key] + t*(((Real)2)*mC[key] +
        ((Real)3)*t*mD[key]);

    return velocity.Length();
}