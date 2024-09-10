bool IntrRay2Box2<Real>::Test ()
{
    Real WdU[2], AWdU[2], DdU[2], ADdU[2];

    Vector2<Real> diff = mRay->Origin - mBox->Center;

    WdU[0] = mRay->Direction.Dot(mBox->Axis[0]);
    AWdU[0] = Math<Real>::FAbs(WdU[0]);
    DdU[0] = diff.Dot(mBox->Axis[0]);
    ADdU[0] = Math<Real>::FAbs(DdU[0]);
    if (ADdU[0] > mBox->Extent[0] && DdU[0]*WdU[0] >= (Real)0)
    {
        return false;
    }

    WdU[1] = mRay->Direction.Dot(mBox->Axis[1]);
    AWdU[1] = Math<Real>::FAbs(WdU[1]);
    DdU[1] = diff.Dot(mBox->Axis[1]);
    ADdU[1] = Math<Real>::FAbs(DdU[1]);
    if (ADdU[1] > mBox->Extent[1] && DdU[1]*WdU[1] >= (Real)0)
    {
        return false;
    }

    Vector2<Real> perp = mRay->Direction.Perp();
    Real LHS = Math<Real>::FAbs(perp.Dot(diff));
    Real part0 = Math<Real>::FAbs(perp.Dot(mBox->Axis[0]));
    Real part1 = Math<Real>::FAbs(perp.Dot(mBox->Axis[1]));
    Real RHS = mBox->Extent[0]*part0 + mBox->Extent[1]*part1;
    return LHS <= RHS;
}