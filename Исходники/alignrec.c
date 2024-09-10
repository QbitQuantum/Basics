// ----------------------------------------------------------------------------
//
//  CenterRectangles()
//      Move all the rectangles so their origin is the center of their union.
//
// ----------------------------------------------------------------------------
void NEAR PASCAL CenterRectangles(LPRECT arc, UINT count)
{
    LPRECT lprc, lprcL;
    RECT rcUnion;

    CopyRect(&rcUnion, arc);

    lprcL = arc + count;
    for (lprc = arc + 1; lprc < lprcL; lprc++)
    {
        UnionRect(&rcUnion, &rcUnion, lprc);
    }

    for (lprc = arc; count; count--)
    {
        OffsetRect(lprc, -RectCenterX(&rcUnion), -RectCenterY(&rcUnion));
        lprc++;
    }
}