//----------------------------------------------------------------------------
bool SEIntrLine3Box3f::DoClipping(float fT0, float fT1, const SEVector3f& 
    rOrigin, const SEVector3f& rDirection, const SEBox3f& rBox, bool bSolid, 
    int& riCount, SEVector3f aPoint[2], int& riIntrType)
{
    SE_ASSERT( fT0 < fT1 );

    // 把linear component变换到box坐标体系下.
    SEVector3f vec3fDiff = rOrigin - rBox.Center;
    SEVector3f vec3fBOrigin(
        vec3fDiff.Dot(rBox.Axis[0]),
        vec3fDiff.Dot(rBox.Axis[1]),
        vec3fDiff.Dot(rBox.Axis[2])
    );
    SEVector3f vec3fBDirection(
        rDirection.Dot(rBox.Axis[0]),
        rDirection.Dot(rBox.Axis[1]),
        rDirection.Dot(rBox.Axis[2])
    );

    float fSaveT0 = fT0, fSaveT1 = fT1;
    bool bNotAllClipped =
        Clip(+vec3fBDirection.X, -vec3fBOrigin.X-rBox.Extent[0], fT0, fT1) &&
        Clip(-vec3fBDirection.X, +vec3fBOrigin.X-rBox.Extent[0], fT0, fT1) &&
        Clip(+vec3fBDirection.Y, -vec3fBOrigin.Y-rBox.Extent[1], fT0, fT1) &&
        Clip(-vec3fBDirection.Y, +vec3fBOrigin.Y-rBox.Extent[1], fT0, fT1) &&
        Clip(+vec3fBDirection.Z, -vec3fBOrigin.Z-rBox.Extent[2], fT0, fT1) &&
        Clip(-vec3fBDirection.Z, +vec3fBOrigin.Z-rBox.Extent[2], fT0, fT1);

    if( bNotAllClipped && (bSolid || fT0 != fSaveT0 || fT1 != fSaveT1) )
    {
        if( fT1 > fT0 )
        {
            riIntrType = IT_SEGMENT;
            riCount = 2;
            aPoint[0] = rOrigin + fT0*rDirection;
            aPoint[1] = rOrigin + fT1*rDirection;
        }
        else
        {
            riIntrType = IT_POINT;
            riCount = 1;
            aPoint[0] = rOrigin + fT0*rDirection;
        }
    }
    else
    {
        riCount = 0;
        riIntrType = IT_EMPTY;
    }

    return riIntrType != IT_EMPTY;
}