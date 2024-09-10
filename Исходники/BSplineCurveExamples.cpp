//----------------------------------------------------------------------------
void BSplineCurveExamples::OnDisplay ()
{
    ClearScreen();

    ColorRGB lightGray(224, 224, 224);
    ColorRGB mediumGray(192, 192, 192);
    ColorRGB darkGray(128, 128, 128);
    ColorRGB black(0, 0, 0);

    // draw axes
    int i;
    for (i = mSize/16; i < mSize; ++i)
    {
        SetPixel(mSize/16, mSize - 1 - i, lightGray);
        SetPixel(i, mSize - 1 - mSize/16, lightGray);
    }

    // draw control points
    int imax = mSpline->GetNumCtrlPoints();
    int x, y;
    for (i = 0; i < imax; ++i)
    {
        const Vector2f& ctrl = mSpline->GetControlPoint(i);
        x = (int)(ctrl.X() + 0.5f);
        y = mSize - 1 - (int)(ctrl.Y() + 0.5f);
        SetThickPixel(x, y, 2, darkGray);
    }

    // draw spline
    imax = 2048;
    for (i = 0; i <= imax; ++i)
    {
        // draw point
        float u = i/(float)imax;
        Vector2f pos = mSpline->GetPosition(u);
        x = (int)(pos.X() + 0.5f);
        y = mSize - 1 - (int)(pos.Y() + 0.5f);

        if (mModified
        &&  mLocCtrlMin[mCurveType] <= u && u <= mLocCtrlMax[mCurveType])
        {
            SetPixel(x, y, mediumGray);
        }
        else
        {
            SetPixel(x, y, black);
        }
    }

    WindowApplication2::OnDisplay();
}