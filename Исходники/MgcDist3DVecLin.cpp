Real Mgc::SqrDistance (const Vector3& rkPoint, const Line3& rkLine,

    Real* pfParam)

{

    Vector3 kDiff = rkPoint - rkLine.Origin();

    Real fSqrLen = rkLine.Direction().SquaredLength();

    Real fT = kDiff.Dot(rkLine.Direction())/fSqrLen;

    kDiff -= fT*rkLine.Direction();



    if ( pfParam )

        *pfParam = fT;



    return kDiff.SquaredLength();

}