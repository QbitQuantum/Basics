//----------------------------------------------------------------------------
Box2 Mgc::ContOrientedBox (int iQuantity, const Vector2* akPoint)
{
    Box2 kBox;

    GaussPointsFit(iQuantity,akPoint,kBox.Center(),kBox.Axes(),
        kBox.Extents());

    // Let C be the box center and let U0 and U1 be the box axes.  Each input
    // point is of the form X = C + y0*U0 + y1*U1.  The following code
    // computes min(y0), max(y0), min(y1), and max(y1).  The box center is
    // then adjusted to be
    //   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1

    Vector2 kDiff = akPoint[0] - kBox.Center();
    Real fY0Min = kDiff.Dot(kBox.Axis(0)), fY0Max = fY0Min;
    Real fY1Min = kDiff.Dot(kBox.Axis(1)), fY1Max = fY1Min;

    for (int i = 1; i < iQuantity; i++)
    {
        kDiff = akPoint[i] - kBox.Center();

        Real fY0 = kDiff.Dot(kBox.Axis(0));
        if ( fY0 < fY0Min )
            fY0Min = fY0;
        else if ( fY0 > fY0Max )
            fY0Max = fY0;

        Real fY1 = kDiff.Dot(kBox.Axis(1));
        if ( fY1 < fY1Min )
            fY1Min = fY1;
        else if ( fY1 > fY1Max )
            fY1Max = fY1;
    }

    kBox.Center() += (0.5f*(fY0Min+fY0Max))*kBox.Axis(0) +
        (0.5f*(fY1Min+fY1Max))*kBox.Axis(1);

    kBox.Extent(0) = 0.5f*(fY0Max - fY0Min);
    kBox.Extent(1) = 0.5f*(fY1Max - fY1Min);

    return kBox;
}