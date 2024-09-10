//----------------------------------------------------------------------------
void Curve3::GetFrame (Real fTime, Vector3& rkPosition, Vector3& rkTangent,
    Vector3& rkNormal, Vector3& rkBinormal) const
{
    rkPosition = GetPosition(fTime);
    Vector3 kVelocity = GetFirstDerivative(fTime);
    Vector3 kAcceleration = GetSecondDerivative(fTime);
    Real fVDotV = kVelocity.Dot(kVelocity);
    Real fVDotA = kVelocity.Dot(kAcceleration);
    rkNormal = fVDotV*kAcceleration - fVDotA*kVelocity;
    rkNormal.Unitize();
    rkTangent = kVelocity;
    rkTangent.Unitize();
    rkBinormal = rkTangent.Cross(rkNormal);
}