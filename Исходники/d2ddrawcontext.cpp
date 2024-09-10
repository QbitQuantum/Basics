//-----------------------------------------------------------------------------
void D2DDrawContext::drawPoint (const CPoint &point, const CColor& color)
{
    saveGlobalState ();
    setLineWidth (1);
    setFrameColor (color);
    CPoint point2 (point);
    point2.h++;
    moveTo (point);
    lineTo (point2);
    restoreGlobalState ();
}