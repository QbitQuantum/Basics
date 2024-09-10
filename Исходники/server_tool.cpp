bool CWTRect::IntersectRect(const CWTRect& rSrcRect1, const CWTRect& rSrcRect2)
{
    if (rSrcRect1.IsRectEmpty() || rSrcRect2.IsRectEmpty()) {
        return false;
    }

    int tLeft   = max(rSrcRect1.mTopLeft.mX, rSrcRect2.mTopLeft.mX);
    int tTop    = max(rSrcRect1.mTopLeft.mY, rSrcRect2.mTopLeft.mY);
    int tRight  = min(rSrcRect1.mBottomRight.mX, rSrcRect2.mBottomRight.mX);
    int tBottom = min(rSrcRect1.mBottomRight.mY, rSrcRect2.mBottomRight.mY);

    if (CWTRect(tLeft, tTop, tRight, tBottom, false).IsRectEmpty()) {
        SetRectEmpty();
        return false;
    }

    mTopLeft.mX     = tLeft;
    mTopLeft.mY     = tTop;
    mBottomRight.mX = tRight;
    mBottomRight.mY = tBottom;
    return true;
}