bool IntrSegment2Box2<Real>::Test ()
{
    Vector2<Real> diff = mSegment->Center - mBox->Center;

    Real AWdU[2], ADdU[2], RHS;
    AWdU[0] = Math<Real>::FAbs(mSegment->Direction.Dot(mBox->Axis[0]));
    ADdU[0] = Math<Real>::FAbs(diff.Dot(mBox->Axis[0]));
    RHS = mBox->Extent[0] + mSegment->Extent*AWdU[0];
    if (ADdU[0] > RHS)
    {
        return false;
    }

    AWdU[1] = Math<Real>::FAbs(mSegment->Direction.Dot(mBox->Axis[1]));
    ADdU[1] = Math<Real>::FAbs(diff.Dot(mBox->Axis[1]));
    RHS = mBox->Extent[1] + mSegment->Extent*AWdU[1];
    if (ADdU[1] > RHS)
    {
        return false;
    }

    Vector2<Real> perp = mSegment->Direction.Perp();
    Real LHS = Math<Real>::FAbs(perp.Dot(diff));
    Real part0 = Math<Real>::FAbs(perp.Dot(mBox->Axis[0]));
    Real part1 = Math<Real>::FAbs(perp.Dot(mBox->Axis[1]));
    RHS = mBox->Extent[0]*part0 + mBox->Extent[1]*part1;
    return LHS <= RHS;
}